#include <pebble.h>

#include "display.h"
#include "phone.h"

static char pbat[4]  = "00";
static char pchg[4]  = "?";
static char net[4]   = "0G";
static char wifi[20] = "";
static char btid[20] = "";
static char btc[4]   = "00";
static char dnd[4]   = "?";
static char noti[12] = "-";

void phone_init() {
    disp_set(disp_noti, noti);
    disp_set(disp_pbat, pbat);
    disp_set(disp_pchg, pchg);
    disp_set(disp_btid, btid);
    disp_set(disp_btc , btc);
    disp_set(disp_dnd , dnd);
    disp_set(disp_wifi, wifi);
    disp_set(disp_net , net);
}

void phone_charge(int batt, bool charging) {
    snprintf(pbat, sizeof(pbat), "%d", batt);
    disp_set(disp_pbat, pbat);
  
    pchg[0] = charging ? 'C' : ' ';
    pchg[1] = 0;
    disp_set(disp_pchg, pchg);
}

void phone_net(int gen) {
    snprintf(net, sizeof(net), "%dG", gen);
    disp_set(disp_net, net);
}

void phone_wifi(char *text) {
    strncpy(wifi, text, sizeof(wifi) - 1);
    disp_set(disp_wifi, wifi);
}

void phone_bt(char *id, int charge) {
    strncpy(btid, id, sizeof(btid) - 1);
    disp_set(disp_btid, btid);
    if (charge == 100) strcpy(btc, "00");
    else snprintf(btc, sizeof(btc), "%d", charge);
    disp_set(disp_btc, btc);
}

void phone_dnd(bool quiet) {
    if (quiet) strcpy(dnd, "X");
    else strcpy(dnd, " ");
    disp_set(disp_dnd, dnd);
}

void phone_noti(char *text) {
    strncpy(noti, text, sizeof(noti) - 1);
    disp_set(disp_noti, noti);
}
