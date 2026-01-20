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

void phone_init() {
    persist_read_string(STOR_PBAT_4,  pbat, sizeof(pbat));
    persist_read_string(STOR_NET_4,   net,  sizeof(net));
    persist_read_string(STOR_SIM_4,   sim,  sizeof(sim));
    persist_read_string(STOR_PLMN_20, plmn, sizeof(plmn));
    persist_read_string(STOR_WIFI_20, wifi, sizeof(wifi));
    persist_read_string(STOR_BTID_20, btid, sizeof(btid));
    persist_read_string(STOR_BTC_4,   btc,  sizeof(btc));
    persist_read_string(STOR_BTON_4,  bton, sizeof(bton));
    persist_read_string(STOR_DND_4,   dnd,  sizeof(dnd));
    persist_read_string(STOR_NOTI_16, noti, sizeof(noti));
    
    disp_set(disp_noti, noti);
    disp_set(disp_pbat, pbat);
    disp_set(disp_btid, btid);
    disp_set(disp_btc , btc);
    disp_set(disp_btc , bton);
    disp_set(disp_dnd , dnd);
    disp_set(disp_net , net);
    disp_set(disp_sim , sim);
    if (wifi[0] != 0)
        disp_set(disp_wifi, wifi);
    else
        disp_set(disp_plmn, plmn);
}

void phone_deinit() {
    char buffer[20];
    
    persist_read_string(STOR_PBAT_4, buffer, sizeof(pbat));
    if (strcmp(buffer, pbat) != 0)
        persist_write_string(STOR_PBAT_4, pbat);
    
    persist_read_string(STOR_NET_4, buffer, sizeof(net));
    if (strcmp(buffer, net) != 0)
        persist_write_string(STOR_NET_4, net);
    
    persist_read_string(STOR_SIM_4, buffer, sizeof(sim));
    if (strcmp(buffer, sim) != 0)
        persist_write_string(STOR_SIM_4, sim);
    
    persist_read_string(STOR_PLMN_20, buffer, sizeof(plmn));
    if (strcmp(buffer, plmn) != 0)
        persist_write_string(STOR_PLMN_20, plmn);
    
    persist_read_string(STOR_WIFI_20, buffer, sizeof(wifi));
    if (strcmp(buffer, wifi) != 0)
        persist_write_string(STOR_WIFI_20, wifi);
    
    persist_read_string(STOR_BTID_20, buffer, sizeof(btid));
    if (strcmp(buffer, btid) != 0)
        persist_write_string(STOR_BTID_20, btid);
    
    persist_read_string(STOR_BTC_4, buffer, sizeof(btc));
    if (strcmp(buffer, btc) != 0)
        persist_write_string(STOR_BTC_4, btc);
    
    persist_read_string(STOR_BTON_4, buffer, sizeof(bton));
    if (strcmp(buffer, bton) != 0)
        persist_write_string(STOR_BTON_4, bton);
    
    persist_read_string(STOR_DND_4, buffer, sizeof(dnd));
    if (strcmp(buffer, dnd) != 0)
        persist_write_string(STOR_DND_4, dnd);
    
    persist_read_string(STOR_NOTI_16, buffer, sizeof(noti));
    if (strcmp(buffer, noti) != 0)
        persist_write_string(STOR_NOTI_16, noti);
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

    strncpy(plmn, carrier, sizeof(plmn) - 1);
    plmn[sizeof(plmn) - 1] = 0;
    
    if (wifi[0] == 0) {
        disp_set(disp_wifi, wifi);
        if (plmn[0] != 0) disp_set(disp_plmn, plmn);
    } else {
        if (plmn[0] != 0) disp_set(disp_plmn, "");
        disp_set(disp_wifi, wifi);
    }
}

void phone_wifi(char *text) {
    strncpy(wifi, text, sizeof(wifi));
    wifi[sizeof(wifi) - 1] = 0;
    
    if (wifi[0] == 0) {
        disp_set(disp_wifi, wifi);
        if (plmn[0] != 0) disp_set(disp_plmn, plmn);
    } else {
        if (plmn[0] != 0) disp_set(disp_plmn, "");
        disp_set(disp_wifi, wifi);
    }
}

void phone_bt(char *id, int charge, bool active) {
    strncpy(btid, id, sizeof(btid));
    btid[sizeof(btid) - 1] = 0;
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
    strncpy(noti, text, sizeof(noti));
    noti[sizeof(noti) - 1] = 0;
    disp_set(disp_noti, noti);
}
