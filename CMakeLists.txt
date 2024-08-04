cmake_minimum_required(VERSION 3.10.2)
project(monitor_for_linux 
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "monitor for linux"
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)

# 可执行文件输出路径
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 动态库
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# 静态库
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 可视化模块
add_subdirectory(src/display)
# rpc通信模块
# add_subdirectory(src/rpc)
# 序列化模块
# add_subdirectory(src/proto)
# 监控工厂模块
# add_subdirectory(src/monitor)