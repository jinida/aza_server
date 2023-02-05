#include <conio.h>
#include "server.hpp"

void Server::do_accept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<Session>(std::move(socket), sessionNum++)->start();
            }
            do_accept();
        });
}

void Session::do_read_header()
{
    auto self(shared_from_this());
    auto f = [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec && read_event.getEventPacket().decodeHeader())
            {
                do_read_body();
            }
        };
    boost::asio::async_read(socket_, boost::asio::buffer(read_event.getEventPacket().data(), LEN_HEADER), f)
}

void Session::do_read_body()
{
    auto self(shared_from_this());
    auto f = [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {   
                do_read_header();
            }
        };
    boost::asio::async_read(socket_, boost::asio::buffer(read_event.getEventPacket().body(), 
        read_event.getEventPacket().body_length()), f);
}

void Session::do_write()
{
    auto self(shared_from_this());
    auto f = [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                write_events.pop_front();
                if (!write_events.empty())
                {
                    do_write();
                }
            }
        };
    boost::asio::async_write(socket_, boost::asio::buffer(write_events.top().getEventPacket().getData(), write_events.top().getEventPacket().getLen()), f);
}