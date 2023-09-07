# cpp-better-main
Better C++ main
```cpp
// Use this instead of main(...)
int bmain(const std::vector<std::string>& args)
{
    for (const auto& arg : args)
    {
        std::cout << arg << std::endl;
    }
    return 0;
}
```

# Usage
The easiest way to use this is using CMake, simply add `better-main` to your targets linked libraries, if you are not using CMake you can just copy better-main.cpp into the project where you wish to use it. After that modify your `main(int argc, const char* argv[])` to `int bmain(const std::vector<std::string>& args)`, that's it. 

On Windows the arguments will be converted to hold UTF8 encoded strings, other platforms usually already pass the arguments UTF8 encoded.

# Overhead
I acknowledge that there is a slight performance overhead due to the use of `std::vector` and `std::string`. However, on the Windows platform, it is necessary to convert the arguments to UTF8 encoding, which requires some additional memory for storing the converted strings. In my view, this is the most compatible choice, and the minor overhead is typically negligible in most scenarios. Furthermore, I opted for this approach to maintain uniformity and compatibility across different C++ language versions, avoiding the need for multiple function signatures based on language versions. This approach should remain functional even with older language versions like C++98.
