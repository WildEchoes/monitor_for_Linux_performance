project(PROTOBUF_SETTING)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(c-ares CONFIG)  # DNS resolver

set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB PROTO_FILES "${PROTO_SRC_DIR}/*.proto")

message(STATUS "Found .proto files: ${PROTO_FILES}")

add_library(monitor_proto STATIC ${PROTO_FILES})

target_link_libraries(monitor_proto
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)

target_include_directories(monitor_proto 
    PUBLIC
        ${PROTOBUF_INCLUDE_DIRS} 
        ${CMAKE_CURRENT_BINARY_DIR}
)

#
# Compile protobuf and grpc files in mointor proto target to cpp
#
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
# protobuf_generate(TARGET monitor_proto LANGUAGE cpp)

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

protobuf_generate(
    TARGET monitor_proto 
    LANGUAGE grpc 
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc 
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)

target_sources(monitor_proto
    PUBLIC
        ${PROTO_SRCS}
        ${PROTO_HDRS}
)