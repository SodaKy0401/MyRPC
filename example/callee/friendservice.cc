#include <iostream>
#include <string>
#include "friend.pb.h"
#include "../../src/Myrpcapplication.h"
#include "../../src/rpcprovider.h"
#include <vector>
#include "zookeeperutil.h"
#include <csignal>
#include <unistd.h>
#include <zookeeper/zookeeper.h>
class FriendService : public LS_RPC::FiendServiceRpc
{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid)
    {
        //std::cout << "do GetFriendsList service! userid:" << userid << std::endl;
        std::vector<std::string> vec;
        vec.push_back("Shuo Lee");
        
        return vec;
    }

    // 重写基类方法
    void GetFriendsList(::google::protobuf::RpcController* controller,
                       const ::LS_RPC::GetFriendsListRequest* request,
                       ::LS_RPC::GetFriendsListResponse* response,
                       ::google::protobuf::Closure* done) override
    {
        uint32_t userid = request->userid();
        std::vector<std::string> friendsList = GetFriendsList(userid);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for (std::string &name : friendsList)
        {
            std::string *p = response->add_friends();
            //std::cout << "GetFriendsList name" << name <<std::endl;
            *p = name;
        }
        done->Run();
    }
};
void signal_handler(int signum) {
    //std::cout << "Received signal, generating gmon.out...\n";
    exit(0);
}

int main(int argc, char **argv)
{
    signal(SIGINT, signal_handler);  // Ctrl+C 也触发 gmon.out 生成
    
    zoo_set_log_stream(nullptr);
    // 调用框架的初始化操作
    MyrpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象。把UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new FriendService());
    
    // 启动一个rpc服务发布节点   Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();

    return 0;
}