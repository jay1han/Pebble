#pragma once

typedef enum {
  disp_none,
  disp_date,
  disp_pchg,
  disp_home,
  disp_noti,
  disp_wbat,
  disp_pbat,
  disp_bt  ,
  disp_wifi,
  disp_net ,
  disp_away,
  disp_dnd ,
  disp_end
} disp_t;


void disp_create(Layer *window_layer);
void disp_destroy();
void disp_set(disp_t index, char *text);
void disp_refresh(disp_t index);
