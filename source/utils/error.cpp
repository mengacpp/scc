#include "utils/error.hpp"

#include <iomanip>
#include <sstream>


#include "utils/ansi.hpp"

std::string severity_to_string(ErrorSeverity severity)
{
    std::stringstream message;

    switch (severity)
    {
    case ErrorSeverity::Error:
        message << ansi::Color::BrightRed << "error" << ansi::Style::Reset;
        break;
    case ErrorSeverity::Warning:
        message << ansi::Color::BrightYellow << "warning" << ansi::Style::Reset;
        break;
    }

    return message.str();
}

std::string ErrorMessage::get() const
{
    std::stringstream message;

    std::string sourceString = _source + ": ",
                contextString = "context: ", remedyString = "remedy: ";

    if (_extended)
    {
        message << sourceString;
        message << severity_to_string(_severity) << ": ";

        message << _description << "\n";

        if (!_context.empty())
        {
            message << ansi::Color::BrightBlue
                    << std::setw(sourceString.length() + contextString.length())
                    << contextString << ansi::Style::Reset << _context << "\n";
        }

        if (!_remedy.empty())
        {
            message << ansi::Color::BrightBlue
                    << std::setw(sourceString.length() + remedyString.length())
                    << remedyString << ansi::Style::Reset << _remedy << "\n";
        }
    }
    else
    {
        message << _source << ": ";

        if (!_context.empty())
        {
            message << _context << ": ";
        }

        message << severity_to_string(_severity) << ": ";

        message << _description << ". ";

        if (!_remedy.empty())
        {
            message << ansi::Color::BrightBlack << _remedy
                    << ansi::Style::Reset;
        }

        message << "\n";
    }

    return message.str();
}

std::string createErrorMessage(std::string description, std::string context,
                               std::string remedy, bool extended)
{
    return ErrorMessage("scc", ErrorSeverity::Error, description, context,
                        remedy, extended)
        .get();
}

std::string createWarningMessage(std::string description, std::string context,
                                 std::string remedy, bool extended)
{
    return ErrorMessage("scc", ErrorSeverity::Warning, description, context,
                        remedy, extended)
        .get();
}