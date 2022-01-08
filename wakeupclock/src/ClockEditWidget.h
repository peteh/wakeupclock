#pragma once

#include <lvgl.h>
#include <helpers/ILVCallback.h>

class ClockEditWidget : public ILVCallback
{
public:
    ClockEditWidget(lv_obj_t *parent, uint8_t hour = 0, uint8_t minute = 0);
    void callBack(lv_event_t *e);
    ~ClockEditWidget(){};

private:
    void setHour(uint8_t hour)
    {
        // TODO boundaries
        lv_roller_set_selected(m_rollerHour, hour, LV_ANIM_OFF);
    }

    void setMinute(uint8_t minute)
    {
        // TODO boundaries
        lv_roller_set_selected(m_rollerMinute, minute, LV_ANIM_OFF);
    }

    void setWeekDayEnabled(uint8_t day, bool enabled)
    {
        if (enabled)
        {
            //lv_btnmatrix_set_selected_btn()
            //lv_obj_add_state(m_switchEnabled, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_state(m_switchEnabled, LV_STATE_CHECKED);
        }
    }

    void setEnabled(bool enabled)
    {
        if (enabled)
        {
            lv_obj_add_state(m_switchEnabled, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_state(m_switchEnabled, LV_STATE_CHECKED);
        }
    }

    bool getEnabled()
    {
        return lv_obj_has_state(m_switchEnabled, LV_STATE_CHECKED);
    }

    lv_obj_t *m_rollerHour = NULL;
    lv_obj_t *m_rollerMinute = NULL;

    lv_obj_t *m_switchEnabled = NULL;
    lv_obj_t *m_bntMatrixWeekdayEnabled = NULL;

    const static char *WEEKDAY_MAP[];
    const char *HOUR_VALUES = "00\n"
                              "01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n"
                              "11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n"
                              "21\n22\n23\n23";
    const char *MINUTE_VALUES = "00\n"
                                "01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n"
                                "11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n"
                                "21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n"
                                "31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n"
                                "41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n"
                                "51\n52\n53\n54\n55\n56\n57\n58\n59\n";
    ;
};