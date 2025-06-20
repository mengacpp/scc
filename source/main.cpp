#include "cli/command_line.hpp"
#include "cli/command_line_iterator.hpp"


#include <iostream>

int main(const int argc, const char **argv)
{
    CommandLine commandLine(argc, argv);

    CommandLineIterator iterator(commandLine.getFirstArgument());

    while (!iterator.isDone())
    {
        std::cout << iterator.consume().getValue() << "\n";
    }

    return 0;
}