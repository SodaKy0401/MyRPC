#include <iostream>
#include <queue>
#include <mutex>
#include <string>
#include <vector>
#include <condition_variable>
#include <arpa/inet.h>
#include <unistd.h>

class ConnectionPool {
public:
    static ConnectionPool& GetInstance() {
        static ConnectionPool instance;
        return instance;
    }

    int GetConnection(const std::string& ip, uint16_t port) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!connections_.empty()) {
            int sockfd = connections_.front();
            connections_.pop();
            return sockfd;
        }
        return CreateSocket(ip, port);
    }

    void ReleaseConnection(int sockfd) {
        std::lock_guard<std::mutex> lock(mutex_);
        connections_.push(sockfd);
    }

    ~ConnectionPool() {
        while (!connections_.empty()) {
            close(connections_.front());
            connections_.pop();
        }
    }
    void InvalidateConnection(int sockfd) {
        close(sockfd);  // 关闭无效连接，防止放回池中
    }

private:
    ConnectionPool() = default;

    int CreateSocket(const std::string& ip, uint16_t port) {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) return -1;
        
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        
        if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            close(sockfd);
            return -1;
        }
        return sockfd;
    }

  
    std::queue<int> connections_;
    std::mutex mutex_;
    
};


