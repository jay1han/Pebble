#pragma once

typedef enum {
  disp_none,
  disp_date,
  disp_pchg,
  disp_time,
  disp_wbat,
  disp_noti,
  disp_pbat,
  disp_bt  ,
  disp_wifi,
  disp_net ,
  disp_away,
  disp_dnd ,
  disp_end
} disp_t;

void disp_create(disp_t index, Layer *window_layer);
void disp_destroy(disp_t index);
void disp_set(disp_t index, char *text);
