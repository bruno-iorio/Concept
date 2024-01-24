//studytimer.cpp

#include "studytimer.h"
using namespace std;


int Timer::storeTimer() {

    time_t end_time = get_time();

    // attributes to store in database:

    // start_timeis attribute of object
    // total_time attribute of object
    // end_time declared here

    return 0;
}

int Timer::stopTimer() {

    counting = 0;
    time_t time = get_time();
    total_time += difftime(time, last_start_time);
    storeTimer();

    return 0;

}

int Timer::display() {

    cout << "Time: " << minute << ":" << second << endl;

    return 0;
}

int Timer::activeCounting() {

    if (finished) {
        stopTimer();
    }
    else {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        update_time();    }

    return 0;

}

int Timer::userPause() {

    counting = 0;
    std::time_t time = get_time();
    total_time += difftime(time, last_start_time);
    display();

    return 0;
}

int Timer::userContinue() {

    counting = 1;
    last_start_time = get_time();

    while (counting) {
        activeCounting();
    }

    return 0;

}

int startTimer(Timer *timer_pointer) {

    (*timer_pointer).last_start_time = (*timer_pointer).get_time();

    (*timer_pointer).counting = 1;
    while ((*timer_pointer).counting) {
        (*timer_pointer).activeCounting();
    }

    return 0;
}



CountUpTimer* initializeZeroTimer() {
    return new CountUpTimer();
}

CountDownTimer* initializeFocusTimer(int s, int m, int h) {
    return new CountDownTimer(s,m, h);
}

Timer userStartsZeroTimer() {

    CountUpTimer* timer = initializeZeroTimer();
    startTimer(timer);

    return *timer;
}

Timer userStartsFocusTimer(int s, int m, int h) {

    CountDownTimer* timer = initializeFocusTimer(s, m, h);
    startTimer(timer);

    return *timer;
}



