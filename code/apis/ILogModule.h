#pragma once
#include <string>
#include <sstream>

class ILogModule 
{
public:
    virtual void LogDebug(const std::string& strLog, const char* function = "", int line = 0) = 0;
    virtual void LogInfo(const std::string& strLog, const  char* function = "", int line = 0) = 0;
    virtual void LogWarning(const std::string& strLog, const char* function = "", int line = 0) = 0;
    virtual void LogError(const std::string& strLog, const char* function = "", int line = 0) = 0;
    virtual void LogFatal(const std::string& strLog, const char* function = "", int line = 0) = 0;

    virtual void LogDebug(const std::ostringstream& stream, const char* func = "", int line = 0) = 0;
    virtual void LogInfo(const std::ostringstream& stream, const  char* func = "", int line = 0) = 0;
    virtual void LogWarning(const std::ostringstream& stream, const char* func = "", int line = 0) = 0;
    virtual void LogError(const std::ostringstream& stream, const char* func = "", int line = 0) = 0;
    virtual void LogFatal(const std::ostringstream& stream, const char* func = "", int line = 0) = 0;
};

