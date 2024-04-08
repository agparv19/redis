#include <iostream>
#include <chrono>

int main() {
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Add 5 seconds to the current time
    auto now_plus_5_seconds = now + std::chrono::seconds(5);

    // Output the updated time
    std::cout << "Current time: " << std::chrono::system_clock::to_time_t(now) << std::endl;
    std::cout << "Current time plus 5 seconds: " << std::chrono::system_clock::to_time_t(now_plus_5_seconds) << std::endl;

    return 0;
}
