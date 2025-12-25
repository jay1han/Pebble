#include <pebble.h>

#include "display.h"
#include "watch.h"

static char home[8]  = "12:00";
static char away[8]  = "00:00";
static char date[12] = "Mon 31/12";

void time_update() {
  time_t temp = time(NULL);
  struct tm *now = localtime(&temp);
  
  strftime(home, sizeof(home), "%H:%M", now);
  disp_set(disp_home, home);

  strftime(date, sizeof(date), "%a %d %b", now);
  disp_set(disp_date, date);

  temp += 8 * 3600;
  strftime(away, sizeof(away), "%H:%M", localtime(&temp));
  disp_set(disp_away, away);
}

static char wbat[4] = "00";

void charge_update(BatteryChargeState charge_state) {

  if (charge_state.charge_percent >= 100) strcpy(wbat, "00");
  else {
    snprintf(wbat, sizeof(wbat), "%d", charge_state.charge_percent);
  }
  disp_set(disp_wbat, wbat);
}

static char conn[4] = "x";
static bool conn_app = false;
static bool conn_kit = false;

static void connection_disp() {
    if (conn_app) {
        if (conn_kit) strcpy(conn, "C");
        else strcpy(conn, "-");
    } else {
        if (conn_kit) strcpy(conn, "?");
        else strcpy(conn, "X");
    }
    disp_set(disp_conn, conn);
}

void connection_update(bool connected) {
    conn_app = connected;
    connection_disp();
}

void pebblekit_update(bool connected) {
    conn_kit = connected;
    connection_disp();
}
