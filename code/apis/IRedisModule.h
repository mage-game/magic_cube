#pragma once
#include <string>  

class IRedisModule
{
public:
    virtual bool Connect(const std::string& ip = "", const int port = 6397, const std::string& password = "") = 0;
    virtual bool Disconnect() = 0;
};