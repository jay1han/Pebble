#include <pebble.h>

#include "time.h"
#include "charge.h"

static Window *s_main_window;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  time_update();
}

static void charge_handler(BatteryChargeState charge_state) {
  charge_update(charge_state);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  time_create(window_layer, &bounds);
  charge_create(window_layer, &bounds);
}

static void main_window_unload(Window *window) {
  time_destroy();
  charge_destroy();
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
  battery_state_service_subscribe(charge_handler);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
