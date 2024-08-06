project(rpc_server)

set(SOURCES
    main.cpp
    rpc_server.cpp
)

add_executable(server ${SOURCES})
target_link_libraries(server
    PUBLIC
        monitor_proto
)