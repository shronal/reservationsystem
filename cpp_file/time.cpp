#include <iostream>
#include <ctime>

int main() {
    // Get current time
    time_t now = time(0);

    // Convert to local time format
    tm *localTime = localtime(&now);

    // Display date and time
    std::cout << "Current Date and Time: "
              << (localTime->tm_year + 1900) << "-"
              << (localTime->tm_mon + 1) << "-"
              << localTime->tm_mday << " "
              << localTime->tm_hour << ":"
              << localTime->tm_min << ":"
              << localTime->tm_sec
              << std::endl;

    return 0;
}
