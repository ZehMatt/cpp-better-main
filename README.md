# cpp-better-main
Better C++ main
```cpp
#include <bmain/bmain.hpp>
#include <iostream>

// This is the entry point of your application. Arguments are passed in as a vector/span of strings with UTF-8
// encoding.
int bmain(bmain_args args)
{
    for (const auto& arg : args)
    {
        std::cout << arg << std::endl;
    }
    return 0;
}
```
# Why
On Windows the `main()` function uses ANSI for the arguments, using `wmain()` is not great as having to deal with `wchar_t` type is not well supported on other platforms and when creating cross platform applications having to deal with this is pretty annoying, other platforms typically have UTF-8 encoded strings for the arguments, to reduce the boilerplate code I opted to create this to just have one entry point that has always UTF-8 strings, also instead of the traditional C style `argc, argv` it uses vector or span depending on the cpp language version being used.

# Usage
The easiest way to use this is using CMake, simply add `better-main` to your targets linked libraries, if you are not using CMake you can just copy the source files into the project where you wish to use it. After that modify your `main(int argc, const char* argv[])` to `int bmain(bmain_args args)`, that's it. Be aware that this should not be used for static or shared libraries and will likely break your build.

On Windows the arguments will be converted to hold UTF-8 encoded strings, other platforms usually already pass the arguments UTF-8 encoded.

# Overhead
I acknowledge that there is a slight performance overhead due to the use of `std::vector` and `std::string`. However, on the Windows platform, it is necessary to convert the arguments to UTF-8 encoding, which requires some additional memory for storing the converted strings. In my view, this is the most compatible choice, and the minor overhead is typically negligible in most scenarios. Furthermore, I opted for this approach to maintain uniformity. This approach should work with even with older language versions like C++98.
