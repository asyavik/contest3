#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <ctime>

class Tracer {
    std::vector<std::pair<std::string, std::string>> messages;
public:
    void add_message(std::string message) {
        time_t rawtime;
        struct tm timeinfo;

        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
        std::string current_time(buffer);

        if (!current_time.empty() && current_time.back() == '\n') {
            current_time.pop_back();
        }
        messages.push_back({ message, current_time });

    }
    void print_all_messages() {
        std::cout << "Stack:" << "\n";
        for (size_t i = 0; i < messages.size(); i++) {
            std::cout << i + 1 << ' ' << messages[i].second << ' ' << messages[i].first << "\n";
        }
    }
};