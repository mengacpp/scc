#pragma once
#include <cstdint>

#define BIT(x) 1 << x
enum class AppFlags : unsigned
{
    None = 0,
    Help = BIT(0),
};
#undef BIT


inline AppFlags operator|(AppFlags a, AppFlags b)
{
    return static_cast<AppFlags>(static_cast<uint32_t>(a) |
                                 static_cast<uint32_t>(b));
}

inline AppFlags &operator|=(AppFlags &a, AppFlags b)
{
    return a = a | b;
}

inline AppFlags operator&(AppFlags a, AppFlags b)
{
    return static_cast<AppFlags>(static_cast<uint32_t>(a) &
                                 static_cast<uint32_t>(b));
}

inline AppFlags &operator&=(AppFlags &a, AppFlags b)
{
    return a = a & b;
}

inline AppFlags operator~(AppFlags a)
{
    return static_cast<AppFlags>(~static_cast<uint32_t>(a));
}

constexpr bool hasFlag(AppFlags value, AppFlags flag)
{
    return (static_cast<uint32_t>(value) & static_cast<uint32_t>(flag)) ==
           static_cast<uint32_t>(flag);
}
