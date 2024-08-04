# Display
project(Display)
# 查找Qt库
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# 添加头文件路径
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 添加源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# 添加主文件
set(SRC_LIST ${SRC_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/src/main_display.cpp)

add_executable(display ${SRC_LIST})

# 自动处理Qt的元对象编译器，CMake会自动调用MOC工具来处理包含 Q_OBJECT 宏的头文件
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

# 设置RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")