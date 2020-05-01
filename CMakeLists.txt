CMAKE_MINIMUM_REQUIRED(VERSION 3.15 FATAL_ERROR)

PROJECT(Flossy VERSION 2020.4 LANGUAGES CXX)

#[[ This sets an header-only project.

Don't worry, no actual binaries will be generated if you should try and build it.
The command <SET_TARGET_PROPERTIES> is there because CMake will otherwise complain
that it cannot infer the target language from .hpp files only.
]]
ADD_LIBRARY(Flossy STATIC Include/Flossy/Flossy.hpp)
SET_TARGET_PROPERTIES(Flossy PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 17)


### Support to Command <make install>

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
INCLUDE(GNUInstallDirs)


# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
TARGET_INCLUDE_DIRECTORIES(Flossy
        PUBLIC
        $<INSTALL_INTERFACE:Include>
        )

# 'make install' to the correct locations (provided by GNUInstallDirs).
INSTALL(TARGETS Flossy
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )

# This is for Windows
INSTALL(DIRECTORY Include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


INCLUDE_DIRECTORIES(Include)

ADD_EXECUTABLE(FlossyTest Test/TestFlossy.cpp)
