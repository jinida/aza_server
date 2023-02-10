#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include "server.hpp"
#include "event.hpp"
#include "logger.hpp"
#include "spdlog/async.h"

int main()
{
    boost::asio::io_context io_context;
    auto filesink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt", true);
    auto pLogger = std::make_shared<spdlog::logger>("LoggerTest", filesink);
    pLogger->set_pattern("[%Y-%m-%d %H:%M:%S] [thread %t] [%L] %v");
    Logger("Initialize AZA! Server", Logger::LoggerType::SERVER, Logger::LoggerStatus::PROCESSED, Logger::LoggerInfo::INFO).printLog(pLogger);
    pLogger->flush();
    
    std::queue<Logger> loggerQueue;
    std::priority_queue<Event> eventQueue;
    std::mutex m;
    Server s(io_context, 50000, &eventQueue, &loggerQueue, &m);
    
    std::thread serv_thrd([](boost::asio::io_context* io_context) {
        io_context->run();
    }, &io_context);

    while(true)
    {
        sleep(0.1);
        std::lock_guard<std::mutex> lock(m);
        if (loggerQueue.size() != 0 && loggerQueue.front().getStatus() == Logger::LoggerStatus::PROCESSED)
        {
            loggerQueue.front().printLog(pLogger);
            pLogger->flush();
            loggerQueue.pop();
        }
    }

    serv_thrd.join();
    return 0;
}