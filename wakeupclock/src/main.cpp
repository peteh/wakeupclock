#include <Arduino.h>
#include <lvgl.h>
#include <lv_conf.h>
#include <TFT_eSPI.h>
#include "FT62XXTouchScreen.h"
#include "Backlight.h"
#include "AlarmEditScreen.h"
#include "ClockScreen.h"
/*Change to your screen resolution*/
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
FT62XXTouchScreen touchScreen = FT62XXTouchScreen(TFT_WIDTH, PIN_SDA, PIN_SCL);
Backlight backlight = Backlight(TFT_BL, 0);

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf)
{
  Serial.printf(buf);
  Serial.flush();
}
#endif

lv_obj_t *btn1;
lv_obj_t *btn2;
AlarmEditScreen *screenAlarmEdit;
ClockScreen *screenClock;
lv_obj_t *screenSettings;
lv_obj_t *label;

lv_obj_t *slider_label;
lv_obj_t *slider;

static void slider_event_cb(lv_event_t *e)
{
  lv_obj_t *slider = lv_event_get_target(e);
  char buf[8];
  backlight.setBrightness((uint8_t)lv_slider_get_value(slider));
  lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
  lv_label_set_text(slider_label, buf);
  lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  // Serial.println("#");
  TouchPoint touchPos = touchScreen.read();

  if (!touchPos.touched)
  {
    data->state = LV_INDEV_STATE_RELEASED;
  }
  else
  {
    data->state = LV_INDEV_STATE_PRESSED;

    /*Set the coordinates*/
    data->point.x = touchPos.xPos;
    data->point.y = touchPos.yPos;

    Serial.print("Data x ");
    Serial.println(data->point.x);

    Serial.print("Data y ");
    Serial.println(data->point.y);
  }
}



ClockEditWidget *cew;
void setup()
{
  Serial.begin(115200); /* prepare for possible serial debug */

  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println(LVGL_Arduino);
  Serial.println("I am LVGL_Arduino");

  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  // Enable Backlight

  tft.begin();        /* TFT init */
  tft.setRotation(1); /* Landscape orientation, flipped */

  // Start TouchScreen
  touchScreen.begin();

  // set backlight
  backlight.begin(20);

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // Screen Object
  screenAlarmEdit = new AlarmEditScreen();
  screenClock = new ClockScreen();
  
  screenSettings = lv_obj_create(NULL);
  
  /*Create a slider in the center of the display*/
  slider = lv_slider_create(screenSettings);
  lv_obj_center(slider);
  lv_slider_set_range(slider, 0, 255);
  lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  /*Create a label below the slider*/
  slider_label = lv_label_create(screenSettings);
  lv_label_set_text(slider_label, "0%");
  lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

  // Screen load
  //lv_scr_load(screenAlarmEdit->getScreen());
  lv_scr_load(screenClock->getScreen());
  Serial.println("Setup done");
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}