#pragma once

//#define FILE_LOG

#if defined (FILE_LOG)
 #if defined (_MSC_VER)
  #include "NanoLog.hpp"
 #else
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wformat"
  #pragma GCC diagnostic ignored "-Wunused-variable"
  #pragma GCC diagnostic ignored "-Wsign-compare"
  #pragma GCC diagnostic ignored "-Wunused-parameter"
  #pragma GCC diagnostic ignored "-Wconversion"
  #include "NanoLog.hpp"
  #pragma GCC diagnostic pop
#endif

#else

#include <sstream>
#include <string>
#include <iostream>

namespace plugin
{
namespace a
{

struct FakeLog
{
    FakeLog(std::string type, int line)
        : ostm_(), type_(type), line_(line)
    {
    }

    ~FakeLog()
    {
        Flush();
    }

    void Flush()
    {
        std::string s = ostm_.str();
        if (!s.empty()) {
            std::cout << "[" << type_ << "] [" << line_ << "] " << s << "\n";
        }
    }

    std::ostringstream& Stream()
    {
        return ostm_;
    }
    std::ostringstream ostm_;
    std::string type_;
    int line_;
};

} // namespace a
} // namespace plugin

#define LOG_INFO plugin::a::FakeLog("INFO", __LINE__).Stream()
#define LOG_WARN plugin::a::FakeLog("WARN", __LINE__).Stream()
#define LOG_CRIT plugin::a::FakeLog("CRIT", __LINE__).Stream()

#endif

