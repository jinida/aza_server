<<<<<<< HEAD
#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <string>
#include <fstream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class Logger
{
public:
    Logger() = default;
    ~Logger() = default;
    enum LoggerStatus { GENEARTED, ENQUEUED, PROCESSED, UNDEFINED };
    enum LoggerInfo { INFO, WARNING, ERROR, ETC };
    enum LoggerType { SERVER, PROCESS, UNDEFINED };
    Logger(std::shared_ptr<spdlog::logger> pLogger, LoggerType type, LoggerStatus st, LoggerInfo info)
        : type_(type), status_(st), pLogger_(pLogger), info_(info) {}
    Logger(std::shared_ptr<spdlog::logger> pLogger, std::string content, LoggerType type, LoggerStatus st)
        : type_(type), status_(st), content_(content), pLogger_(pLogger) {}
    Logger(std::shared_ptr<spdlog::logger> pLogger, std::string content, LoggerType type, LoggerStatus st, LoggerInfo info)
        : type_(type), status_(st), content_(content), pLogger_(pLogger), info_(info) {}
    LoggerStatus getStatus() const { return status_; }
    void setStatus(LoggerStatus status) { this->status_ = status; }
    void setContents(string content) { this->content_ = content; }
    void printLog();
private:
    std::string makeConetnts();
    LoggerStatus status_;
    LoggerInfo info_;
    LoggerType type_;
    std::string content_;
    std::shared_ptr<spdlog::logger> pLogger_;
};

#endif
=======
#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include "spdlog/spdlog.h"

class Logger
{
    friend ostream& operator<<(ostream& fout, const Event& e);
    public:
        Logger();
        ~Logger() = default;
        enum LoggerStatus { INFO, WARNING, ERROR, ETC };
    private:
        
}

#endif LOGGER_H
>>>>>>> a47a899b2fa2d48d198ca373cd7a857c218141dd
