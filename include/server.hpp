#ifndef SERVER_H
#define SERVER_H
#include <boost/asio.hpp>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <utility>
#include <deque>
#include <queue>
#include "event.hpp"
#include "server.hpp"
using boost::asio::ip::tcp;
typedef std::priority_queue<Event> evt_queue;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session() = delete;
    Session(tcp::socket socket, int session_id)
        : socket_(std::move(socket)), session_id_(session_id)
    {
    }
    ~Session() = delete;
    void start() { do_read_header(); }
    void deliver() {}
private:
    void do_read_header();
    void do_read_body();
    void do_write();
    tcp::socket socket_;
    int session_id_;
    Event read_event;
    evt_queue write_event;
};

class Server
{
public:
    Server() = delete;
    Server(boost::asio::io_context &io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), sessionNum(0)
    {
        do_accept();
    }
    ~Server() = default;

private:
    void do_accept();
    // std::shared_ptr<Session> pSession;
    int sessionNum;
    tcp::acceptor acceptor_;
};

#endif