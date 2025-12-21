#include <pebble.h>

#include "display.h"
#include "watch.h"
#include "phone.h"

static Window *s_main_window;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  time_update();
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  disp_create(window_layer);
}

static void main_window_unload(Window *window) {
  disp_destroy();
}

static void init() {
  s_main_window = window_create();

  window_set_window_handlers(s_main_window, (WindowHandlers) {
      .load = main_window_load,
      .unload = main_window_unload
    });
  
  window_stack_push(s_main_window, true);

  time_update();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  charge_update(battery_state_service_peek());
  battery_state_service_subscribe(charge_update);

  phone_init();
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
