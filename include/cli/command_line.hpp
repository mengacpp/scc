#pragma once

#include <memory>
#include <string>
#include <vector>

class CommandLineArgument
{
public:
    CommandLineArgument(std::string value) : _value(value), _next(nullptr) {}

    bool hasNext() const noexcept { return _next != nullptr; }
    CommandLineArgument &getNext() const noexcept { return *_next.get(); }
    CommandLineArgument &setNext(std::unique_ptr<CommandLineArgument> next)
    {
        _next.reset();
        _next = std::move(next);
        return getNext();
    }

    const std::string &getValue() const noexcept { return _value; }

    bool isOption(std::vector<std::string> options = {}) const noexcept
    {
        if (_value.empty()) return false;

        if (options.empty()) return _value.at(0) == '-';

        for (const std::string &option : options)
        {
            if (_value == option)
            {
                return true;
            }
        }

        return false;
    }

private:
    std::string _value;
    std::unique_ptr<CommandLineArgument> _next;
};

class CommandLine
{
public:
    CommandLine(const int argc, const char **argv);

    CommandLineArgument &getFirstArgument() const noexcept
    {
        return *_firstArgument.get();
    }

private:
    std::unique_ptr<CommandLineArgument> _firstArgument;
};
