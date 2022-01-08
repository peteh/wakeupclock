#pragma once
#include <lvgl.h>
#include "ClockEditWidget.h"
class AlarmEditScreen
{
public:
    AlarmEditScreen();
    lv_obj_t* getScreen(){
        return m_screen;
    }

private:
    lv_obj_t *m_screen;
    lv_obj_t *m_pageSelector;
    ClockEditWidget *m_clockEditWidget;
};