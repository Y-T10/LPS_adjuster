#include <cstdint>
#include <format>
#include <optional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "repeat_func.hpp"

TEST_CASE("Call funtions") {
    constexpr auto Hertz = 60;
    TCL::RepeatInHz(Hertz, [n = 0]() mutable -> bool {
        if (n >= (Hertz * 10)) {
            return false;
        }
        MESSAGE(std::format("frame: {}", n));
        ++n;
        return true;
    });
}