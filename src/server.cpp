#include "server.hpp"

void Server::do_accept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                auto pSession = std::make_shared<Session>(std::move(socket));
                pLogger_queue_->push(Logger(pLogger_, "Create Session", Logger::LoggerType::SERVER, Logger::LoggerStatus::PROCESSED, Logger::LoggerInfo::INFO));
                Event evt(sessionNum++, 0, 0, pSession);
                pEvt_queue_->push(evt);
                Logger log(pLogger_, Logger::LoggerType::SERVER, Logger::LoggerStatus::GENEARTED, Logger::LoggerInfo::INFO);
                pLogger_queue_->push(log);
                
                pSession->start(&evt, &log);
            }
            do_accept();
        });
}