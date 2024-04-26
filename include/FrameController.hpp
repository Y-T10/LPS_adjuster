#pragma once

#include<cstdint>
#include<chrono>
#include<deque>

namespace TCL {
    /**
     * @class FrameController
     * @brief 1 ループ当たりにかかる時間を調整するクラス
     */
    struct FrameController final {
        /// 時計型
        using clock_type = std::chrono::steady_clock;

        /**
         * @brief コンストラクタ
         * @param fps 目標のFPS値．0より大きい値を入れること．
         */
        explicit FrameController(const uint32_t fps) noexcept;
        
        FrameController(const FrameController& rval) noexcept = delete;
        FrameController(FrameController&& rval) noexcept;
        FrameController() noexcept = delete;

        FrameController& operator=(const FrameController& rval) noexcept = delete;
        FrameController& operator=(FrameController&& rval) noexcept;
        
        ~FrameController();

        /**
         * @brief プログラムの実行を止め、フレームの消費時間を調整する．
         */
        void delay() noexcept;

        /**
         * @brief 現在のFPSを返す． 
         */
        const double FPS() const noexcept;

        /// 最後に調整したフレームの消費時間を返す．
        const clock_type::duration lastDuration() const noexcept;

        private:
        /**
         * @brief 時間管理バッファ
         * @details frontが最新の使用時間。backが最古の使用時間。
         */
        std::deque<clock_type::duration> m_frameDurations;
        /// 最後に取得した時刻
        clock_type::time_point m_lastTime;
        /// 目標とするLPS
        uint32_t m_FPS;
    };
}