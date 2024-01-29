#ifndef CONCEPTAPP_TIMER_ELEMENTS_H
#define CONCEPTAPP_TIMER_ELEMENTS_H

#include "precompiled.h"
#include <QString>
#include <ctime>

class QX_CONCEPTAPP_DLL_EXPORT timerElements {
public:
    long id;
    double totalFocusTime;
    double totalBreakTime;
    time_t startTime;
};

QX_REGISTER_HPP_QX_CONCEPTAPP(timerElements, qx::trait::no_base_class_defined, 0)
#endif
