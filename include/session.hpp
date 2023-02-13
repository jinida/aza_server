#ifndef SESSION_HPP
#define SESSION_HPP

#include <boost/asio.hpp>
#include <iostream>
#include "event.hpp"
#include "server.hpp"
#include "logger.hpp"
#include "spdlog/spdlog.h"
using boost::asio::ip::tcp;
class Packet;
class Event;
class Logger;

class Session : public std::enable_shared_from_this<Session>
{
public:
    // Session() = default;
    Session(tcp::socket socket, std::mutex* pMutex)
        : socket_(std::move(socket)), pMutex_(pMutex)
    {
    }
    //~Session() = default;
    void start(std::priority_queue<Event>* pEvt_queue, std::queue<Logger>* pLogger_queue);
    void setData(const char *data);
    void deliver() {}

private:
    void do_read_header();
    void do_read_body();
    void do_write();
    tcp::socket socket_;
    int session_id_;
    std::priority_queue<Event>* pEvt_queue_;
    std::queue<Logger>* pLogger_queue_;
    std::mutex *pMutex_;
    Packet *pkt;
    char write_data_[516];
    int write_len_;
};

#endif