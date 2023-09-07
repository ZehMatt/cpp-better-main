cmake_minimum_required(VERSION 3.12)
project(better-main
	LANGUAGES
		CXX
)

option(BETTER_MAIN_CONVERT_TO_UTF8 "Converts the arguments to hold UTF8 encoded bytes, this is only relevant for MSVC builds." ON)
option(BETTER_MAIN_BUILD_EXAMPLE "Builds the example." OFF)

set(IS_ROOT_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(IS_ROOT_PROJECT ON)
endif()

# better-main
add_library(better-main INTERFACE)
target_sources(better-main
    INTERFACE
    ${CMAKE_SOURCE_DIR}/src/better-main.cpp
)

if(BETTER_MAIN_CONVERT_TO_UTF8)
    target_compile_definitions(better-main INTERFACE "BETTER_MAIN_CONVERT_TO_UTF8=1")
endif()

# example
if(BETTER_MAIN_BUILD_EXAMPLE OR IS_ROOT_PROJECT)
    add_executable(better-main-example
        example/main.cpp
    )
    target_link_libraries(better-main-example
        better-main
    )
endif()
