## Introduction
Header only library for compile-time encrypted strings.

The provided library should encrypt sensitive strings - such as API URLs in a client application - and decrypt them only at runtime.

The library supports all modern C++ string encodings, including narrow strings, wide strings, UTF-8, UTF-16, and UTF-32.

## Prerequisites
Because of the use of `consteval` for the constructor of `EncryptedString`, `C++20` is required at minimum.

If you removed or replaced `consteval` with `constexpr`, the minimum version would drop to `C++17` (because of inline constexpr variables). But due to the fact that for proper encryption the string MUST be evaluated at compile-time, the `consteval` is a lot safer bet.

The compiler optimization level can be set to maximum, such as `-O3` for the `clang++` compiler, as shown in the example. However, it is important to note that for this library's encryption mechanism to work correctly, the decryption function MUST NOT be optimized. This is because compilers often silently evaluate it at compile time, whereas runtime evaluation is required. To ensure proper runtime decryption, compiler optimizations are explicitly disabled for the decrypt function. This approach SHOULD be compatible with `clang`, `gcc`, and `msvc` compilers, although the code has only been tested with clang so far.

## How to use
1. Include [`include/xorstr.hpp`](include/xorstr.hpp). in your project.
2. Change the cipher key to your own.
3. Create compile-time encrypted strings.

```cpp
#include "xorstr.hpp"

auto main() -> int
{
    using namespace n0rthern_light::xorstr;

    {
        const auto encrypted = EncryptedString{ "very-secret-data" };
        const auto decrypted = encrypted.decrypt();

        std::cout << decrypted.constStr() << '\n';
    }

    return 0;
}
```
## Example
See example usage in [`example/main.cpp`](example/main.cpp).

```sh
cd example
./compile_and_test.sh
```

Output:
```sh
Compiling as example
Done.
---------------------------------------------
Output:
very-secret-data [char]
very-secret-data [wchar_t]
very-secret-data [char8_t]
very-secret-data [char16_t]
very-secret-data [char32_t]
---------------------------------------------
Searching secret "very-secret-data" string in the binary example:
0 results found.
=============================================
[OK] Strings are encrypted inside the binary
```
