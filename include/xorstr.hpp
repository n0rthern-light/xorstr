#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_BEGIN) && !defined(N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_END)

  #if defined(__clang__)
    #define N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_BEGIN __attribute__((optnone))
    #define N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_END

  #elif defined(__GNUC__)
    #define N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_BEGIN __attribute__((optimize("O0")))
    #define N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_END

  #elif defined(_MSC_VER)
    #define N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_BEGIN #pragma(optimize("", off))
    #define N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_END   #pragma(optimize("", on))

  #else
    #define N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_BEGIN
    #define N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_END
  #endif

#endif

namespace n0rthern_light::xorstr
{
inline constexpr std::size_t ENCRYPTION_KEY_SIZE = 32;
inline constexpr std::array<uint8_t, ENCRYPTION_KEY_SIZE> ENCRYPTION_KEY = {
    0x3A, 0x7F, 0xB2, 0x4C, 0xE1, 0x09, 0xD7, 0x5A,
    0x8C, 0x13, 0x6E, 0x21, 0x99, 0xF3, 0x42, 0xAF,
    0x1B, 0x77, 0xC5, 0x36, 0xDE, 0x60, 0x84, 0xEA,
    0x58, 0x2D, 0x91, 0xCE, 0x0A, 0xF9, 0x6B, 0x34
};

template<typename T>
constexpr T xorCharacter(T value, std::size_t index) {
    T xorValue = 0;

    for (auto i = 0u; i < sizeof(T); ++i) {
        xorValue |= T(ENCRYPTION_KEY[(index + i) % ENCRYPTION_KEY_SIZE]) << (8 * i);
    }

    return value ^ xorValue;
}

template<typename T, std::size_t N>
struct PlainString
{
    std::array<T, N + 1> data_;

    N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_BEGIN
    PlainString (const T* str) noexcept 
    {
        data_ = { 0 };
        for (auto i = 0ul; i < N; ++i) {
            volatile const auto v = xorCharacter<T>(str[i], i);
            data_[i] = v;
        }
    }
    N0RTHERN_LIGHT_XORSTR__NO_OPTIMIZE_END

    auto constStr() const noexcept -> const T*
    {
        return static_cast<const T*>(data_.data());
    }

    auto begin() const noexcept
    {
        return data_.begin();
    }

    auto end() const noexcept
    {
        return data_.end();
    }
};

template<typename T, std::size_t N>
struct EncryptedString
{
    std::array<T, N> data_;

    consteval EncryptedString(const T (&str)[N]) noexcept
    {
        data_ = { 0 };
        for (auto i = 0ul; i < N; ++i) {
            data_[i] = xorCharacter<T>(str[i], i);
        }
    }

    auto decrypt() const noexcept
    {
        return PlainString<T, N> { data_.data() };
    }
};
}
