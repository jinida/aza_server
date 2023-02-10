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
    enum LoggerStatus { GENEARTED, ENQUEUED, PROCESSED};
    enum LoggerInfo { INFO, WARNING, ERROR, ETC };
    enum LoggerType { SERVER, PROCESS, UNDEFINED };
    Logger(LoggerType type, LoggerStatus st, LoggerInfo info)
        : type_(type), status_(st), info_(info) {}
    Logger(std::string content, LoggerType type, LoggerStatus st)
        : type_(type), status_(st), content_(content) {}
    Logger(std::string content, LoggerType type, LoggerStatus st, LoggerInfo info)
        : type_(type), status_(st), content_(content), info_(info) {}
    LoggerStatus getStatus() const { return status_; }
    void setStatus(LoggerStatus status) { this->status_ = status; }
    void setContents(std::string content) { this->content_ = content; }
    void printLog(std::shared_ptr<spdlog::logger> pLogger_);
private:
    std::string makeConetnts();
    LoggerStatus status_;
    LoggerInfo info_;
    LoggerType type_;
    std::string content_;
};

#endif
