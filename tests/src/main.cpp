#define DOCTEST_CONFIG_IMPLEMENT

#include <utility>

#include <doctest/doctest.h>

auto main(int argc, char** argv) -> int {
    doctest::Context context;
    context.applyCommandLine(argc, argv);

    int res     = context.run();
    std::ignore = context.shouldExit();

    return res;
}
