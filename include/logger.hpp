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