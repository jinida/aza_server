#include "server.hpp"

void Server::do_accept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                auto pSession = std::make_shared<Session>(std::move(socket));
<<<<<<< HEAD
                pLogger_queue_->push(Logger(pLogger_, "Create Session", Logger::LoggerType::SERVER, Logger::LoggerStatus::PROCESSED, Logger::LoggerInfo::INFO));
                Event evt(sessionNum++, 0, 0, pSession);
                pEvt_queue_->push(evt);
                Logger log(pLogger_, Logger::LoggerType::SERVER, Logger::LoggerStatus::GENEARTED, Logger::LoggerInfo::INFO);
                pLogger_queue_->push(log);
                
                pSession->start(&evt, &log);
            }
            do_accept();
        });
=======
                Event evt(sessionNum++, 0, 0, pSession);
                temp.pSession->start(&temp);
                pEvt_queue->push(temp);
            }
            do_accept();
        });
}
void Session::start(Event* pEvt)
{
    pEvt_ = pEvt;
    do_read_header();
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
                pEvt_->setEventStatus(Event::EventStatus::ENQUEUED);
                do_read_header();
            }
        };
    boost::asio::async_read(socket_, boost::asio::buffer(pEvt_->getEventPacket().body(), 
        pEvt_->getEventPacket().body_length()), f);
}

void Session::do_write(const char* data, int len)
{
    auto self(shared_from_this());
    auto f = [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                do_write();
            }
        };
    boost::asio::async_write(socket_, boost::asio::buffer(data, len), f);
>>>>>>> a47a899b2fa2d48d198ca373cd7a857c218141dd
}