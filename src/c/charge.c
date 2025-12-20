#include <pebble.h>

static TextLayer *charge_layer;

void charge_update(BatteryChargeState charge_state) {
  static char charge_text[4];

  if (charge_state.charge_percent >= 100) strcpy(charge_text, "100");
  else {
    snprintf(charge_text, sizeof(charge_text), "%d%c",
	     charge_state.charge_percent,
	     charge_state.is_charging ? 'C' : '%');
  }
  text_layer_set_text(charge_layer, charge_text);
}
 
void charge_create(Layer *window_layer, GRect *bounds) {
  charge_layer = text_layer_create(GRect(0, 30, bounds->size.w, 50));
  text_layer_set_background_color(charge_layer, GColorClear);
  text_layer_set_text_color(charge_layer, GColorBlack);
  text_layer_set_text(charge_layer, "100");
  text_layer_set_font(charge_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(charge_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(charge_layer));

  charge_update(battery_state_service_peek());
}

void charge_destroy() {
  text_layer_destroy(charge_layer);
}
