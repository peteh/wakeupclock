#include "ClockEditWidget.h"

const char *ClockEditWidget::WEEKDAY_MAP[] = {"M", "T", "W", "T", "F", "S", NULL};

ClockEditWidget::ClockEditWidget(lv_obj_t *parent, uint8_t hour, uint8_t minute)
    : m_hour(hour),
      m_minute(minute)
{

    lv_obj_t *btnm1 = lv_btnmatrix_create(parent);
    lv_btnmatrix_set_map(btnm1, WEEKDAY_MAP);
    for (int i = 0; WEEKDAY_MAP[i] != NULL; i++)
    {
        lv_btnmatrix_set_btn_ctrl(btnm1, i, LV_BTNMATRIX_CTRL_CHECKABLE);
    }
    lv_obj_align(btnm1, LV_ALIGN_BOTTOM_RIGHT, 0, 0);

    /*Create a container with ROW flex direction*/
    lv_obj_t * cont_row = lv_obj_create(parent);
    lv_obj_set_size(cont_row, 300, 75);
    lv_obj_align(cont_row, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW);

    lv_obj_t *rollerHour = lv_roller_create(cont_row);
    lv_roller_set_options(rollerHour, HOUR_VALUES,
                        LV_ROLLER_MODE_NORMAL);

    lv_obj_t *rollerMinute = lv_roller_create(cont_row);
    lv_roller_set_options(rollerMinute, MINUTE_VALUES,
                        LV_ROLLER_MODE_NORMAL);
}