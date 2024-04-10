# CTestを読み込む
include(CTest)
## テストフレームワークを追加
find_package(doctest REQUIRED)
include(doctest)

# Ctestヘルパーモジュールを読み込む
include(${CMAKE_SOURCE_DIR}/cmake/CtestHelper.cmake)

# テストを追加する
register_test(TestMain Target doctest::doctest)
# doctestに追加する
doctest_discover_tests(TestMain)
