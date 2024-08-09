project(RPC_Clinet)

# aux_source_directory(. SRC_LIST)
set(SOURCES
    rpc_client.cpp
)

add_library(client STATIC ${SOURCES})

target_link_libraries(client
    PUBLIC
        monitor_proto
)