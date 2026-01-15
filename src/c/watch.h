#pragma once

void time_update();
void tz_change(int minutes);
int tz_get();
extern int watch_battery;
void charge_update(BatteryChargeState charge_state);
void connection_update(bool connected);
void pebblekit_update(bool connected);
