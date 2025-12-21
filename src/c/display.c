#include <pebble.h>

#include "display.h"

static struct {
  TextLayer *layer;
  GRect rect;
  uint8_t back, front;
  GTextAlignment align;
  const char *font;
} fmt[disp_end] = {
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentCenter, FONT_KEY_ROBOTO_BOLD_SUBSET_49},      //  disp_none
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_date
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentRight , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_pchg
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentCenter, FONT_KEY_ROBOTO_BOLD_SUBSET_49},      //  disp_time
  {NULL, {{0, 62}, {50, 31}} , 0xFF, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_wbat
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentCenter, FONT_KEY_GOTHIC_28_BOLD       },      //  disp_noti
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentRight , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_pbat
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_24_BOLD       },      //  disp_bt  
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_18_BOLD       },      //  disp_wifi
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentRight , FONT_KEY_GOTHIC_18_BOLD       },      //  disp_net 
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_24_BOLD       },      //  disp_away
  {NULL, {{0, 0}, {144, 168}}, 0xFF, 0xC0, GTextAlignmentRight , FONT_KEY_GOTHIC_24_BOLD       }       //  disp_dnd 
};

void disp_create(disp_t index, Layer *window_layer) {
  TextLayer *layer = text_layer_create(fmt[index].rect);
  text_layer_set_background_color(layer, (GColor8){.argb=fmt[index].back});
  text_layer_set_text_color(layer, (GColor8){.argb=fmt[index].front});
  text_layer_set_text(layer, "");
  text_layer_set_font(layer, fonts_get_system_font(fmt[index].font));
  text_layer_set_text_alignment(layer, fmt[index].align);
  layer_add_child(window_layer, text_layer_get_layer(layer));
  fmt[index].layer = layer;
}

void disp_destroy(disp_t index) {
  text_layer_destroy(fmt[index].layer);
}

void disp_set(disp_t index, char *text) {
  text_layer_set_text(fmt[index].layer, text);
}
