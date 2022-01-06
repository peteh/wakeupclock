#pragma once 
#include <lvgl.h>
class ILVCallback
{
    public:
        virtual ~ILVCallback() {}
        virtual void callBack(lv_event_t *e) = 0;
};

static void lvhelper_userdata_event_handler(lv_event_t * e)
{
    // call the user data event handler
    ((ILVCallback*) (e->user_data))->callBack(e);
}