#pragma once

void phone_init();

void phone_charge(int batt, bool charging);
void phone_net(int gen);
void phone_wifi(char *text);
void phone_bt(char *id, int charge);
void phone_dnd(bool quiet);
void phone_noti(char *text);
