#include "Timer.h"

Timer::Timer() : elapsedTime(0) { start(); }

void Timer::start() {
    startTime = std::chrono::steady_clock::now();
}


void Timer::update() {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::duration<long long, std::milli> duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
    elapsedTime = duration.count();
}

std::string Timer::getFormattedTime() const {
    int milliseconds = static_cast<int>(elapsedTime % 1000);
    int seconds = static_cast<int>((elapsedTime / 1000) % 60);
    int minutes = static_cast<int>((elapsedTime / 60000) % 60);
    int hours = static_cast<int>(elapsedTime / 3600000);
    
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":"
       << std::setw(2) << std::setfill('0') << minutes << ":"
       << std::setw(2) << std::setfill('0') << seconds << "."
       << std::setw(3) << std::setfill('0') << milliseconds;

    return ss.str();
}

