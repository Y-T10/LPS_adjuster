#include "FrameController.hpp"
#include <format>

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

TEST_CASE("Call funtions") {
    using Duration = TCL::FrameController::clock_type::duration;

    constexpr auto Hertz = 60;
    TCL::RepeatInHz(Hertz, [n = 0](const Duration& LastFrameTime, const double FPS) mutable -> bool {
        if (n >= (Hertz * 10)) {
            return false;
        }
        MESSAGE(std::format("frame: {}, time: {}, FPS: {}", n, LastFrameTime, FPS));
        ++n;
        return true;
    });
}