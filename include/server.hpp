#ifndef SERVER_HPP
#define SERVER_HPP
#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include "event.hpp"
#include "server.hpp"
#include "logger.hpp"
using boost::asio::ip::tcp;
<<<<<<< HEAD
class Event;
class Session;
class Logger;
=======
typedef std::priority_queue<Event> evt_queue;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session() = delete;
    Session(tcp::socket socket)
        : socket_(std::move(socket))
    {
    }
    ~Session() = delete;
    void start();
    void deliver() {}
private:
    void do_read_header();
    void do_read_body();
    void do_write();
    tcp::socket socket_;
    int session_id_;
    Event *pEvt_;
};
>>>>>>> a47a899b2fa2d48d198ca373cd7a857c218141dd

class Server
{
public:
<<<<<<< HEAD
    Server(boost::asio::io_context &io_context, short port, std::priority_queue<Event>* pEvt_queue, std::queue<Logger>* pLogger_queue, 
        std::shared_ptr<spdlog::logger> pLogger)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), sessionNum(0), pEvt_queue_(pEvt_queue), pLogger_queue_(pLogger_queue), pLogger_(pLogger)
=======
    Server() = delete;
    Server(boost::asio::io_context &io_context, short port, pEvt_queue pEvt_queue)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), sessionNum(0), pEvt_queue_(pEvt_queue)
>>>>>>> a47a899b2fa2d48d198ca373cd7a857c218141dd
    {
        do_accept();
    }
    ~Server() = default;

private:
    void do_accept();
<<<<<<< HEAD
    std::priority_queue<Event>* pEvt_queue_;
    std::queue<Logger>* pLogger_queue_;
    std::shared_ptr<spdlog::logger> pLogger_;
    std::mutex* pMutex;
=======
    evt_queue* pEvt_queue_;
    // std::shared_ptr<Session> pSession;
>>>>>>> a47a899b2fa2d48d198ca373cd7a857c218141dd
    int sessionNum;
    tcp::acceptor acceptor_;
};

#endif