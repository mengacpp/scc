#pragma once
#include <ostream>
#include <string>
#include <type_traits>

namespace ansi
{

// ───────────────────────────────────────────────────────────────────────────
//  Text‐formatting SGR parameters
// ───────────────────────────────────────────────────────────────────────────
enum class Style : int
{
    Reset = 0,
    Bold = 1,
    Faint = 2,
    Italic = 3,
    Underline = 4,
    SlowBlink = 5,
    RapidBlink = 6,
    Reverse = 7,
    Conceal = 8,
    CrossedOut = 9,
    DoubleUnderline = 21,
    NormalIntensity = 22,
    ItalicOff = 23,
    UnderlineOff = 24,
    BlinkOff = 25,
    ReverseOff = 27,
    Reveal = 28,
    CrossedOutOff = 29
};

enum class Color : int
{
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
    Default = 39,
    BrightBlack = 90,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93,
    BrightBlue = 94,
    BrightMagenta = 95,
    BrightCyan = 96,
    BrightWhite = 97
};

enum class Background : int
{
    Black = 40,
    Red = 41,
    Green = 42,
    Yellow = 43,
    Blue = 44,
    Magenta = 45,
    Cyan = 46,
    White = 47,
    Default = 49,
    BrightBlack = 100,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103,
    BrightBlue = 104,
    BrightMagenta = 105,
    BrightCyan = 106,
    BrightWhite = 107
};

// ───────────────────────────────────────────────────────────────────────────
//  Generic to_string for any enum-based SGR code
// ───────────────────────────────────────────────────────────────────────────
template <typename Enum, typename = std::enable_if_t<std::is_enum<Enum>::value>>
inline std::string to_string(Enum code)
{
    return "\033[" + std::to_string(static_cast<int>(code)) + "m";
}

// ───────────────────────────────────────────────────────────────────────────
//  Constrained operator<< overloads (no more ambiguity!)
// ───────────────────────────────────────────────────────────────────────────
inline std::ostream &operator<<(std::ostream &os, Style code)
{
    return os << to_string(code);
}

inline std::ostream &operator<<(std::ostream &os, Color code)
{
    return os << to_string(code);
}

inline std::ostream &operator<<(std::ostream &os, Background code)
{
    return os << to_string(code);
}

// ───────────────────────────────────────────────────────────────────────────
//  Extended 256-color and TrueColor helpers
// ───────────────────────────────────────────────────────────────────────────
inline std::string fg_color_256(int idx)
{
    return "\033[38;5;" + std::to_string(idx) + "m";
}

inline std::string bg_color_256(int idx)
{
    return "\033[48;5;" + std::to_string(idx) + "m";
}

inline std::string fg_color_rgb(int r, int g, int b)
{
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" +
           std::to_string(b) + "m";
}

inline std::string bg_color_rgb(int r, int g, int b)
{
    return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" +
           std::to_string(b) + "m";
}

} // namespace ansi
