#include "bmain.hpp"

#include <vector>

using bmain_args_storage = std::vector<bmain_args_string_type>;

#ifdef WIN32
#    ifndef WIN32_LEAN_AND_MEAN
#        define WIN32_LEAN_AND_MEAN
#    endif
#    include <windows.h>
#    include <shellapi.h>

int main()
{
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv != nullptr)
    {
        bmain_args_storage args;
        for (int i = 0; i < argc; ++i)
        {
            const auto* srcArg = argv[i];
            const auto argLen = wcslen(srcArg);

            // Convert to UTF8
            const auto sizeRequired = WideCharToMultiByte(CP_UTF8, 0, srcArg, argLen, nullptr, 0, nullptr, nullptr);
            if (sizeRequired == 0)
            {
                fprintf(stderr, "Unable to convert argument to UTF8 (%08X).\n", GetLastError());
                return -1;
            }

            bmain_args_string_type utf8Arg(sizeRequired, 0);
            WideCharToMultiByte(CP_UTF8, 0, srcArg, argLen, (char*)utf8Arg.data(), sizeRequired, NULL, NULL);
            args.push_back(std::move(utf8Arg));
        }

        LocalFree(argv);
        return bmain(args);
    }
    else
    {
        wprintf(L"CommandLineToArgvW failed\n");
        return 0;
    }
}

#else

int main(int argc, const char* argv[])
{
    bmain_args_storage args;
    for (int i = 0; i < argc; ++i)
    {
        args.push_back(argv[i]);
    }
    return bmain(args);
}

#endif