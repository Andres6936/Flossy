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


### Support to CPM (Content Package Manager)

# This CMake allow ddd dependencies (Like Gradle, Maven, Pip, etc ...)
# For more information see: https://github.com/TheLartians/CPM.cmake
INCLUDE(CMakeModules/CPM.cmake)

# Creating installable CMake scripts always requires a large amount
# of boilerplate code to get things working. This small script should
# simplify the CMake packaging process into a single, easy-to-use command.
CPMAddPackage(
        NAME PackageProject.cmake
        GITHUB_REPOSITORY TheLartians/PackageProject.cmake
        VERSION 1.2
)

packageProject(
        NAME Flossy
        VERSION ${PROJECT_VERSION}
        BINARY_DIR ${PROJECT_BINARY_DIR}
        INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Include
        INCLUDE_DESTINATION Include
        DEPENDENCIES ""
)


### Support to Test

INCLUDE_DIRECTORIES(Include)

ADD_EXECUTABLE(FlossyTest Test/TestFlossy.cpp)
