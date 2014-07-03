#
# Project Properties
#
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (moomin-example)
SET (APPLICATION_NAME "Moomin Example")
SET (APPLICATION_CODENAME "${PROJECT_NAME}")
SET (APPLICATION_COPYRIGHT_YEARS "2014")
SET (APPLICATION_VERSION_MAJOR 1)
SET (APPLICATION_VERSION_MINOR 0)
SET (APPLICATION_VERSION_PATCH 0)
SET (APPLICATION_VERSION_TYPE SNAPSHOT)
SET (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")
SET (APPLICATION_VENDOR_ID "com.cyniq")
SET (APPLICATION_VENDOR_NAME "Cyniq")
SET (APPLICATION_VENDOR_URL "cyniq.com")
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
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Werror -Wfloat-equal -Wno-unused-parameter")

# set c++ 11

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    endif ()
elseif (MSVC)
    # On by default
endif ()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++")

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