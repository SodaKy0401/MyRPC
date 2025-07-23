set(SRC_LIST callfriendservice.cc ./friend.pb.cc)
include_directories(../)
include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR}/src/include)
add_executable(consumer ${SRC_LIST})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
target_link_libraries(consumer lsrpc protobuf  zookeeper_mt muduo_base muduo_net glog )
