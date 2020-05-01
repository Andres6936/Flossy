CMAKE_MINIMUM_REQUIRED(VERSION 3.15 FATAL_ERROR)

PROJECT(Flossy VERSION 2020.4 LANGUAGES CXX)

#[[ This sets an header-only project.

Don't worry, no actual binaries will be generated if you should try and build it.
The command <SET_TARGET_PROPERTIES> is there because CMake will otherwise complain
that it cannot infer the target language from .hpp files only.
]]
ADD_LIBRARY(Flossy STATIC Include/Flossy.hpp)
SET_TARGET_PROPERTIES(Flossy PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 17)

INCLUDE_DIRECTORIES(Include)

ADD_EXECUTABLE(FlossyTest Test/TestFlossy.cpp)
