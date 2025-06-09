#include <iostream>

#include "../include/xorstr.hpp"

auto main() -> int
{
    using namespace n0rthern_light::xorstr;

    {
        const auto encrypted = EncryptedString{ "very-secret-data [char]" };
        const auto decrypted = encrypted.decrypt();

        std::cout << decrypted.constStr() << '\n';
    }

    {
        const auto encrypted = EncryptedString{ L"very-secret-data [wchar_t]" };
        const auto decrypted = encrypted.decrypt();

        std::wcout << decrypted.constStr() << '\n';
    }

    {
        const auto encrypted = EncryptedString{ u8"very-secret-data [char8_t]" };
        const auto decrypted = encrypted.decrypt();

        for (char8_t chr : decrypted) {
            std::cout << static_cast<char>(chr);
        }
        std::cout << '\n';
    }

    {
        const auto encrypted = EncryptedString{ u"very-secret-data [char16_t]" };
        const auto decrypted = encrypted.decrypt();

        for (char16_t chr : decrypted) {
            std::wcout << static_cast<wchar_t>(chr);
        }
        std::wcout << '\n';
    }

    {
        const auto encrypted = EncryptedString{ U"very-secret-data [char32_t]" };
        const auto decrypted = encrypted.decrypt();

        for (char32_t chr : decrypted) {
            std::wcout << static_cast<wchar_t>(chr);
        }
        std::wcout << '\n';
    }

    return 0;
}

