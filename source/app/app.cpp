#include "app/app.hpp"

#include <iostream>

#include "cli/command_line_iterator.hpp"

#include "utils/error.hpp"

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

    ErrorMessageStream errorMessageStream;

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
                errorMessageStream.appendError(
                    "invalid option: " + iterator.consume().getValue(), "",
                    "supply a filename (es. -o output)");
            }
            else
            {
                iterator.skip();
                _output_path = iterator.consume().getValue();
            }
        }
        else if (iterator.peek().isOption())
        {
            errorMessageStream.appendError("unknown option: " +
                                           iterator.consume().getValue());
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
        errorMessageStream.appendError("no input file");
    }

    if (!errorMessageStream.str().empty())
    {
        throw std::runtime_error(errorMessageStream.str());
    }

    return;
}