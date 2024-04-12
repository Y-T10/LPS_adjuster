#pragma once

#include <type_traits>
#include <concepts>
#include <cstdint>

#include "loop_speed.hpp"

namespace TCL {
    template<class F, class R, class ...Args>
    concept InvocableR =
        std::invocable<F, Args...> &&
        std::same_as<std::invoke_result_t<F, Args...>, R>
    ;

    template<class hz_type = uint32_t, class Func, class ...Args>
    requires InvocableR<Func, bool, Args...>
    void RepeatInHz(const hz_type hz, Func&& func, Args&&... args) noexcept {
        const auto Adjuster = AdjustLPS(hz);
        Adjuster.run();
        while (func(args...)) {
            Adjuster.adjust_fps();
        }
    }
}