# Display
project(Display)
# 查找Qt库
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# 添加头文件路径
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# 添加源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# 添加主文件
set(SRC_LIST ${SRC_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(display ${SRC_LIST})

# 设置自动moc 用于信号和槽机制
set_target_properties(display PROPERTIES AUTOMOC TRUE)

# 添加头文件路径
get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)
target_include_directories(display PUBLIC ${PARENT_DIR}/rpc)

# 添加链接库
target_link_libraries(display
    PUBLIC
    client
    monitor_proto
    Qt5::Widgets
    Qt5::Core
)

# 设置RPATH
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)  # 安装时使用链接路径
# set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)    # 设置编译时使用安装路径
# set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")  # 设置安装路径，能在lib够找到依赖库
# message(STATUS "CMAKE_INSTALL_RPATH: ${CMAKE_INSTALL_RPATH}")