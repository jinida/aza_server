#include "server.hpp"
#include "logger.hpp"

void Server::do_accept()
{
    auto f = [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                pMutex_->lock();
                auto pSession = std::make_shared<Session>(std::move(socket), pMutex_);
                pLogger_queue_->push(Logger("Succeed to create session",
                    Logger::LoggerType::SERVER, Logger::LoggerStatus::PROCESSED, Logger::LoggerInfo::INFO));
                // timespec begin, end;
                // clock_gettime(CLOCK_MONOTONIC, &begin);
                // std::stringstream thread_id_converter;
                // thread_id_converter << std::this_thread::get_id();
                // uint64_t id = static_cast<uint64_t>(std::stoull(thread_id_converter.str()));
                // Event evt(sessionNum++, 0, id, pSession);
                // clock_gettime(CLOCK_MONOTONIC, &end);
                // end.tv_sec = end.tv_sec - begin.tv_sec;
                // end.tv_nsec = end.tv_nsec - begin.tv_nsec;
                // evt.setEventGenTime(end);
                // pLogger_queue_->push(Logger("Succeed to create event" + evt.createEventInfo(),
                //     Logger::LoggerType::SERVER, Logger::LoggerStatus::PROCESSED, Logger::LoggerInfo::INFO));
                // pEvt_queue_->push(evt);
                pMutex_->unlock();
                pSession->start(pEvt_queue_, pLogger_queue_);
            }
            else
            {
                pMutex_->lock();
                pLogger_queue_->push(Logger("Failed to create session", Logger::LoggerType::SERVER, Logger::LoggerStatus::PROCESSED, Logger::LoggerInfo::ERROR));
                pMutex_->unlock();
            }
            do_accept();
        };

    acceptor_.async_accept(f);
}