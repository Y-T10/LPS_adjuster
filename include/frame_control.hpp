#pragma once

#include<cstdint>
#include<chrono>
#include<queue>

namespace TCL {
    struct FrameCtrl {
        FrameCtrl(const uint32_t hz = 0) noexcept;
        FrameCtrl(const FrameCtrl& rval) noexcept = delete;
        FrameCtrl(FrameCtrl&& rval) noexcept;

        FrameCtrl& operator=(const FrameCtrl& rval) noexcept = delete;
        FrameCtrl& operator=(FrameCtrl&& rval) noexcept;

        /// 時計型
        using clock_type = std::chrono::steady_clock;
        /// 時刻型
        using time_type = std::chrono::time_point<clock_type>;

        /// 目標とするLPS
        uint32_t m_fps;

        /// 最後に取得した時刻
        time_type m_timeLast;

        /// 経過時間キュー
        std::queue<clock_type::duration> m_timeQueue;
    };
}
