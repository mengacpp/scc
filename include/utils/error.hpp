#pragma once

#include <string>

enum class ErrorSeverity
{
    Error,
    Warning,
};

class ErrorMessage
{
public:
    ErrorMessage(std::string source, ErrorSeverity severity,
                 std::string description, std::string context = "",
                 std::string remedy = "", bool extended = false)
        : _source(source), _severity(severity), _description(description),
          _context(context), _remedy(remedy), _extended(extended)
    {
    }

    std::string get() const;

private:
    std::string _source;
    std::string _description;
    std::string _context;
    std::string _remedy;

    ErrorSeverity _severity;
    bool _extended;
};

std::string createErrorMessage(std::string description,
                               std::string context = "",
                               std::string remedy = "", bool extended = false);

std::string createWarningMessage(std::string description,
                                 std::string context = "",
                                 std::string remedy = "",
                                 bool extended = false);

class ErrorMessageStream
{
public:
    ErrorMessageStream() = default;


    ErrorMessageStream appendError(std::string description,
                                   std::string context = "",
                                   std::string remedy = "",
                                   bool extended = false)
    {
        _message.append(
            createErrorMessage(description, context, remedy, extended));
        return *this;
    }

    ErrorMessageStream appendWarning(std::string description,
                                     std::string context = "",
                                     std::string remedy = "",
                                     bool extended = false)
    {
        _message.append(
            createWarningMessage(description, context, remedy, extended));
        return *this;
    }

    const std::string &str() const { return _message; }

private:
    std::string _message;
};