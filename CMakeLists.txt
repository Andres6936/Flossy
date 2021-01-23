CMAKE_MINIMUM_REQUIRED(VERSION 3.1 FATAL_ERROR)

PROJECT(Flossy VERSION 2021.1 LANGUAGES CXX)

### Support to Command <make install>

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
INCLUDE(GNUInstallDirs)

#[[ This sets an header-only project.

Don't worry, no actual binaries will be generated if you should try and build it.
The command <SET_TARGET_PROPERTIES> is there because CMake will otherwise complain
that it cannot infer the target language from .hpp files only.
]]
ADD_LIBRARY(Flossy INTERFACE)
# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
TARGET_INCLUDE_DIRECTORIES(Flossy INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

# Support to compiler on mode C++ 17 standard.
TARGET_COMPILE_FEATURES(Flossy INTERFACE cxx_std_17)

# 'make install' to the correct locations (provided by GNUInstallDirs).
INSTALL(TARGETS Flossy
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )

# This is for install the headers in correct location
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/Include/ DESTINATION include)



### Support to Test

INCLUDE_DIRECTORIES(Include)

ADD_EXECUTABLE(FlossyTest Test/TestFlossy.cpp)
TARGET_LINK_LIBRARIES(FlossyTest PRIVATE Flossy)
