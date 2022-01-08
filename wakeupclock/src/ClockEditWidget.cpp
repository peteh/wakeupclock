#include "ClockEditWidget.h"

#include <Arduino.h>
const char *ClockEditWidget::WEEKDAY_MAP[] = {"M", "T", "W", "T", "F", "S", "S", NULL};

void ClockEditWidget::callBack(lv_event_t *e)
{
    if (e->target == m_rollerHour)
    {
        lv_event_code_t code = lv_event_get_code(e);
        lv_obj_t *obj = lv_event_get_target(e);
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            char buf[32];
            lv_roller_get_selected_str(obj, buf, sizeof(buf));
            uint16_t index = lv_roller_get_selected(obj);
            Serial.printf("Hour selected value: %s (Index %d)", buf, index);
            setHour(index);
        }
    }

    if (e->target == m_rollerMinute)
    {
        lv_event_code_t code = lv_event_get_code(e);
        lv_obj_t *obj = lv_event_get_target(e);
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            char buf[32];
            lv_roller_get_selected_str(obj, buf, sizeof(buf));
            uint16_t index = lv_roller_get_selected(obj);
            Serial.printf("Minute selected value: %s (Index %d)", buf, index);
            setMinute(index);
        }
    }
}

ClockEditWidget::ClockEditWidget(lv_obj_t *parent, uint8_t hour, uint8_t minute)
{
    m_bntMatrixWeekdayEnabled = lv_btnmatrix_create(parent);
    lv_btnmatrix_set_map(m_bntMatrixWeekdayEnabled, WEEKDAY_MAP);
    lv_btnmatrix_set_btn_ctrl_all(m_bntMatrixWeekdayEnabled, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_obj_set_height(m_bntMatrixWeekdayEnabled, 60);
    lv_obj_align(m_bntMatrixWeekdayEnabled, LV_ALIGN_BOTTOM_MID, 0, -20);

    // Create enable switch
    m_switchEnabled = lv_switch_create(parent);
    lv_obj_align(m_switchEnabled, LV_ALIGN_CENTER, 0, -50);
    lv_obj_add_event_cb(m_switchEnabled, lvhelper_userdata_event_handler, LV_EVENT_ALL, this);
    lv_obj_align(m_switchEnabled, LV_ALIGN_BOTTOM_RIGHT, -40, -40);

    // Create hour selector
    m_rollerHour = lv_roller_create(parent);
    lv_roller_set_options(m_rollerHour, HOUR_VALUES,
                          LV_ROLLER_MODE_NORMAL);
    lv_obj_align(m_rollerHour, LV_ALIGN_CENTER, -40, -40);

    // attach our callback to user data
    lv_obj_set_user_data(m_rollerHour, this);
    lv_obj_add_event_cb(m_rollerHour, lvhelper_userdata_event_handler, LV_EVENT_ALL, this);

    // Create minute selector
    m_rollerMinute = lv_roller_create(parent);
    lv_roller_set_options(m_rollerMinute, MINUTE_VALUES,
                          LV_ROLLER_MODE_NORMAL);
    lv_obj_align(m_rollerMinute, LV_ALIGN_CENTER, +40, -40);

    // attach our callback to user data
    lv_obj_set_user_data(m_rollerMinute, this);
    lv_obj_add_event_cb(m_rollerMinute, lvhelper_userdata_event_handler, LV_EVENT_ALL, this);
}