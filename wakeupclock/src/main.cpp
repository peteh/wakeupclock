#include <lvgl.h>
#include <lv_conf.h>
#include <TFT_eSPI.h>
#include "FT62XXTouchScreen.h"
/*If you want to use the LVGL examples,
  make sure to install the lv_examples Arduino library
  and uncomment the following line.
#include <lv_examples.h>
*/

/*Change to your screen resolution*/
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
FT62XXTouchScreen touchScreen = FT62XXTouchScreen(TFT_WIDTH, PIN_SDA, PIN_SCL);

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
lv_obj_t *screenMain;
lv_obj_t *label;

static void event_handler_btn(lv_event_t *e)
{
  lv_obj_t *target = lv_event_get_target(e);
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED)
  {
    if (target == btn1)
      lv_label_set_text(label, "Hello");
    else if (target == btn2)
    {
      lv_label_set_text(label, "Goodbye");
    }
  }
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
  //Serial.println("#");
  uint16_t touchX, touchY;

  TouchPoint touchPos = touchScreen.read();

  if (!touchPos.touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;

    /*Set the coordinates*/
    data->point.x = touchPos.xPos;
    data->point.y = touchPos.yPos;

    Serial.print("Data x ");
    Serial.println(data->point.x);

    Serial.print("Data y ");
    Serial.println(data->point.y);
  }
}

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
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, 1);
  tft.begin();        /* TFT init */
  tft.setRotation(1); /* Landscape orientation, flipped */

  /*Set the touchscreen calibration data,
   the actual data for your display can be aquired using
   the Generic -> Touch_calibrate example from the TFT_eSPI library*/
  uint16_t calData[5] = {275, 3620, 264, 3532, 1};
  // TODO
  // tft.setTouch( calData );

  // Start TouchScreen
  touchScreen.begin();

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

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // Screen Object
  screenMain = lv_obj_create(NULL);

  // Text
  label = lv_label_create(screenMain);
  lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
  lv_label_set_text(label, "Press a button");
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_size(label, 240, 40);
  lv_obj_set_pos(label, 0, 15);

  // BUtton 1
  btn1 = lv_btn_create(screenMain);
  lv_obj_add_event_cb(btn1, event_handler_btn, LV_EVENT_ALL, NULL);
  lv_obj_set_width(btn1, 90);
  lv_obj_set_height(btn1, 32);
  lv_obj_set_pos(btn1, 32, 100);
  lv_obj_t *label1 = lv_label_create(btn1);
  lv_label_set_text(label1, "Hello");
  lv_obj_center(label1);

  // Button 2
  btn2 = lv_btn_create(screenMain);
  lv_obj_add_event_cb(btn2, event_handler_btn, LV_EVENT_ALL, NULL);
  lv_obj_set_width(btn2, 90);
  lv_obj_set_height(btn2, 32);
  lv_obj_set_pos(btn2, 142, 100);
  lv_obj_t *label2 = lv_label_create(btn2);
  lv_label_set_text(label2, "Goodbye");
  lv_obj_center(label2);
  // Screen load
  lv_scr_load(screenMain);

  Serial.println("Setup done");
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}