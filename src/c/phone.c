#include <pebble.h>

#include "display.h"
#include "phone.h"

static char pbat[4]  = "80";
static char pchg[4]  = "C";
static char net[4]   = "5G";
static char wifi[20] = "Climbing";
static char bt[20]   = "Quiet:90";
static char dnd[4]   = "Q";
static char noti[20] = "SAMPLE";

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

void phone_net();
void phone_wifi();
void phone_bt();
void phone_dnd(bool quiet);
void phone_noti();
