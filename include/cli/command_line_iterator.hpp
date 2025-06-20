#pragma once

#include "command_line.hpp"

class CommandLineIterator
{
public:
    CommandLineIterator(CommandLineArgument &firstArgument);

    bool isDone() const noexcept { return _currentArgument == nullptr; }
    void reset() noexcept { _currentArgument = &_firstArgument; }

    CommandLineArgument &peek() const { return *_currentArgument; }

    void skip();
    CommandLineArgument &consume();

private:
    CommandLineArgument &_firstArgument;
    CommandLineArgument *_currentArgument;
};