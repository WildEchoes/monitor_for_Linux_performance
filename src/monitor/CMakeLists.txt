project(monitor)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(monitor main.cpp ${SRC_LIST})

target_link_directories(monitor 
    PUBLIC
    ${PROJECT_SOURCE_DIR}/monitor/include
    ${PROJECT_SOURCE_DIR}/rpc
)

target_link_libraries(monitor
    PUBLIC
    monitor_proto
    client 
    boost_system
    boost_chrono
)
