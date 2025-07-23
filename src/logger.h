#pragma once


#include "lockqueue.hpp"
#include <mutex>
#include <string>
#include <atomic>
//定义宏 LOG_INFO("xxx %d %s", 20, "xxxx")
#define LOG_INFO(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c,INFO); \
    } while(0) 

#define LOG_ERR(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c,ERROR); \
    } while(0) 

// 定义日志级别
enum LogLevel
{
    INFO,  // 普通信息
    ERROR, // 错误信息
};
//日志系统
class Logger
{
public:
    // 获取日志的单例
    static Logger& GetInstance();
    // 设置日志级别 
    void SetLogLevel(LogLevel level);
    // 写日志
    void Log(std::string msg,LogLevel level);
private:
    std::atomic<LogLevel> m_loglevel; // 记录日志级别
    LockQueue<std::pair<std::string,LogLevel>> m_lckQue; // 日志缓冲队列
   
    Logger();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
};

/*
#include<glog/logging.h>
#include<string>
//采用RAII的思想
class rpcLogger
{
public:
      //构造函数，自动初始化glog
      explicit rpcLogger(const char *argv0)
      {
        google::InitGoogleLogging(argv0);
        FLAGS_colorlogtostderr=true;//启用彩色日志
        FLAGS_logtostderr=true;//默认输出标准错误
      }
      ~rpcLogger(){
        google::ShutdownGoogleLogging();
      }
      //提供静态日志方法
      static void Info(const std::string &message)
      {
        //std::cout<<message;
      }
      static void Warning(const std::string &message){
        LOG(WARNING)<<message;
      }
      static void ERROR(const std::string &message){
        //std::cout<<message;
      }
          static void Fatal(const std::string& message) {
        LOG(FATAL) << message;
    }
//禁用拷贝构造函数和重载赋值函数
private:
    rpcLogger(const rpcLogger&)=delete;
    rpcLogger& operator=(const rpcLogger&)=delete;
};
*/