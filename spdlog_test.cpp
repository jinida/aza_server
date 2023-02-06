#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
//#include "logger.hpp"

int main()
{
    auto filesink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt", true);
    auto pLogger = std::make_shared<spdlog::logger>("LoggerTest", filesink);
    pLogger->set_pattern("[%Y-%m-%d %H:%M:%S] [thread %t] [%L] %v");
    pLogger->info("asd");
}
