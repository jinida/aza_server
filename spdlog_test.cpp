<<<<<<< HEAD
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
=======
#include "spdlog/spdlog.h"
#include <iostream>
#include "spd"
int main()
{
    std::cout << "hello world!" << std::endl;
}
>>>>>>> a47a899b2fa2d48d198ca373cd7a857c218141dd
