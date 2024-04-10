cmake_minimum_required(VERSION 3.20)

# このプロジェクトの概要を設定する
project(
    TCL
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "Control repeat count per second."
)

# ビルド周りの設定
option(BUILD_SHARED_LIBS "Build shared libraries." OFF)
option(CMAKE_BUILD_TYPE "Build type." Release)

# CMAKE_EXPORT_COMPILE_COMMANDSの既定値を設定する
if ((NOT (DEFINED $ENV{CMAKE_EXPORT_COMPILE_COMMANDS})) AND (DEFINED CMAKE_EXPORT_COMPILE_COMMANDS))
  set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
endif()

# CMakeのポリシーを設定する
cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0128 NEW)
cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0077 NEW)

# C++コンパイラに渡すオプションを設定する
add_compile_options(-Wall $<$<CONFIG:Debug>:-g3>)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 23)

# システム内のパッケージを読み込む
find_package(Threads REQUIRED)

# Add sub directories
add_subdirectory(src)

## 親プロジェクトが存在するかを調べる
if(NOT (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME}))
    ## ここで処理を終わらせる
    return()
endif()

## テストを有効にする
enable_testing()
## テストディレクトリ
add_subdirectory(test)
