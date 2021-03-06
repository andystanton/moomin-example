#
# Project Properties
#
CMAKE_MINIMUM_REQUIRED (VERSION 2.8.12)
PROJECT (moomin-example)
SET (APPLICATION_NAME "Moomin Example")
SET (APPLICATION_CODENAME "${PROJECT_NAME}")
SET (APPLICATION_COPYRIGHT_YEARS "2014")
SET (APPLICATION_VERSION_MAJOR 1)
SET (APPLICATION_VERSION_MINOR 0)
SET (APPLICATION_VERSION_PATCH 1)
SET (APPLICATION_VERSION_TYPE SNAPSHOT)
SET (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")
SET (APPLICATION_ID "${APPLICATION_VENDOR_ID}.${PROJECT_NAME}")


# Copy files from source directory to destination directory, substituting any
# variables.  Create destination directory if it does not exist.

macro(configure_files srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    @ONLY)
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(configure_files)

# Copy directory only

macro(copy_files srcDir destDir)
    message(STATUS "Copying directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Copying file ${templateFile}")
            file(COPY ${srcTemplatePath} DESTINATION ${destDir})
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(copy_files)

#
# Debugging Options
#
SET (CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 for release

#
# Project Output Paths
#
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

#
# Project Search Paths
#
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
INCLUDE_DIRECTORIES("${MAINFOLDER}/include")

# set compiler warnings
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Werror -Wfloat-equal -Wno-unused-parameter -Wno-unknown-pragmas")

#
# Enable C++11
#
IF(CMAKE_COMPILER_IS_GNUCXX)
    IF(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7")
        MESSAGE(FATAL_ERROR "Compiler does not support C++11")
    ELSE()
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    ENDIF()
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    ENDIF()
ELSEIF(MSVC)
    # On by default
ELSE()
    MESSAGE(FATAL_ERROR "Compiler not supported")
ENDIF()

#
# Locate Project Prerequisites
#

# MOOMIN

# add subdirectory
add_subdirectory(lib/moomin)
set(MOOMIN_INCLUDE_PATH "${MAINFOLDER}/lib/moomin/include")

# GLFW

# disable unnecessary glfw targets
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)

# add subdirectory
add_subdirectory(lib/glfw)
set(GLFW_INCLUDE_PATH "${MAINFOLDER}/lib/glfw/include")

# GLEW

OPTION( glew-cmake_BUILD_SHARED "Build the shared glew library" OFF)
add_subdirectory(lib/glew-cmake)
set(GLEW_INCLUDE_PATH "${MAINFOLDER}/lib/glew-cmake/include")

# GLM

set(GLM_INCLUDE_PATH "${MAINFOLDER}/lib/glm")

# GLM

set(GLM_INCLUDE_PATH "${MAINFOLDER}/lib/glm")

#
# Add Build Targets
#
ADD_SUBDIRECTORY(src)

# Test Includes

set(GTEST_INCLUDE_PATH "${MAINFOLDER}/lib/moomin/lib/gtest/include")
set(GMOCK_INCLUDE_PATH "${MAINFOLDER}/lib/moomin/lib/gmock/include")
set(BANDIT_INCLUDE_PATH "${MAINFOLDER}/lib/moomin/lib/bandit")

#
# Add Test Targets
#
enable_testing()
ADD_SUBDIRECTORY(test)


#
# Add Install Targets
#
IF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
    INSTALL(DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}" DESTINATION "include")
ENDIF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
