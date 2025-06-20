#include "app/app.hpp"

#include <iostream>

int main(const int argc, const char **argv)
{
    CommandLine commandLine(argc, argv);
    App app(commandLine);

    try
    {
        app.run();
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what();
    }

    return 0;
}