#pragma once

#include <string>
#include <vector>


#include "app/app_flags.hpp"
#include "cli/command_line.hpp"

class App
{
public:
    App(const CommandLine &commandLine);

    void run();

private:
    void parseCommandLine();

    constexpr bool hasFlag(AppFlags flags) const
    {
        return ::hasFlag(_flags, flags);
    }

    const CommandLine &_commandLine;
    AppFlags _flags;
    std::vector<std::string> _input_file_paths;
    std::string _output_path;
};