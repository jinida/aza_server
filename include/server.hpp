#ifndef SERVER_HPP
#define SERVER_HPP
#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include "event.hpp"
#include "server.hpp"
#include "logger.hpp"
#include "spdlog/spdlog.h"
using boost::asio::ip::tcp;
class Event;
class Session;
class Logger;

class Server
{
public:
    Server(boost::asio::io_context &io_context, short port, std::priority_queue<Event>* pEvt_queue, std::queue<Logger>* pLogger_queue, std::mutex* pMutex)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), sessionNum(0), pEvt_queue_(pEvt_queue), pLogger_queue_(pLogger_queue), pMutex_(pMutex)
    {
        do_accept();
    }
    ~Server() = default;

private:
    void do_accept();
    std::priority_queue<Event>* pEvt_queue_;
    std::queue<Logger>* pLogger_queue_;
    std::mutex* pMutex_;
    int sessionNum;
    tcp::acceptor acceptor_;
};

#endif