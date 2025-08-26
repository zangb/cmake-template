project(template_test LANGUAGES CXX)

set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/template.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    doctest::doctest
    FakeIt::FakeIt-doctest
    template::template)

if(${ENABLE_CODE_COVERAGE} AND NOT BUILD_SHARED)
    # Explicitly required to link against the gcov lib
    # Coverage for shared builds is currently not in the preset
    target_link_libraries(${PROJECT_NAME} PRIVATE -lgcov)
endif()

# Adds a call to the generate unit-test executable. Additional commandline args
# can be passed here as well
add_test(NAME ${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>)

if(${ENABLE_CODE_COVERAGE})
    # The variables are specified by the CMakePresets.json
    file(MAKE_DIRECTORY ${COVERAGE_DIR})
    file(MAKE_DIRECTORY ${HTML_OUTPUT_DIR})

    # No need to have the user specify these values
    set(LCOV lcov)
    set(GENTHML genhtml)
    set(COVERAGE_INFO "${COVERAGE_DIR}/coverage.info")

    # Compiles the coverage data into a report
    add_test(NAME lcov
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND lcov --mcdc-coverage --branch-coverage
            -c -d . -o ${COVERAGE_INFO})

    # Generates a HTML report from the compile coverage data
    add_test(NAME genhtml
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND genhtml ${COVERAGE_INFO} --mcdc-coverage
            --branch-coverage --output-directory ${HTML_OUTPUT_DIR})

    # Set up dependencies for execution order
    set_tests_properties(lcov
        PROPERTIES DEPENDS ${PROJECT_NAME})
    set_tests_properties(genhtml
        PROPERTIES DEPENDS lcov)
endif()
