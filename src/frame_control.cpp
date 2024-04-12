#pragma once

#include "frame_control.hpp"

namespace {
    constexpr auto OneSecond = TCL::FrameCtrl::clock_type::duration(std::chrono::seconds(1));
}

namespace TCL {
    FrameCtrl::FrameCtrl(const uint32_t hz) noexcept:
    m_fps(hz),
    m_timeLast(clock_type::now()),
    m_timeQueue(){
        //キューの中身を初期化する
        for(auto i = 0; i < m_fps; ++i) {
            m_timeQueue.push(clock_type::duration(OneSecond.count() / m_fps));
        }
    }
    FrameCtrl::FrameCtrl(FrameCtrl&& rval) noexcept:
    m_fps(std::move(rval.m_fps)),
    m_timeLast(std::move(rval.m_timeLast)),
    m_timeQueue(std::move(rval.m_timeQueue)){
    }

    FrameCtrl& FrameCtrl::operator=(FrameCtrl&& rval) noexcept {
        if (this == &rval) {
            return *this;
        }

        m_fps = std::move(rval.m_fps);
        m_timeLast = std::move(rval.m_timeLast);
        m_timeQueue = std::move(rval.m_timeQueue);

        return *this;
    }
}
