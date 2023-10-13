cmake_minimum_required(VERSION 3.15)
project(better-main
	LANGUAGES
		CXX
)

option(BETTER_MAIN_BUILD_EXAMPLE "Builds the example." OFF)

set(IS_ROOT_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(IS_ROOT_PROJECT ON)
endif()

# better-main
add_library(better-main STATIC)
add_library(better-main::better-main ALIAS better-main)

target_sources(better-main PRIVATE 
    src/bmain.cpp
    include/bmain/bmain.hpp
)

target_include_directories(better-main
    PRIVATE
        include/bmain
    PUBLIC
        include
)

# example
if(BETTER_MAIN_BUILD_EXAMPLE OR IS_ROOT_PROJECT)
    add_executable(better-main-example
        example/main.cpp
    )
    target_link_libraries(better-main-example
        better-main::better-main
    )
endif()
