cmake_minimum_required(VERSION 3.26)
project(template VERSION 1.0.0.0 LANGUAGES C CXX)

# add source files to this variable
set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/template.cpp")

set(LIB_OBJ    ${PROJECT_NAME}_obj)
set(LIB_SHARED ${PROJECT_NAME}_shared)
set(LIB_STATIC ${PROJECT_NAME})

# using an intermediary object library format prevents the code from being
# compiled twice if both a shared and a static lib are built from the same source
add_library(${LIB_OBJ}    OBJECT ${SOURCES})
add_library(${LIB_SHARED} SHARED $<TARGET_OBJECTS:${LIB_OBJ}>)
add_library(${LIB_STATIC} STATIC $<TARGET_OBJECTS:${LIB_OBJ}>)

add_library(${PROJECT_NAME}::shared ALIAS ${LIB_SHARED})
add_library(${PROJECT_NAME}::static ALIAS ${LIB_STATIC})

# Change output name from libtemplate_shared to libtemplate.so
set_target_properties(${LIB_SHARED}
    PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

# Target modifications
# Note: The modifications cannot be used on the ALIAS targets, those are just for
# dependent projects to use

# shared libs need PIC, this is needed because we use an intermediate object library
# building a shared library directly does not require this call
set_property(TARGET ${LIB_OBJ} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(${LIB_OBJ}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_include_directories(${LIB_SHARED}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_include_directories(${LIB_STATIC}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# Compile options are private so we don't pollute other targets with our flags
# this is important especially for coverage so other code is not accidentally
# instrumented
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(${LIB_OBJ} PRIVATE ${COMMON_CXX_FLAGS_DEBUG} ${WARNINGS})
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(${LIB_OBJ} PRIVATE ${COMMON_CXX_FLAGS_RELEASE} ${WARNINGS})
endif()

if(${ENABLE_CODE_COVERAGE})
    message(STATUS "Building ${LIB_OBJ} with coverage")
    target_compile_options(${LIB_OBJ} PRIVATE ${COVERAGE_FLAGS})
endif()

# Unit Tests
if(CMAKE_BUILD_TYPE MATCHES "Debug" AND ${ENABLE_TESTING})
    enable_testing()
    add_subdirectory(external/doctest)
    add_subdirectory(external/fakeit)
    add_subdirectory(tests)
endif()

# adds an automatic symlink to the compilation database of the current build configuration
add_custom_target(compile_commands_symlink ALL
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ln -snf ${CMAKE_COMPILE_COMMANDS} "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json"
    COMMENT "Creating symlink to ${CMAKE_COMPILE_COMMANDS}")
add_dependencies(compile_commands_symlink ${LIB_OBJ})

