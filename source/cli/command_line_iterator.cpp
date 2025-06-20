#include "cli/command_line_iterator.hpp"

CommandLineIterator::CommandLineIterator(CommandLineArgument &firstArgument)
    : _firstArgument(firstArgument)
{
    _currentArgument = &_firstArgument;
}

void CommandLineIterator::skip()
{
    _currentArgument = &_currentArgument->getNext();
}

CommandLineArgument &CommandLineIterator::consume()
{
    CommandLineArgument &oldCurrentArgument = *_currentArgument;

    _currentArgument = &_currentArgument->getNext();

    return oldCurrentArgument;
}