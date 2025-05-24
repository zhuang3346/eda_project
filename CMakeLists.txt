cmake_minimum_required(VERSION 3.10)
project(eda_project)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 添加源文件
set(SOURCES
    main.cpp
    parser.cpp
    place.cpp
    exporter.cpp
)

# 添加头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 生成可执行文件
add_executable(eda_project ${SOURCES})