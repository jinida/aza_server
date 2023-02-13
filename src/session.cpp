#include "session.hpp"

void Session::start(std::priority_queue<Event>* pEvt_queue, std::queue<Logger>* pLogger_queue)
{
    pkt = new Packet;
    pEvt_queue_ = pEvt_queue;
    pLogger_queue_ = pLogger_queue;
    do_read_header();
}

void Session::do_read_header()
{
    auto self(shared_from_this());
    auto f = [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec && pkt->decodeHeader())
            {   
                do_read_body();
            }
            else
            {
                auto errormsg = ec.category().message(ec.value());
                pMutex_->lock();
                pLogger_queue_->push(Logger(errormsg, 
                    Logger::LoggerType::SERVER, Logger::LoggerStatus::PROCESSED, Logger::LoggerInfo::ERROR));
                pMutex_->unlock();
            }
        };
    boost::asio::async_read(socket_, boost::asio::buffer(pkt->data(), LEN_HEADER), f);
}

void Session::do_read_body()
{
    auto self(shared_from_this());
    auto f = [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {   
                pMutex_->lock();
                pLogger_queue_->push(Logger(fmt::format("Received packets of {} len", pkt->getBodyLen()), 
                    Logger::LoggerType::SERVER, Logger::LoggerStatus::PROCESSED, Logger::LoggerInfo::ERROR));
                // pEvt_->setEventStatus(Event::EventStatus::ENQUEUED);
                // do_read_header();
                std::stringstream thread_id_converter;
                thread_id_converter << std::this_thread::get_id();
                uint64_t id = static_cast<uint64_t>(std::stoull(thread_id_converter.str()));
                pEvt_queue_->push(Event(session_id_, 0, id, std::move(*pkt), self));
                pMutex_->unlock();
                do_write();
            }
            else
            {
                auto errormsg = ec.category().message(ec.value());
                pMutex_->lock();
                pLogger_queue_->push(Logger(errormsg, 
                    Logger::LoggerType::SERVER, Logger::LoggerStatus::PROCESSED, Logger::LoggerInfo::ERROR));
                pMutex_->unlock();
                do_write();
            }
        };
    boost::asio::async_read(socket_, boost::asio::buffer(pkt->body(), pkt->getBodyLen()), f);
}

// 패킷 송신 기록을 기록해야함
// Logger 받아서 PROCESSED 처리해줘야함
// pLog->setContents(fmt::format("Send packet of {} len", write_len_));
// pLog->setStatus(Logger::LoggerStatus::PROCESSED);
void Session::do_write()
{
    auto self(shared_from_this());
    auto f = [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                do_read_header();
            }
        };
    // boost::asio::async_write(socket_, boost::asio::buffer(pEvt_->getEventPacket().body(), 
    //     pEvt_->getEventPacket().getBodyLen()), f);
    boost::asio::async_write(socket_, boost::asio::buffer(pkt->data(), pkt->getLen()), f);
}