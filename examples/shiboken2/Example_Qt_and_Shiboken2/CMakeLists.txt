cmake_minimum_required(VERSION 3.12)
cmake_policy(VERSION 3.12)
# ************************************************************************************************************START
if (POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif ()

project(Shiboken2-Qt-Example)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 5.12 REQUIRED COMPONENTS Core Gui Widgets)
# ************************************************************************************************************END
# ************************************************************************************************************START
# get_target_property(QtCore_location Qt5::Core LOCATION)
# get_filename_component(QtCore_libdir ${QtCore_location} DIRECTORY)
# ************************************************************************************************************END
set(CMAKE_AUTOMOC ON)

set(sample_library "libexamplebinding")
set(bindings_library "Shiboken2QtExample")
set(wrapped_header ${CMAKE_SOURCE_DIR}/bindings.h)
set(typesystem_file ${CMAKE_SOURCE_DIR}/bindings.xml)
set(generated_sources
    ${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/qobjectwithenum_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/shiboken2qtexample_module_wrapper.cpp)

if(NOT python_interpreter)
    find_program(python_interpreter "python")
endif()
find_package(Python2 REQUIRED COMPONENTS Interpreter Development)
set(PYSIDE2_DIR ${Python2_SITELIB}/PySide2)

macro(pyside2_config option output_var)
    if(${ARGC} GREATER 2)
        set(is_list ${ARGV2})
    else()
        set(is_list "")
    endif()

    execute_process(
      COMMAND ${python_interpreter} "${PYSIDE2_DIR}/examples/utils/pyside2_config.py"
		${option}
      OUTPUT_VARIABLE ${output_var}
      OUTPUT_STRIP_TRAILING_WHITESPACE)

    if ("${${output_var}}" STREQUAL "")
        message(FATAL_ERROR "Error: Calling pyside2_config.py ${option} returned no output.")
    endif()
    if(is_list)
        string (REPLACE " " ";" ${output_var} "${${output_var}}")
    endif()
endmacro()

pyside2_config(--shiboken2-module-path shiboken2_module_path)
pyside2_config(--shiboken2-generator-path shiboken2_generator_path)
pyside2_config(--python-include-path python_include_dir)
pyside2_config(--shiboken2-generator-include-path shiboken_include_dir 1)
pyside2_config(--shiboken2-module-shared-libraries-cmake shiboken_shared_libraries 0)
#pyside2_config(--pyside2-shared-libraries-cmake pyside2_link 0)
pyside2_config(--python-link-flags-cmake python_linking_data)
# ************************************************************************************************************START
pyside2_config(--pyside2-path PYSIDE2_PATH)
pyside2_config(--pyside2-include-path PYSIDE2_INCLUDE_DIR 1)
pyside2_config(--pyside2-shared-libraries-cmake PYSIDE2_SHARED_LIBRARIES 0)
# ************************************************************************************************************END
set(shiboken_path "${shiboken2_generator_path}/shiboken2${CMAKE_EXECUTABLE_SUFFIX}")
if(NOT EXISTS ${shiboken_path})
    message(FATAL_ERROR "Shiboken executable not found at path: ${shiboken_path}")
endif()
# ************************************************************************************************************START
get_property(QT_CORE_INCLUDE_DIRS TARGET Qt5::Core PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
get_property(QT_GUI_INCLUDE_DIRS TARGET Qt5::Gui PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
get_property(QT_WIDGETS_INCLUDE_DIRS TARGET Qt5::Widgets PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
set(QT_INCLUDE_DIRS ${QT_CORE_INCLUDE_DIRS} ${QT_GUI_INCLUDE_DIRS} ${QT_WIDGETS_INCLUDE_DIRS})
set(INCLUDES "")
foreach (INCLUDE_DIR ${QT_INCLUDE_DIRS})
    list(APPEND INCLUDES "-I${INCLUDE_DIR}")
endforeach ()
include_directories(${QT_INCLUDE_DIRS})
set(PYSIDE2_ADDITIONAL_INCLUDES "")
foreach (INCLUDE_DIR ${PYSIDE2_INCLUDE_DIR})
    list(APPEND PYSIDE2_ADDITIONAL_INCLUDES "${INCLUDE_DIR}/QtCore")
    list(APPEND PYSIDE2_ADDITIONAL_INCLUDES "${INCLUDE_DIR}/QtGui")
    list(APPEND PYSIDE2_ADDITIONAL_INCLUDES "${INCLUDE_DIR}/QtWidgets")
endforeach ()
# ************************************************************************************************************END
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
# ************************************************************************************************************START
set(CMAKE_INSTALL_RPATH ${shiboken2_module_path} ${CMAKE_CURRENT_SOURCE_DIR} ${PYSIDE2_PATH})
# set(CMAKE_INSTALL_RPATH ${shiboken2_module_path} ${CMAKE_CURRENT_SOURCE_DIR} ${QtCore_libdir})
# ************************************************************************************************************END
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(${sample_library}_sources qobjectwithenum.cpp)
add_library(${sample_library} SHARED ${${sample_library}_sources})
target_link_libraries(${sample_library} Qt5::Core)
set_property(TARGET ${sample_library} PROPERTY PREFIX "")

get_target_property(qtcore_lib_includes Qt5::Core INTERFACE_INCLUDE_DIRECTORIES)
list(JOIN qtcore_lib_includes ";-I" lib_includes)
set(lib_includes "-I${lib_includes}")

target_compile_definitions(${sample_library} PRIVATE BINDINGS_BUILD)
# ************************************************************************************************************START
target_include_directories(${sample_library} PRIVATE ${python_include_dir})
target_include_directories(${sample_library} PRIVATE ${shiboken_include_dir})
target_include_directories(${sample_library} PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(${sample_library} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
#target_include_directories(${sample_library} PRIVATE ${PYSIDE2_PATH})
target_include_directories(${sample_library} PRIVATE ${QT_INCLUDE_DIRS})
target_include_directories(${sample_library} PRIVATE ${PYSIDE2_ADDITIONAL_INCLUDES})
# ************************************************************************************************************END

set(shiboken_options --generator-set=shiboken --enable-parent-ctor-heuristic
    --enable-return-value-heuristic --use-isnull-as-nb_nonzero
    --avoid-protected-hack
    --enable-pyside-extensions
    ${lib_includes}
    -I${CMAKE_SOURCE_DIR}
    -T${CMAKE_SOURCE_DIR}
    -T${PYSIDE2_DIR}/typesystems/
    --output-directory=${CMAKE_CURRENT_BINARY_DIR}
    )

set(generated_sources_dependencies ${wrapped_header} ${typesystem_file})

add_custom_command(OUTPUT ${generated_sources}
                    COMMAND ${shiboken_path}
                    ${shiboken_options} ${wrapped_header} ${typesystem_file}
                    DEPENDS ${generated_sources_dependencies}
                    IMPLICIT_DEPENDS CXX ${wrapped_header}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Running generator for ${typesystem_file}.")

set(${bindings_library}_sources ${generated_sources})

add_library(${bindings_library} MODULE ${${bindings_library}_sources})
# ************************************************************************************************************START
target_include_directories(${bindings_library} PRIVATE ${python_include_dir})
# target_include_directories(${bindings_library} PRIVATE ${PYSIDE2_DIR}/include/)
# target_include_directories(${bindings_library} PRIVATE ${PYSIDE2_DIR}/include/QtCore)
target_include_directories(${bindings_library} PRIVATE ${shiboken_include_dir})
target_include_directories(${bindings_library} PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(${bindings_library} PRIVATE ${shiboken_shared_libraries})
target_link_libraries(${bindings_library} PRIVATE ${sample_library})

target_compile_definitions(${bindings_library} PRIVATE LIBSHIBOKEN_EXPORTS)

target_include_directories(${sample_library} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${bindings_library} PRIVATE ${PYSIDE2_PATH})
target_include_directories(${bindings_library} PRIVATE ${PYSIDE2_INCLUDE_DIR})
target_include_directories(${bindings_library} PRIVATE ${QT_INCLUDE_DIRS})
target_include_directories(${bindings_library} PRIVATE ${PYSIDE2_ADDITIONAL_INCLUDES})
target_link_libraries(${bindings_library} PRIVATE Qt5::Widgets)
#target_link_libraries(${bindings_library} PRIVATE Qt5::Core)
#target_link_libraries(${bindings_library} PRIVATE Qt5::Gui)
#target_link_libraries(${bindings_library} PRIVATE ${PYSIDE2_PATH})
target_link_libraries(${bindings_library} PRIVATE ${PYSIDE2_SHARED_LIBRARIES})#pyside2.abi3.lib

# target_link_libraries(${bindings_library} PRIVATE ${pyside2_link})
# ************************************************************************************************************END

set_property(TARGET ${bindings_library} PROPERTY PREFIX "")
# ************************************************************************************************************START
#set_property(TARGET ${bindings_library} PROPERTY OUTPUT_NAME
#             "${bindings_library}${PYTHON_EXTENSION_SUFFIX}")
set_property(TARGET ${bindings_library} PROPERTY OUTPUT_NAME_DEBUG#OUTPUT_NAME #OUTPUT_NAME_DEBUG
             "${bindings_library}${PYTHON_EXTENSION_SUFFIX}")
# ************************************************************************************************************END
# ************************************************************************************************************START
if (WIN32)
    set_property(TARGET ${bindings_library} PROPERTY SUFFIX ".pyd")
endif ()

if (WIN32)
    list(GET python_linking_data 0 python_libdir)
    list(GET python_linking_data 1 python_lib)

    find_library(python_link_flags ${python_lib} PATHS ${python_libdir} HINTS ${python_libdir})
    target_link_libraries(${bindings_library} PRIVATE ${python_link_flags})
    message("python_libdir: ${python_libdir}")
    message("python_link_flags: ${python_link_flags}")
    # =========================================================================================
    # !!! (The section below is deployment related, so in a real world application you will
    # want to take care of this properly (this is simply to eliminate errors that users usually
    # encounter.
    # =========================================================================================
    # Circumvent some "#pragma comment(lib)"s in "include/pyconfig.h" which might force to link
    # against a wrong python shared library.

    set(python_versions_list 3 32 33 34 35 36 37 38)
    set(python_additional_link_flags "")
    foreach(ver ${python_versions_list})
        set(python_additional_link_flags
                "${python_additional_link_flags} /NODEFAULTLIB:\"python${ver}_d.lib\"")
        set(python_additional_link_flags
                "${python_additional_link_flags} /NODEFAULTLIB:\"python${ver}.lib\"")
    endforeach()

    set_target_properties(${bindings_library}
            PROPERTIES LINK_FLAGS "${python_additional_link_flags}")

    # Add custom target to hard-link shiboken shared libraries into the build folder, so that
    # the user doesn't have to set the PATH manually to point to the PySide2 package.
    foreach(library_path ${shiboken_shared_libraries})
        string(REGEX REPLACE ".lib$" ".dll" library_path ${library_path})
        get_filename_component(base_name ${library_path} NAME)
        file(TO_NATIVE_PATH ${library_path} source_path)
        file(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/${base_name}" dest_path)
        add_custom_command(OUTPUT "${base_name}"
                COMMAND mklink /H "${dest_path}" "${source_path}"
                DEPENDS ${library_path}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Creating hardlink to shiboken shared library ${base_name}")

        # Fake target that depends on the previous one, but has special ALL keyword, which means
        # it will always be executed.
        add_custom_target("fake_${base_name}" ALL DEPENDS ${base_name})
    endforeach()
endif()
# ************************************************************************************************************END

install(TARGETS ${bindings_library} ${sample_library}
        LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
        RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
        )