#ライブラリを追加
add_library(LPSAdjuster)

#プログラムファイル
target_sources(LPSAdjuster PRIVATE loop_speed.cpp)
target_include_directories(LPSAdjuster PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#ライブラリを追加
target_link_libraries(LPSAdjuster PRIVATE)