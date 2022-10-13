#include"loop_speed.hpp"

//usingディレクティブ
using namespace std::chrono;

//コンストラクタ
AdjustLPS::AdjustLPS(const uint32_t target_fps):
m_target_lps(target_fps),
m_past_time(){
}

//デストラクタ
AdjustLPS::~AdjustLPS(){
    m_past_time.clear();
}

//現在の時刻を取得する
const AdjustLPS::t_time AdjustLPS::now_time() const{
    //現在時刻を取得
    return t_clock::now();
}

//現在のFPSを返す
const double AdjustLPS::fps() const{
    //FPSが0かを確かめる
    if(m_target_lps == 0){
        return 0;
    }

    assert(m_past_time.size() == m_target_lps);
    //目標フレーム数分経過するのにかかった時間を求める
    const t_time::duration dur_spent_t_time = std::accumulate(
        m_past_time.begin(), m_past_time.end(),
        t_time::duration(0)
    );
    const t_duration dur_spent_time = duration_cast<t_duration>(dur_spent_t_time);

    //経過時間が0sかを判断する
    if(dur_spent_time == t_duration(0)){
        //doubleの最大値を返す
        return std::numeric_limits<double>::max();
    }

    //秒単位でFPSを求める
    constexpr t_duration one_second = t_duration(seconds(1));
    return static_cast<double>((m_target_lps * one_second.count())) / static_cast<double>(dur_spent_time.count());
}

//制御開始
void AdjustLPS::run(const uint32_t target_fps){
    //目標FPSを設定
    m_target_lps = target_fps;
    
    //計測のための初期化を実行
    const_cast<const AdjustLPS*>(this)->run();
    assert(m_past_time.size() == m_target_lps);
}

//制御開始
void AdjustLPS::run() const{
    //キューのサイズを変更する
    m_past_time.resize(m_target_lps);
    //キューの中身を初期化する
    constexpr t_duration one_second = t_duration(seconds(1));
    const t_duration SPF = t_duration(one_second.count() / m_target_lps);
    std::fill(m_past_time.begin(), m_past_time.end(), SPF);

    //調整開始時刻を定める
    m_last_time = now_time();
}

//FPS調整
void AdjustLPS::adjust_fps() const{
    assert(!m_past_time.empty());
    //処理時間を求める
    const t_time cur_time = now_time();
    assert( cur_time > m_last_time );
    const t_time::duration spent_time = cur_time - m_last_time;
    //処理時間を求めた時間を保存する
    m_last_time = cur_time;

    //最新の経過時間を保存する
    m_past_time.push_front(duration_cast<t_duration>(spent_time));
    //最古の経過時間を削除する
    m_past_time.pop_back();
    assert(m_past_time.size() == m_target_lps);

    //キュー内の経過時間の和を求める
    const t_duration sum_spent_time = std::accumulate(
        m_past_time.begin(), m_past_time.end(),
        t_duration(0)
    );

    //経過時間が1sより小さいかを確認する
    constexpr t_duration one_second = t_duration(seconds(1));
    if(sum_spent_time < one_second){
        //遅延時間を求める
        const t_duration delay_time = one_second - sum_spent_time;
        assert(delay_time.count() > 0);
        //遅延させる
        const t_duration SPF = t_duration(one_second.count() / m_target_lps);
        std::this_thread::sleep_for(delay_time >= SPF ? SPF: delay_time);
    }
}