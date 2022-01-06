#include "ClockEditWidget.h"

#include <Arduino.h>
const char *ClockEditWidget::WEEKDAY_MAP[] = {"M", "T", "W", "T", "F", "S", NULL};

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
    : m_hour(hour),
      m_minute(minute),
      m_rollerHour(NULL),
      m_rollerMinute(NULL)
{

    lv_obj_t *btnm1 = lv_btnmatrix_create(parent);
    lv_btnmatrix_set_btn_ctrl_all(btnm1, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_set_map(btnm1, WEEKDAY_MAP);
    lv_obj_align(btnm1, LV_ALIGN_BOTTOM_RIGHT, 0, 0);

    /*Create a container with ROW flex direction*/
    lv_obj_t *cont_row = lv_obj_create(parent);
    lv_obj_set_size(cont_row, 300, 75);
    lv_obj_align(cont_row, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW);

    m_rollerHour = lv_roller_create(cont_row);
    lv_roller_set_options(m_rollerHour, HOUR_VALUES,
                          LV_ROLLER_MODE_NORMAL);
    
    // attach our callback to user data
    lv_obj_set_user_data(m_rollerHour, this);
    lv_obj_add_event_cb(m_rollerHour, lvhelper_userdata_event_handler, LV_EVENT_ALL, this);

    m_rollerMinute = lv_roller_create(cont_row);
    lv_roller_set_options(m_rollerMinute, MINUTE_VALUES,
                          LV_ROLLER_MODE_NORMAL);

    // attach our callback to user data
    lv_obj_set_user_data(m_rollerMinute, this);
    lv_obj_add_event_cb(m_rollerMinute, lvhelper_userdata_event_handler, LV_EVENT_ALL, this);
}