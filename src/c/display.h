#pragma once

typedef enum {
  disp_date = 0,
  disp_dnd ,
  disp_pchg,
  disp_conn,
  disp_home,
  disp_noti,
  disp_btc,
  disp_btid,
  disp_net ,
  disp_wifi,
  disp_away,
  disp_wbat,
  disp_pbat,
  disp_end
} disp_t;


void disp_create(Layer *window_layer);
void disp_destroy();
void disp_set(disp_t index, char *text);
