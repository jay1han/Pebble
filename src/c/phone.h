#pragma once

void phone_init();

void phone_charge(int batt, bool charging);
void phone_net(char *text);
void phone_wifi(char *text);
void phone_bt(char *text);
void phone_dnd(bool quiet);
void phone_noti(char *text);
