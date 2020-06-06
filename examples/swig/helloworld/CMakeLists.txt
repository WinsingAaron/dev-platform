cmake_minimum_required(VERSION 3.5)

project(hello LANGUAGES CXX)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_SOURCE_DIR}/../../../cmake/modules
                      ${CMAKE_SOURCE_DIR}/../../../cmake/macros)

include(DevCXXFlags)

# Packages
if(WIN32)
    # XXX Qt
    list( APPEND CMAKE_PREFIX_PATH "C:/DEV_PROJECT/LIBRARY/Qt/5.12.6/msvc2017_64/lib/cmake/Qt5" )
    # XXX Python
    set(PYTHON_HOME "C:/cygwin/home/Aaron/DEV_PROJECT/LIBRARY/Digital_Asset_Library/dev-platform/python/windows10-python-2.7.15")

    set(PYTHON_INCLUDE_DIRS "${PYTHON_HOME}/include")
    set(PYTHON_LIBRARIES "${PYTHON_HOME}/libs/python27.lib")
endif()
if(UNIX)
	message(STATUS "Using cygwin")
	# XXX Qt
    list( APPEND CMAKE_PREFIX_PATH "/cygdrive/c/DEV_PROJECT/LIBRARY/Qt/5.12.6/msvc2017_64/lib/cmake/Qt5")	# mingw73_64 | msvc2017_64
    set(ENV{PATH} "${PYTHON_HOME}:$PATH")

#    # XXX Python with custom
#    set(W_PYTHON_HOME "/home/Aaron/DEV_PROJECT/LIBRARY/Digital_Asset_Library/dev-platform/python/windows10-python-2.7.15")
#    set(L_PYTHON_HOME "/home/Aaron/DEV_PROJECT/LIBRARY/Digital_Asset_Library/dev-platform/python/centos7-python-2.7.17")
#
#    set(PYTHON_INCLUDE_DIRS "${L_PYTHON_HOME}/include/python2.7")
#    set(PYTHON_LIBRARIES "${L_PYTHON_HOME}/lib/libpython2.7.a")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
if(UNIX)
	find_package(Python2 REQUIRED Interpreter Development)
	find_package(PythonLibs REQUIRED)
endif()

if(ANDROID)
#  add_library(${PROJECT_NAME} SHARED
#    hello.cpp
#  )
else()
#  add_executable(QtCMakeProject
#    main.cpp
#    widget.cpp
#    widget.h
#  )
    add_library(${PROJECT_NAME} SHARED
        hello.cpp
        print_hello_wrap.cxx
    )
endif()
# ${PYTHON_LIBRARIES}
#
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE 
	# Qt5::Widgets
    ${PYTHON_LIBRARIES}
)

set_target_properties(hello PROPERTIES PREFIX "")
set_target_properties(hello PROPERTIES OUTPUT_NAME "_hello")
set_target_properties(hello PROPERTIES SUFFIX ".pyd")
# set_target_properties(hello PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../)

