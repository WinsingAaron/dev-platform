cmake_minimum_required(VERSION 3.5)

project(hello LANGUAGES CXX)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_SOURCE_DIR}/../../../cmake/modules
                      ${CMAKE_SOURCE_DIR}/../../../cmake/macros)

include(DevCXXFlags)

# Packages
if(WIN32)
    # XXX Python
    set(PYTHON_HOME "C:/cygwin/home/Aaron/DEV_PROJECT/LIBRARY/Digital_Asset_Library/dev-platform/python/windows10-python-2.7.15")

    set(PYTHON_INCLUDE_DIRS "${PYTHON_HOME}/include")
    set(PYTHON_LIBRARIES "${PYTHON_HOME}/libs/python27.lib")
endif()
if(UNIX)
    set(ENV{PATH} "${PYTHON_HOME}:$PATH")

    # UNTEST
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(${PROJECT_NAME} SHARED
    hello.cpp
    print_hello_wrap.cxx
)

include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PYTHON_LIBRARIES}
)

set_target_properties(hello PROPERTIES PREFIX "")
set_target_properties(hello PROPERTIES OUTPUT_NAME "_hello")
set_target_properties(hello PROPERTIES SUFFIX ".pyd")
set_target_properties(hello PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../)

