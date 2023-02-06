#include <logger.hpp>
#include <iostream>

std::string Logger::makeConetnts()
{
    switch (type_)
    {
    case LoggerType::SERVER:
        return fmt::format("{:>10} {}", "[SERVER]", content_);
    case LoggerType::PROCESS:
        return fmt::format("{:>10} {}", "[PROCESS]", content_);
    case LoggerType::UNDEFINED:
        return fmt::format("{:>10} {}", "[UNDEFINED]", content_);
    default:
        return fmt::format("{:>10} {}", "[UNKNOWN]", content_);
    }
}

void Logger::printLog()
{
    std::string contents;

    if (this->getStatus() != Logger::LoggerStatus::PROCESSED)
    {
        switch (type_)
        {
        case LoggerType::SERVER:
            contents = fmt::format("{:>10} {}", "[SERVER]", "Attempt to write an unprocessed Logger.");
            break;
        case LoggerType::PROCESS:
            contents = fmt::format("{:>10} {}", "[PROCESS]", "Attempt to write an unprocessed Logger.");
            break;
        case LoggerType::UNDEFINED:
            contents = fmt::format("{:>10} {}", "[UNDEFINED]", "Attempt to write an unprocessed Logger.");
            break;
        default:
            contents = fmt::format("{:>10} {}", "[UNKNOWN]", "Attempt to write an unprocessed Logger.");
            break;
        }
        pLogger_->warn(contents);
    }
    else
    {
        contents = makeConetnts();
        switch (status_)
        {
        case LoggerInfo::INFO:
            pLogger_->info(contents);
            break;
        case LoggerInfo::WARNING:
            pLogger_->warn(contents);
            break;
        case LoggerInfo::ERROR:
            pLogger_->error(contents);
            break;
        case LoggerInfo::ETC:
            pLogger_->critical(contents);
            break;
        default:
            pLogger_->critical(contents);
            break;
        }
    }
}
