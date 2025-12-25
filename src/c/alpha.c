#include <pebble.h>

#include "display.h"
#include "watch.h"
#include "phone.h"
#include "dict.h"

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

    connection_update(connection_service_peek_pebble_app_connection());
    pebblekit_update(connection_service_peek_pebblekit_connection());
    connection_service_subscribe((ConnectionHandlers){connection_update, pebblekit_update});

    phone_init();

    app_message_register_inbox_received(dict_parse);
    app_message_open(32, 16);
}

static void deinit() {
    app_message_deregister_callbacks();
    connection_service_unsubscribe();
    battery_state_service_unsubscribe();
    tick_timer_service_unsubscribe();
    window_destroy(s_main_window);
}

int main(void) {
    init();
    app_event_loop();
    deinit();
}
