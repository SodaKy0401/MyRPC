#include <iostream>
#include "mprpcapplication.h"
#include "friend.pb.h"
#include <atomic>
#include <vector>
#include <thread>
#include "/home/ls/RPC/src/logger.h"
  /*
int main(int argc, char **argv)
{
    // 整个程序启动以后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    rpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    fixbug::::FiendServiceRpc_Stub stub(new MyrpcChannel());
    // rpc方法的请求参数
    fixbug::::GetFriendsListRequest request;
    request.set_userid(1000);
    // rpc方法的响应
    fixbug::::GetFriendsListResponse response;
    // 发起rpc方法的调用  同步的rpc调用过程  MprpcChannel::callmethod
    MyrpcController controller;
    
    
    stub.GetFriendsList(&controller,&request, &response, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送
    
    // 一次rpc调用完成，读调用的结果
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    }
    else
    {
        if (0 == response.result().errcode())
        {
            std::cout << "rpc GetFriendsList response success!" << std::endl;
            int size = response.friends_size();
            for (int i=0; i < size; ++i)
            {
                std::cout << "index:" << (i+1) << " name:" << response.friends(i) << std::endl;
            }
        }
        else
        {
            std::cout << "rpc GetFriendsList response error : " << response.result().errmsg() << std::endl;
        }
    }
    
} 
     */


///*
void testqps(int thread_id, std::atomic<int> &success_count, std::atomic<int> &fail_count)
{

    // 整个程序启动以后，想使用krpc框架就要先调用初始化函数(只初始化一次)
    

    // 演示调用远程发布的rpc方法Login
    fixbug::FiendServiceRpc_Stub stub(new MprpcChannel());
    // rpc方法的请求参数
    fixbug::GetFriendsListRequest request;
    request.set_userid(1000);
    // rpc方法的响应
    fixbug::GetFriendsListResponse response;
    MprpcController controller;
   
    
    stub.GetFriendsList(&controller,&request, &response, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送             // 我们重写的Rpchannel继承google的rpc框架的rpcchannel,形成多态
    
    if (controller.Failed())
    {       std::cout << "Failed!" << controller.ErrorText().c_str() ;
            //fail_count ++;
    }
    else
    {
        if (0 == response.result().errcode())
        {
            std::cout << "rpc GetFriendsList response success!" << std::endl;
            int size = response.friends_size();
            for (int i=0; i < size; ++i)
            {
                std::cout << "index:" << (i+1) << " name:" << response.friends(i) << std::endl;
            }
            success_count ++;
        }
        else
        {
            std::cout << "rpc GetFriendsList response error : " << response.result().errmsg() << std::endl;
            fail_count ++;
        }
    }
    
}


int main(int argc, char **argv)
{
    
    
    MprpcApplication::Init(argc, argv);
   /* rpcLogger logger("MyRPC");
    FLAGS_log_dir = "/home/ls/fixbug::/example/caller/tmp";
    FLAGS_logtostderr = false;  
    FLAGS_alsologtostderr = false; 
    FLAGS_log_prefix = true; // 允许日志文件名前缀*/


    const int thread_count = 100;      // 并发线程数
    const int requests_per_thread = 50; // 每个线程发送的请求数

    std::vector<std::thread> threads;
    std::atomic<int> success_count(0);
    std::atomic<int> fail_count(0);
   
    auto start_time = std::chrono::high_resolution_clock::now(); // 开始时间
    // 启动多线程进行并发测试
    for (int i = 0; i < thread_count; i++)
    {
        threads.emplace_back([argc, argv, i, &success_count, &fail_count, requests_per_thread]()
                             {
        for(int j=0;j<requests_per_thread;j++)
        {
          testqps(i,success_count,fail_count);
        } });
    }
    for (auto &t : threads)
    {
        t.join();
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    // 输出统计结果
    std::cout << "Total requests: " << thread_count * requests_per_thread;
    std::cout << "Success count: " << success_count;
    std::cout << "Fail count: " << fail_count;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds"  ;
    std::cout << "QPS: " << (thread_count * requests_per_thread) / elapsed.count();
    return 0;
} 
//*/git