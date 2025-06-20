#include "cli/command_line_iterator.hpp"

CommandLineIterator::CommandLineIterator(CommandLineArgument &firstArgument)
    : _firstArgument(firstArgument)
{
    _currentArgument = &_firstArgument;
}

CommandLineArgument &CommandLineIterator::consume()
{
    CommandLineArgument &oldCurrentArgument = *_currentArgument;

    _currentArgument = &_currentArgument->getNext();

    return oldCurrentArgument;
}