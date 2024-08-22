
#pragma once

#ifndef __LOGGER_H__
#define __LOGGER_H__

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include "Logger.h"

namespace Logger {
    class Logs
    {
    public:
        Logs();

        void Error(std::string logMessage);
        void Warn(std::string logMessage);
        void Console(std::string logMessage);
        void Exception(std::string logMessage, std::exception e);
        void Fatal(std::string logMessage, uint32_t exitCode);

    private:
        const char* commonFmt = "[{}]--[{}]--: {}";

        std::string dateTimeString();
        std::string logFileName;
        std::fstream logFile;
    };
    extern std::shared_ptr<Logger::Logs> Log;
}
#endif // __LOGGER_H__