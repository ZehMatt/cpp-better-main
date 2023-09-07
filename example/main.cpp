#include <vector>
#include <string>
#include <iostream>

int bmain(const std::vector<std::string>& args)
{
    for (const auto& arg : args)
    {
        std::cout << arg << std::endl;
    }
    return 0;
}