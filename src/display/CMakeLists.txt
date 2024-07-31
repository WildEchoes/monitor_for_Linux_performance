# Display
project(display)
# 查找Qt库
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 添加源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(display ${SRC_LIST})

# 设置自动moc 用于qt的信号槽
set_target_properties(display PROPERTIES AUTOMOC TRUE)

# 添加头文件路径
# target_include_directories(display PUBLIC ${PROJECT_SOURCE_DIR}/src/rpc_manager)

# 添加链接库
target_link_libraries(display
    PUBLIC
    # client
    # monitor_proto
    Qt5::Widgets
    Qt5::Core
)