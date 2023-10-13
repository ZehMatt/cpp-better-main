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
