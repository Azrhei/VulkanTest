#define _CRT_SECURE_NO_WARNINGS
#include <format>
#include <chrono>
#include <iostream>
#include "Utility.h"
#include "color.hpp"
#include <fstream>
#include "Settings.h"
#include "Logger.h"

using namespace std;
using namespace Settings;

namespace Logger {
    Logs::Logs()
    {
        //logFileName = Conf->logFileName();
        //logFile.open(logFileName, fstream::app);
    }

    void Logs::Warn(std::string logMessage)
    {
        string formatOutput = std::format("[{}]--[{}]--: {}", "ERROR", dateTimeString(), logMessage);

        logFile << formatOutput << nl;
        cerr << formatOutput << nl;
    }

    void Logs::Error(std::string logMessage)
    {
        string formatOutput = std::format("[{}]--[{}]--: {}","ERROR", dateTimeString(), logMessage);

        logFile << formatOutput << nl;
        cerr << formatOutput << nl;
    }

    void Logs::Console(string logMessage)
    {
        string formatOutput = format("[{}]--[{}]--: {}","CONSOLE", dateTimeString(), logMessage);

        logFile << formatOutput << nl;
        cout << formatOutput  << nl;
    }


    void Logs::Exception(std::string logMessage, std::exception e)
    {
        string formatOutput = format("[{}]--[{}]--: {}", "EXCEPTION", dateTimeString(), logMessage);

        logFile << formatOutput << nl;
        cerr << formatOutput << nl;
        cout << formatOutput << nl;

        throw e;
    }

    void Logs::Fatal(std::string logMessage, uint32_t exitCode)
    {
        string formatOutput = format("[{}]--[{}]--: {}", "FATAL", dateTimeString(), logMessage);

        logFile << formatOutput << nl;
        cerr <<  formatOutput  << nl;
        cout << formatOutput << nl;

        exit(exitCode);
    }

    string Logs::dateTimeString()
    {
        string timeformat{ "%m-%d-%Y::%X" };
        stringstream ss{};
        std::time_t t = std::time(nullptr);
        ss << put_time<char>(std::localtime(&t), timeformat.c_str());
        return ss.str();
    }
    shared_ptr<Logs> Log{};
}

