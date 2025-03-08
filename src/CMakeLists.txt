

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


set(SRC_LIST 
    mprpcapplication.cc 
    rpcprovider.cc 
    mprpcconfig.cc
    rpcheader.pb.cc 
    mprpcchannel.cc
    mprpccontroller.cc
    logger.cc
    zookeeperutil.cc
   
    )



add_library(lsrpc  ${SRC_LIST} )
target_link_libraries(lsrpc pthread zookeeper_mt muduo_base muduo_net    )

