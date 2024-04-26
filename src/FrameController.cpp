#include "FrameController.hpp"

#include <algorithm>
#include <numeric>
#include <thread>
#include <utility>
#include <cassert>

namespace {
    constexpr auto OneSecond = TCL::FrameController::clock_type::duration(std::chrono::seconds(1));

    inline const auto CurrentTime() noexcept {
        return TCL::FrameController::clock_type::now();
    };
}

namespace TCL {
    FrameController::FrameController(const uint32_t fps) noexcept:
    m_frameDurations(fps, clock_type::duration(OneSecond.count() / fps)),
    m_lastTime(CurrentTime()),
    m_FPS(fps){
        assert(m_FPS > 0);
    }
    FrameController::FrameController(FrameController&& rval) noexcept:
    m_frameDurations(std::move(rval.m_frameDurations)),
    m_lastTime(std::move(rval.m_lastTime)),
    m_FPS(std::move(rval.m_FPS)){
    }

    FrameController& FrameController::operator=(FrameController&& rval) noexcept {
        if (this == &rval) {
            return *this;
        }

        m_frameDurations = std::move(rval.m_frameDurations);
        m_lastTime = std::move(rval.m_lastTime);
        m_FPS = std::move(rval.m_FPS);

        return *this;
    };
    
    FrameController::~FrameController() {
    }

    void FrameController::delay() noexcept {
        assert(!m_frameDurations.empty());
        //現在のフレームが消費した時間を求め、最後に取得した時刻を更新する
        const clock_type::duration FrameDuration = CurrentTime() - m_lastTime;
        m_lastTime += FrameDuration;

        //最新の経過時間を保存し、最古の経過時間を削除する
        m_frameDurations.push_front(FrameDuration);
        m_frameDurations.pop_back();

        //キュー内の経過時間の和を求める
        const clock_type::duration SumFrameDuration = std::accumulate(
            m_frameDurations.begin(), m_frameDurations.end(),
            clock_type::duration(0)
        );

        //経過時間が1sより小さいかを確認する
        if (SumFrameDuration >= OneSecond) {
            return;
        }

        //最も短い時間だけ実行を止める
        std::this_thread::sleep_for(std::min(
            OneSecond - SumFrameDuration,                       //現在のフレームに与えられた残り時間
            clock_type::duration(OneSecond.count() / m_FPS)  //1フレーム当たりの時間
        ));
    }

    const double FrameController::FPS() const noexcept {
        assert(m_FPS > 0);
        assert(m_frameDurations.size() == m_FPS);

        //目標フレーム数分経過するのにかかった時間を求める
        const clock_type::duration SumFrameDuration = std::accumulate(
            m_frameDurations.begin(), m_frameDurations.end(),
            clock_type::duration(0)
        );

        //経過時間が0sかを判断する
        if(SumFrameDuration == clock_type::duration(0)){
            //doubleの最大値を返す
            return std::numeric_limits<double>::max();
        }

        //秒単位でFPSを求める
        return static_cast<double>((m_FPS * OneSecond.count())) / static_cast<double>(SumFrameDuration.count());
    }

    const FrameController::clock_type::duration FrameController::lastDuration() const noexcept {
        return m_frameDurations.front();
    }
}