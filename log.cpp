#include <iostream>

using namespace std;
string getCurrentTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char formattedTime[80];
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localTime);
    return string(formattedTime);
}