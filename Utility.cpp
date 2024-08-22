#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <format>
#include "Logger.h"

using namespace std;
using namespace Logger;

namespace Utils
{
    bool to_bool(string str)
    {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        istringstream is(str);
        bool b;
        is >> boolalpha >> b;
        return b;
    }

    [[noreturn]]
    void dieWithError(string message, uint32_t errorCode)
    {
        Log->Error(message);
        Log->Error(format("Exiting with error : {}", errorCode));
        exit(errorCode);
    }
}