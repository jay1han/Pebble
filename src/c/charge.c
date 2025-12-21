#include <pebble.h>

#include "display.h"

static char charge_text[4];

void charge_update(BatteryChargeState charge_state) {

  if (charge_state.charge_percent >= 100) strcpy(charge_text, "00");
  else {
    snprintf(charge_text, sizeof(charge_text), "%d",
	     charge_state.charge_percent);
  }
  disp_set(disp_wbat, charge_text);
}
 
void charge_create(Layer *window_layer) {
  disp_create(disp_wbat, window_layer);
  charge_update(battery_state_service_peek());
}

void charge_destroy() {
  disp_destroy(disp_wbat);
}
