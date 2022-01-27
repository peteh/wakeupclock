#pragma once
#include <lvgl.h>
#include "ClockEditWidget.h"

class ClockScreen
{
public:
    ClockScreen();
    bool loop();

    lv_obj_t* getScreen(){
        return m_screen;
    }


private:
    lv_obj_t *m_screen;
};