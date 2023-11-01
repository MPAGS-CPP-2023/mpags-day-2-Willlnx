cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 1.0.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable (mpags-cipher 
                mpags-cipher.cpp
                MPAGSCipher/TransformChar.cpp
                MPAGSCipher/processCommandLine.cpp
                )

target_include_directories(mpags-cipher 
                            PRIVATE MPAGSCipher
                            )

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_EXTENSIONS OFF)

target_compile_features(mpags-cipher 
    PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization
    )


