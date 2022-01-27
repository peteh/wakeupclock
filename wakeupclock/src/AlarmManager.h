#pragma once
#include <Arduino.h>
#include "Alarm.h"
class AlarmManager{

    public: 
    /**
     * @brief Gets the number of alarms storable. 
     * 
     * @return uint8_t number of alarms
     */
    uint8_t getAlarmNum();

    uint8_t getHour(uint8_t alarmId);
    uint8_t getHour(uint8_t alarmId);
    uint8_t isEnabled(uint8_t alarmId);
    uint8_t isDayEnabled(uint8_t day);

    private:
    static const int MAX_ALARMS = 5;
    Alarm* m_alarms[MAX_ALARMS];

};