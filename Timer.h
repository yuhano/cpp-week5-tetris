#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>

class Timer {
public:
    // 생성자
    Timer();

    // 초기화
    void start();

    // 시간 업데이트
    void update();

    // start 시간부터 지금 시간 차이를 string 형식으로 변환
    std::string getFormattedTime() const;

private:
    std::chrono::steady_clock::time_point startTime;
    long long elapsedTime; // milliseconds
};

#endif
