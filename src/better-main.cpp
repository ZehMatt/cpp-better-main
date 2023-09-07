#include <vector>
#include <string>

using args_string_type = std::string;
using args_storage_type = std::vector<args_string_type>;
using args_view_type = const args_storage_type&;

int bmain(args_view_type args);

#ifdef WIN32

#if defined(BETTER_MAIN_CONVERT_TO_UTF8) && BETTER_MAIN_CONVERT_TO_UTF8
#    ifndef WIN32_LEAN_AND_MEAN
#        define WIN32_LEAN_AND_MEAN
#    endif
#    include <windows.h>

int wmain(int argc, const wchar_t* argv[])
#else
int main(int argc, const char* argv[])
#endif
{
    args_storage_type args;
    for (int i = 0; i < argc; ++i)
    {
        const auto* srcArg = argv[i];
#if defined(BETTER_MAIN_CONVERT_TO_UTF8) && BETTER_MAIN_CONVERT_TO_UTF8
        const auto argLen = wcslen(srcArg);

        // Convert to UTF8
        const auto sizeRequired = WideCharToMultiByte(CP_UTF8, 0, srcArg, argLen, nullptr, 0, nullptr, nullptr);
        if (sizeRequired == 0)
        {
            fprintf(stderr, "Unable to convert argument to UTF8 (%08X).\n", GetLastError());
            return -1;
        }

        args_string_type utf8Arg(sizeRequired, 0);
        WideCharToMultiByte(CP_UTF8, 0, srcArg, argLen, (char*)utf8Arg.data(), sizeRequired, NULL, NULL);
        args.push_back(std::move(utf8Arg));
#else
        args.emplace_back(srcArg);
#endif
    }

    return bmain(std::move(args));
}

#else

int main(int argc, const char* argv[])
{
    args_storage_type args;
    for (int i = 0; i < argc; ++i)
    {
        args.push_back(argv[i]);
    }
    return bmain(std::move(args));
}

#endif