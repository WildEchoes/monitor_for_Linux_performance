project(monitor_manager)
find_package(Boost REQUIRED COMPONENTS system chrono)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(monitor main.cpp ${SRC_LIST})

get_filename_component(PARENT_DIRECTORY ${PROJECT_SOURCE_DIR} DIRECTORY)
get_filename_component(PARENT_DIRECTORY ${PARENT_DIRECTORY} DIRECTORY)

message(STATUS "Found P-S-D ${PARENT_DIRECTORY}")

target_include_directories(monitor
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PARENT_DIRECTORY}/src/rpc
)

target_link_libraries(monitor
    PUBLIC
    monitor_proto
    client 
    boost_system
    boost_chrono
)
