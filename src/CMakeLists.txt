

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


set(SRC_LIST 
    Myrpcapplication.cc 
    rpcprovider.cc 
    Myrpcconfig.cc
    rpcheader.pb.cc 
    Myrpcchannel.cc
    Myrpccontroller.cc
    logger.cc
    zookeeperutil.cc
   
    )



add_library(lsrpc  ${SRC_LIST} )
target_link_libraries(lsrpc pthread zookeeper_mt muduo_base muduo_net    )

