#include <pebble.h>

#include "display.h"
#include "watch.h"
#include "dict.h"

static char home[8]  = "12:00";
static char away[8]  = "00:00";
static char date[12] = "Mon 31/12";
static int tz = 8 * 60;

static void tz_update(time_t *temp) {
    time_t now;
    if (temp == NULL) {
        now = time(NULL);
        temp = &now;
    }
    *temp += tz * 60;
    strftime(away, sizeof(away), "%H:%M", localtime(temp));
    disp_set(disp_away, away);
}

void time_update() {
    time_t temp = time(NULL);
    struct tm *now = localtime(&temp);
  
    strftime(home, sizeof(home), "%H:%M", now);
    disp_set(disp_home, home);

    strftime(date, sizeof(date), "%a %d %b", now);
    disp_set(disp_date, date);

    tz_update(&temp);

    send_batt();
}

void tz_change(int minutes) {
    tz = minutes;
    tz_update(NULL);
}

int tz_get() {
    return tz;
}

static char wbat[4] = "00";
BatteryChargeState watch_battery = {0, false, false};

void charge_update(BatteryChargeState charge_state) {
    watch_battery = charge_state;
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
