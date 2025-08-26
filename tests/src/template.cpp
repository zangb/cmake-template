#include <doctest/doctest.h>

#include <template/template.hpp>

TEST_SUITE("Template") {
    TEST_CASE("Dummy") {
        CHECK_EQ(dummy::greater_than(6, 3), true);
        CHECK_EQ(dummy::greater_than(3, 6), false);
    }
}
