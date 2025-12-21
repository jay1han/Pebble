#include <pebble.h>

#include "display.h"

static struct {
  TextLayer *layer;
  GRect rect;
  uint8_t back, front;
  GTextAlignment align;
  const char *font;
} fmt[disp_end] = {
  {NULL, {{0, 0},     {144, 168}}, 0x00, 0xC0, GTextAlignmentCenter, FONT_KEY_ROBOTO_BOLD_SUBSET_49},      //  disp_none
  {NULL, {{0, -10},   {128, 31}} , 0x00, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_date
  {NULL, {{128, -10}, {16, 31}}  , 0x00, 0xC0, GTextAlignmentRight , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_pchg
  {NULL, {{0, 11},    {144, 51}} , 0x00, 0xC0, GTextAlignmentCenter, FONT_KEY_ROBOTO_BOLD_SUBSET_49},      //  disp_home
  {NULL, {{0, 62},    {32, 31}}  , 0x00, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_wbat
  {NULL, {{32, 62},   {80, 31}}  , 0x00, 0xC0, GTextAlignmentCenter, FONT_KEY_GOTHIC_28_BOLD       },      //  disp_noti
  {NULL, {{112, 62},  {32, 31}}  , 0x00, 0xC0, GTextAlignmentRight , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_pbat
  {NULL, {{0, 93},    {144, 26}} , 0x00, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_24_BOLD       },      //  disp_bt  
  {NULL, {{0, 119},   {128, 20}} , 0x00, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_24_BOLD       },      //  disp_wifi
  {NULL, {{128, 119}, {16, 20}}  , 0x00, 0xC0, GTextAlignmentRight , FONT_KEY_GOTHIC_24_BOLD       },      //  disp_net 
  {NULL, {{0, 138},   {128, 30}} , 0x00, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_away
  {NULL, {{128, 138}, {16, 30}}  , 0x00, 0xC0, GTextAlignmentRight , FONT_KEY_GOTHIC_28_BOLD       }       //  disp_dnd 
};

void disp_create(Layer *window_layer) {
  TextLayer *layer;

  for (disp_t index = disp_none + 1; index < disp_end; index++) {
    layer = text_layer_create(fmt[index].rect);
    text_layer_set_background_color(layer, (GColor8){.argb=fmt[index].back});
    text_layer_set_text_color(layer, (GColor8){.argb=fmt[index].front});
    text_layer_set_text(layer, "");
    text_layer_set_font(layer, fonts_get_system_font(fmt[index].font));
    text_layer_set_text_alignment(layer, fmt[index].align);
    layer_add_child(window_layer, text_layer_get_layer(layer));
    fmt[index].layer = layer;
  }
}

void disp_destroy(void) {
  for (disp_t index = disp_none + 1; index < disp_end; index++) {
    text_layer_destroy(fmt[index].layer);
  }
}

void disp_set(disp_t index, char *text) {
  text_layer_set_text(fmt[index].layer, text);
}
