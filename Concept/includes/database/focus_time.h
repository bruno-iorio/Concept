//
// Created by hung3a8 on 29/12/2023.
//

#ifndef CONCEPTAPP_FOCUS_TIME_H
#define CONCEPTAPP_FOCUS_TIME_H

class FocusTime {
public:
    long id;
    QDateTime start_time;
    QDateTime end_time;
    QDateTime time_spent;

    FocusTime() : id(0) { ; }
    virtual ~FocusTime() { ; }
};

QX_REGISTER_HPP(FocusTime, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<FocusTime> FocusTime_ptr;
typedef std::vector<FocusTime_ptr> list_FocusTime;

#endif //CONCEPTAPP_FOCUS_TIME_H
