#include <pebble.h>

#include "display.h"
#include "phone.h"

static char pbat[4];
static char net[4];
static char wifi[20];
static char btid[20];
static char btc[4];
static char dnd[4];
static char noti[16];

void phone_init() {
    disp_set(disp_noti, noti);
    disp_set(disp_pbat, pbat);
    disp_set(disp_btid, btid);
    disp_set(disp_btc , btc);
    disp_set(disp_dnd , dnd);
    disp_set(disp_wifi, wifi);
    disp_set(disp_net , net);
}

void phone_charge(int batt, bool charging) {
    char *p = pbat;
    if (charging) *(p++) = '+';
    if (batt >= 100) strncpy(p, "00", 3);
    else if (batt <= 0) pbat[0] = 0;
    else snprintf(p, 3, "%d", batt);
    pbat[3] = 0;
    disp_set(disp_pbat, pbat);
}

void phone_net(int gen) {
    if (gen > 0 && gen <= 5) snprintf(net, 3, "%dG", gen);
    else net[0] = 0;
    disp_set(disp_net, net);
}

void phone_wifi(char *text) {
    strncpy(wifi, text, sizeof(wifi));
    wifi[sizeof(wifi) - 1] = 0;
    disp_set(disp_wifi, wifi);
}

void phone_bt(char *id, int charge) {
    strncpy(btid, id, sizeof(btid));
    btid[sizeof(btid) - 1] = 0;
    disp_set(disp_btid, btid);
    
    if (charge >= 100) strcpy(btc, "00");
    else if (charge <= 0) btc[0] = 0;
    else snprintf(btc, 3, "%d", charge);
    disp_set(disp_btc, btc);
}

void phone_dnd(bool quiet) {
    if (quiet) strcpy(dnd, "X");
    else strcpy(dnd, " ");
    disp_set(disp_dnd, dnd);
}

void phone_noti(char *text) {
    strncpy(noti, text, sizeof(noti));
    noti[sizeof(noti) - 1] = 0;
    disp_set(disp_noti, noti);
}
