#ifndef SESSION_HPP
#define SESSION_HPP

#include <boost/asio.hpp>
#include <iostream>
#include "event.hpp"
#include "server.hpp"
#include "logger.hpp"
using boost::asio::ip::tcp;
class Event;
class Logger;

class Session : public std::enable_shared_from_this<Session>
{
public:
    // Session() = default;
    Session(tcp::socket socket)
        : socket_(std::move(socket))
    {
    }
    //~Session() = default;
    void start(Event* pEvt, Logger* pLog);
    void setData(const char *data);
    void deliver() {}

private:
    void do_read_header();
    void do_read_body();
    void do_write();
    tcp::socket socket_;
    int session_id_;
    Event *pEvt_;
    Logger *pLog_;
    char write_data_[516];
    int write_len_;
};

#endif