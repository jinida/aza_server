#include "session.hpp"

void Session::start(Event* pEvt, Logger* pLog)
{
    pEvt_ = pEvt;
    pLog_ = pLog;
    do_read_header();
}

void Session::do_read_header()
{
    auto self(shared_from_this());
    auto f = [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec && pEvt_->getEventPacket().decodeHeader())
            {
                do_read_body();
            }
        };
    boost::asio::async_read(socket_, boost::asio::buffer(pEvt_->getEventPacket().data(), LEN_HEADER), f);
}

void Session::do_read_body()
{
    auto self(shared_from_this());
    auto f = [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {   
                pEvt_->setEventStatus(Event::EventStatus::ENQUEUED);
                pLog_->setContents(fmt::format("Received packets of {} len", pEvt_->getEventPacket().getBodyLen()));
                pLog_->setStatus(Logger::LoggerStatus::PROCESSED);
                do_read_header();
            }
        };
    boost::asio::async_read(socket_, boost::asio::buffer(pEvt_->getEventPacket().body(), 
        pEvt_->getEventPacket().getBodyLen()), f);
}

void Session::do_write()
{
    auto self(shared_from_this());
    auto f = [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                do_write();
            }
        };
    boost::asio::async_write(socket_, boost::asio::buffer(write_data_, write_len_), f);
}