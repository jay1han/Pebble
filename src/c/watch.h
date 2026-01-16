#pragma once

void time_update();
void tz_change(int minutes);
int tz_get();
extern BatteryChargeState watch_battery;
void charge_update(BatteryChargeState charge_state);
void connection_update(bool connected);
void pebblekit_update(bool connected);
void outbox_failed(DictionaryIterator *iter, AppMessageResult reason, void *context);
void outbox_sent(DictionaryIterator *iter, void *context);
void inbox_dropped(AppMessageResult reason, void *context);
