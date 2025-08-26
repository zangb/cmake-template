project(template_test LANGUAGES CXX)

set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/template.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    doctest::doctest
    FakeIt::FakeIt-doctest
    template::static)

if(${ENABLE_CODE_COVERAGE})
    target_link_libraries(${PROJECT_NAME} PRIVATE -lgcov)
endif()

# Adds a call to the generate unit-test executable. Additional commandline args
# can be passed here as well
add_test(NAME ${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>)
