#include <Arduino.h>
#include <lvgl.h>
#include "display.h"
#include "esp_bsp.h"

static lv_obj_t *status_label;
static const char *names[] = {"RED", "GREEN", "BLUE"};
static const uint32_t rgb[] = {0xFF0000, 0x00FF00, 0x0000FF};
static uint32_t touches = 0;

static void on_press(lv_event_t *event) {
    const uintptr_t index = (uintptr_t)lv_event_get_user_data(event);
    lv_point_t point_px = {0, 0};
    lv_indev_t *input = lv_indev_get_act();
    if (input) lv_indev_get_point(input, &point_px);
    lv_label_set_text_fmt(status_label, "%s #%lu  x=%d y=%d",
        names[index], (unsigned long)++touches, point_px.x, point_px.y);
    Serial.printf("%s: x_px=%d y_px=%d\n", names[index], point_px.x, point_px.y);
}

void setup() {
    Serial.begin(115200);
    if (!psramFound()) {
        Serial.println("Octal PSRAM missing: check board configuration");
        while (true) delay(1000);
    }
    bsp_display_cfg_t cfg = {};
    cfg.lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    cfg.buffer_size = 320 * 480; // pixels; RGB565 uses 307200 bytes
    cfg.rotate = LV_DISP_ROT_NONE; // portrait: x=0..319, y=0..479
    if (!bsp_display_start_with_config(&cfg)) {
        Serial.println("Display/touch initialization failed");
        while (true) delay(1000);
    }
    ESP_ERROR_CHECK(bsp_display_backlight_on());
    if (!bsp_display_lock(0)) return; // 0 = wait indefinitely, milliseconds otherwise
    lv_obj_t *screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000000), 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    for (uintptr_t i = 0; i < 3; ++i) {
        lv_obj_t *button = lv_btn_create(screen);
        lv_obj_set_pos(button, 10, 10 + i * 130);
        lv_obj_set_size(button, 300, 120);
        lv_obj_set_style_bg_color(button, lv_color_hex(rgb[i]), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(button, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_radius(button, 0, LV_PART_MAIN);
        lv_obj_add_event_cb(button, on_press, LV_EVENT_PRESSED, (void *)i);
        lv_obj_t *label = lv_label_create(button);
        lv_label_set_text(label, names[i]);
        lv_obj_set_style_text_color(label, lv_color_hex(i == 1 ? 0x000000 : 0xFFFFFF), 0);
        lv_obj_center(label);
    }
    status_label = lv_label_create(screen);
    lv_label_set_text(status_label, "Touch RED, GREEN, BLUE");
    lv_obj_set_style_text_color(status_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(status_label, LV_ALIGN_BOTTOM_MID, 0, -25);
    bsp_display_unlock();
}

void loop() {
    delay(20); // vendor port supplies the LVGL task and millisecond tick
}
