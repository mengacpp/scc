#pragma once

#include <string>

const std::string USAGE = R"(Usage: scc [OPTIONS] <input-file>

A Small C Compiler.

OPTIONS:
    -h, --help             Show this message
    -o, --output <file>     Write output to file <file> (default: a.out)

ARGS:
    <input-file>            Source file to compile (*.c)

)";