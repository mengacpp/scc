#include "cli/command_line.hpp"

#include <cstddef>

CommandLine::CommandLine(const int argc, const char **argv)
{
    _firstArgument = std::make_unique<CommandLineArgument>(argv[0]);

    CommandLineArgument *currentArgument = _firstArgument.get();

    for (size_t i = 1; i < argc; i++)
    {
        currentArgument = &currentArgument->setNext(
            std::make_unique<CommandLineArgument>(argv[i]));
    }
}