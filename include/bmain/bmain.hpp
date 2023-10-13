#pragma once
#ifndef BETTER_MAIN_HPP
#define BETTER_MAIN_HPP

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || __cplusplus >= 202002L)
#define BETTER_MAIN_CPP20 1
#else
#define BETTER_MAIN_CPP20 0
#endif

#if BETTER_MAIN_CPP20
#include <span>
#else
#include <vector>
#endif
#include <string>

using bmain_args_string_type = std::string;

#if BETTER_MAIN_CPP20
using bmain_args = std::span<const bmain_args_string_type>;
#else
using bmain_args = const std::vector<bmain_args_string_type>&;
#endif

int bmain(bmain_args args);

#endif // BETTER_MAIN_HPP