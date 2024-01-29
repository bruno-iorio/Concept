//studytimer.h

#ifndef STUDYTIMER_H
#define STUDYTIMER_H
#include <chrono>
#include <thread>
#include <ctime>
#include <QObject>
#include <QTimer>

using namespace std;


class Timer
{
public:

    int second;
    int minute;
    int hour;

    bool counting;
    bool finished;
    bool countdowntimer;
    Timer(int sec=0, int min=0, int h=0) : second(sec), minute(min), hour(h),counting(0), finished(0), countdowntimer(0) {}

    virtual ~Timer() {}
    // IMPLEMENT IF NECESSARY
    time_t get_time() { //for storing system time
        std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
        time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
        return currentTime_t;
    } 

    time_t start_time;
    time_t last_start_time;
    time_t end_time;
    int total_time;

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

    CountUpTimer() : Timer(0,0,0) {};

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

    CountDownTimer(int sec, int min, int h) : Timer(sec, min, h) {
        countdowntimer = 1;
    };



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


};

#endif // STUDYTIMER_H
