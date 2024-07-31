cmake_minimum_required(VERSION 3.10.2)
project(moniter-node-my LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)

# 可视化模块
add_subdirectory(src/display)
# rpc通信模块
add_subdirectory(src/rpc)
# 序列化模块
add_subdirectory(src/proto)
# 监控工厂模块
add_subdirectory(src/moniter)