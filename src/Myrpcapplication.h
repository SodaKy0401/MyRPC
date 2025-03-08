#pragma once
#include "Myrpcconfig.h"
#include "Myrpcchannel.h"
#include "Myrpccontroller.h"
// mprpc框架的基础类，负责框架的一些初始化操作
class MyrpcApplication
{
public:
    static void Init(int argc, char **argv);
    static MyrpcApplication& GetInstance();
    static Myrpcconfig& GetConfig();
private:
    static Myrpcconfig m_config;

    MyrpcApplication(){}
    MyrpcApplication(const MyrpcApplication&) = delete;
    MyrpcApplication(MyrpcApplication&&) = delete;
};