#include "app/app.hpp"

#include <iostream>

#include "cli/command_line_iterator.hpp"

App::App(const CommandLine &commandLine) : _commandLine(commandLine) {}

void App::run()
{
    parseCommandLine();

    if (hasFlag(AppFlags::Help))
    {
        std::cout << "USAGE\n";
        return;
    }
}

void App::parseCommandLine()
{
    // skip program name using .getNext()
    CommandLineIterator iterator(_commandLine.getFirstArgument().getNext());

    _flags = AppFlags::None;
    _input_file_paths.clear();
    _output_path = "a.out";

    bool hasNoInputFiles = true;

    std::string errorMessage;

    while (!iterator.isDone())
    {
        if (iterator.peek().isOption({"-h", "--help"}))
        {
            _flags |= AppFlags::Help;
            return;
        }
        else if (iterator.peek().isOption({"-o", "--output"}))
        {
            if (!iterator.peek().hasNext())
            {
                errorMessage.append(
                    "invalid option: " + iterator.consume().getValue() +
                    " (expects 1 argument)\n");
            }
            else
            {
                iterator.skip();
                _output_path = iterator.consume().getValue();
            }
        }
        else if (iterator.peek().isOption())
        {
            errorMessage.append(
                "unknown option: " + iterator.consume().getValue() + "\n");
        }
        else
        {
            _input_file_paths.push_back(iterator.consume().getValue());
            if (hasNoInputFiles)
            {
                hasNoInputFiles = false;
            }
        }
    }

    if (hasNoInputFiles)
    {
        errorMessage.append("no input file\n");
    }

    if (!errorMessage.empty())
    {
        throw std::runtime_error(errorMessage);
    }

    return;
}