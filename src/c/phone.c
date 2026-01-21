#include <pebble.h>

#include "display.h"
#include "dict.h"
#include "phone.h"

static char pbat[4];
static char net[4];
static char sim[4];
static char plmn[20];
static char wifi[20];
static char btid[20];
static char btc[4];
static char bton[4];
static char dnd[4];
static char noti[16];

static bool changed[STOR_END];

void phone_init() {
    persist_read_string(STOR_PLMN_20, plmn, sizeof(plmn));
    persist_read_string(STOR_WIFI_20, wifi, sizeof(wifi));
    persist_read_string(STOR_BTID_20, btid, sizeof(btid));
    persist_read_string(STOR_NOTI_16, noti, sizeof(noti));
    
    disp_set(disp_noti, noti);
    disp_set(disp_btid, btid);
    disp_set(disp_net , net);
    if (wifi[0] != 0)
        disp_set(disp_wifi, wifi);
    else
        disp_set(disp_plmn, plmn);
}

void phone_deinit() {
    if (changed[STOR_PLMN_20])
        persist_write_string(STOR_PLMN_20, plmn);
    
    if (changed[STOR_WIFI_20])
        persist_write_string(STOR_WIFI_20, wifi);
    
    if (changed[STOR_BTID_20])
        persist_write_string(STOR_BTID_20, btid);
    
    if (changed[STOR_NOTI_16])
        persist_write_string(STOR_NOTI_16, noti);
}

void phone_charge(int batt, bool plugged, bool charging) {
    char *p = pbat;
    if (charging) *(p++) = '+';
    else if (plugged) *(p++) = ':';
    if (batt >= 100) strncpy(p, "00", 3);
    else if (batt <= 0) pbat[0] = 0;
    else snprintf(p, 3, "%d", batt);
    pbat[3] = 0;
    disp_set(disp_pbat, pbat);
}

void phone_net(int network_gen, int active_sim, char *carrier) {
    if (network_gen > 0 && network_gen <= 5)
        snprintf(net, 3, "%dG", network_gen);
    else net[0] = 0;
    disp_set(disp_net, net);

    char *p = sim;
    if (active_sim & 0x0F) *(p++) = '0' + (active_sim & 0x0F);
    if (active_sim & 0x10) *(p++) = 'R';
    *p = 0;
    disp_set(disp_sim, sim);

    if (strcmp(plmn, carrier)) {
        strncpy(plmn, carrier, sizeof(plmn) - 1);
        plmn[sizeof(plmn) - 1] = 0;
        changed[STOR_PLMN_20] = true;
    }
    
    if (wifi[0] == 0) {
        disp_set(disp_wifi, wifi);
        if (plmn[0] != 0) disp_set(disp_plmn, plmn);
    } else {
        if (plmn[0] != 0) disp_set(disp_plmn, "");
        disp_set(disp_wifi, wifi);
    }
}

void phone_wifi(char *text) {
    if (strcmp(wifi, text)) {
        strncpy(wifi, text, sizeof(wifi));
        wifi[sizeof(wifi) - 1] = 0;
    }
    
    if (wifi[0] == 0) {
        disp_set(disp_wifi, wifi);
        if (plmn[0] != 0) disp_set(disp_plmn, plmn);
    } else {
        if (plmn[0] != 0) disp_set(disp_plmn, "");
        disp_set(disp_wifi, wifi);
    }
}

void phone_bt(char *id, int charge, bool active) {
    if (strcmp(btid, id)) {
        strncpy(btid, id, sizeof(btid));
        btid[sizeof(btid) - 1] = 0;
    }
    disp_set(disp_btid, btid);
    
    if (charge >= 100) strcpy(btc, "00");
    else if (charge <= 0) btc[0] = 0;
    else snprintf(btc, 3, "%d", charge);
    disp_set(disp_btc, btc);

    if (active) strcpy(bton, "B");
    else bton[0] = 0;
    disp_set(disp_bton, bton);
}

void phone_dnd(bool quiet) {
    if (quiet) strcpy(dnd, "X");
    else strcpy(dnd, " ");
    disp_set(disp_dnd, dnd);
}

void phone_noti(char *text) {
    if (strcmp(noti, text)) {
        strncpy(noti, text, sizeof(noti));
        noti[sizeof(noti) - 1] = 0;
    }
    disp_set(disp_noti, noti);
}
