#include <pebble.h>

#include "display.h"
#include "phone.h"

static char pbat[4]  = "80";
static char pchg[4]  = "C";
static char net[4]   = "5G";
static char wifi[20] = "ClimbingDistrict";
static char bt[20]   = "Phantom:90";
static char dnd[4]   = "Q";
static char noti[12] = "GKLMOSTWZ+";

void phone_init() {
  disp_set(disp_noti, noti);
  disp_set(disp_pbat, pbat);
  disp_set(disp_pchg, pchg);
  disp_set(disp_bt  , bt);
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

void phone_net(char *text) {
  strncpy(net, text, sizeof(net) - 1);
  disp_set(disp_net, net);
}

void phone_wifi(char *text) {
  strncpy(wifi, text, sizeof(wifi) - 1);
  disp_set(disp_wifi, wifi);
}

void phone_bt(char *text) {
  strncpy(bt, text, sizeof(bt) - 1);
  disp_set(disp_bt, bt);
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

