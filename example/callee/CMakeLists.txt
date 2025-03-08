set(SRC_LIST friendservice.cc ./friend.pb.cc)
include_directories(../)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/include)
add_executable(provider ${SRC_LIST})
target_link_libraries(provider lsrpc protobuf  zookeeper_mt muduo_base muduo_net glog )  


