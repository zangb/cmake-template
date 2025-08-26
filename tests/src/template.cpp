#include <doctest/doctest.h>

#include <template/template.hpp>

TEST_SUITE("Template") {
    TEST_CASE("Dummy") {
        CHECK_EQ(dummy::dummy(6, 3), 9);
    }
}
