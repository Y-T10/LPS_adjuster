#pragma once

#include<chrono>
#include<thread>
#include<cassert>
#include<cstdint>
#include<deque>
#include<numeric>
#include<algorithm>
#include<string>
#include<sstream>

/**
 * @class AdjustLPS
 * @brief 1 ループ当たりにかかる時間を調整するクラス
 */
class AdjustLPS final{
    public:
    /**
     * @brief コンストラクタ
     * @param target_fps 目標のFPS値
     * @details `target_fps`のデフォルト値は0。
     */
    AdjustLPS(const uint32_t target_fps = 0);

    /**
     * @brief デストラクタ
     */
    ~AdjustLPS();

    /**
     * @brief 制御を始める
     * @details 現在の時刻を取得し、制御の準備を行う。
     * @details 制御を行う直前で実行すること。
     * @param target_fps 目標FPS
     */
    void run(const uint32_t target_fps);

    /**
     * @overload
     * @brief 制御を始める
     * @details 現在の時刻を取得し、制御の準備を行う。
     * @details 制御を行う直前で実行すること。
     */
    void run() const;

    /**
     * @brief 目標fps値に合わせる
     */
    void adjust_fps() const;

    /**
     * @brief 現在のFPSを返す
     * @return 現在のFPS
     * @retval 目標FPSが0 0
     * @retval それ以外 現在のFPS
     */
    const double fps() const;

    private:
    /// 時計型
    typedef std::chrono::steady_clock t_clock;
    /// 時刻型
    typedef std::chrono::time_point<t_clock> t_time;
    /// 時間型
    typedef t_time::duration t_duration;

    /// 目標とするLPS
    mutable uint32_t m_target_lps;
    /**
     * @brief 最後に取得した時刻
     */
    mutable t_time m_last_time;
    /**
     * @brief 時間管理バッファ
     * @details frontが最新の使用時間。backが最古の使用時間。
     */
    mutable std::deque<t_duration> m_past_time;
    
    /**
     * @brief 現在の時刻を返す
     * @return 現在の時刻
     */
    const t_time now_time() const;
};