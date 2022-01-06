#pragma once

#include <lvgl.h>

class ClockEditWidget
{
public:
    ClockEditWidget(lv_obj_t *parent, uint8_t hour = 0, uint8_t minute = 0);
    ~ClockEditWidget();

private:
    uint8_t m_hour;
    uint8_t m_minute;
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