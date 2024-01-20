//studytimer.h

#ifndef STUDYTIMER_H
#define STUDYTIMER_H
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

class Timer
{
public:

    int second;
    int minute;
    int hour;
    int current_second;
    int current_minute;
    int current_hour;
    bool counting;
    bool finished;

    Timer(int min=0, int h=0) : second(0), minute(min), hour(h),counting(0), finished(0), current_second(second), current_minute(minute) {}

    virtual ~Timer() {}
    // IMPLEMENT IF NECESSARY
    time_t get_time() { //for storing system time
        std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
        time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
        return currentTime_t;
    }

    time_t start_time = get_time();
    time_t last_start_time = start_time;
    time_t end_time;
    int total_time = 0;

    int storeTimer();
    int display();
    int activeCounting();
    virtual bool update_time() {
        if (second != 59) {second ++;}
        else {second = 0;
            if (minute != 59) {minute ++;}
            else {minute = 0;
                hour ++;}
        }
        return finished;}


    int userPause();
    int userContinue();
    int stopTimer();



};

class CountUpTimer : public Timer {
public:

    CountUpTimer() : Timer() {};

    virtual bool update_timer() {
        if (second != 59) {
            second++;
        } else {
            if (minute != 59) {
                minute++;
                second = 0;
            } else {
                hour++;
                minute = 0;
                second = 0;
            }
        }
        return finished;
    }

};

class CountDownTimer : public Timer {
public:

    CountDownTimer(int focus_minutes, int focus_hours) : Timer(focus_minutes, focus_hours) {};



    virtual bool update_timer() {
        if (second != 0) {
            second--;
        } else {
            if (minute != 0) {
                minute--;
                second = 59;
            } else {
                if (hour != 0) {
                    hour--;
                    minute = 59;
                    second = 59;
                } else {
                    // Timer is finished
                    finished = true;
                }
            }
        }
        return finished;
    }

public slots:
    void startTimer() {
        // Your existing implementation here or any changes you want to make.
        while (counting) {
            activeCounting();
        }
    }

    // Inside the CountDownTimer class in studytimer.h
    QString getTime() const {
        return QString("%1:%2:%3").arg(current_hour, 2, 10, QChar('0')).arg(current_minute, 2, 10, QChar('0')).arg(current_second, 2, 10, QChar('0'));
    }

};

#endif // STUDYTIMER_H
