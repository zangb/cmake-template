cmake_minimum_required(VERSION 3.26)
project(template VERSION 1.0.0.0 LANGUAGES C CXX)

option(BUILD_SHARED "Build the shared version of the library" OFF)
option(ENABLE_UNIT_TESTS "Include unit-tests in the build" OFF)
option(ENABLE_CODE_COVERAGE "Compile the lib with coverage or not" OFF)

# add source files to this variable
set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/template.cpp")

if(BUILD_SHARED)
    message(STATUS "Building library ${PROJECT_NAME}: SHARED")
    add_library(${PROJECT_NAME} SHARED ${SOURCES})
else()
    message(STATUS "Building library ${PROJECT_NAME}: STATIC")
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif(BUILD_SHARED)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# Compile options are private so we don't pollute other targets with our flags.
# This is important especially for coverage so other code is not accidentally
# instrumented
# Setting flags globally is bad practice
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE
        ${COMMON_CXX_FLAGS_DEBUG} ${WARNINGS})
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE
        ${COMMON_CXX_FLAGS_RELEASE} ${WARNINGS})
endif()

if(${ENABLE_CODE_COVERAGE})
    message(STATUS "Building library ${PROJECT_NAME} with coverage")
    target_compile_options(${PROJECT_NAME} PRIVATE ${COVERAGE_FLAGS})
endif()

# Unit Tests
if(CMAKE_BUILD_TYPE MATCHES "Debug" AND ${ENABLE_UNIT_TESTS})
    enable_testing()
    add_subdirectory(external/doctest)
    add_subdirectory(external/fakeit)
    add_subdirectory(tests)
endif()

# Adds a symlink to the compilation database of the current build config
# The symlink is automatically updated if the build config changes.
add_custom_target(compile_commands_symlink ALL
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ln -snf ${CMAKE_COMPILE_COMMANDS}
        "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json"
    COMMENT "Creating symlink to ${CMAKE_COMPILE_COMMANDS}")
add_dependencies(compile_commands_symlink ${PROJECT_NAME})

