#include <pebble.h>

#include "display.h"

static struct {
    TextLayer *layer;
    GRect rect;
    uint8_t back, front;
    GTextAlignment align;
    const char *font;
    char *text;
} disp[disp_end] = {
    {NULL, {{0, 21},    {144, 41}} , 0x00, 0xC0, GTextAlignmentCenter, FONT_KEY_GOTHIC_14            , NULL},      //  disp_none
    {NULL, {{0, -10},   {144, 31}} , 0x00, 0xFF, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       , NULL},      //  disp_date
    {NULL, {{0, -10},   {144, 31}} , 0x00, 0xFF, GTextAlignmentRight , FONT_KEY_GOTHIC_28_BOLD       , NULL},      //  disp_pchg
    {NULL, {{0, 14},    {144, 51}} , 0x00, 0xC0, GTextAlignmentCenter, FONT_KEY_ROBOTO_BOLD_SUBSET_49, NULL},      //  disp_home
    {NULL, {{0, 64},    {144, 31}} , 0x00, 0xFF, GTextAlignmentCenter, FONT_KEY_GOTHIC_28_BOLD       , NULL},      //  disp_noti
    {NULL, {{0, 64},    {144, 31}} , 0x00, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       , NULL},      //  disp_wbat
    {NULL, {{0, 64},    {144, 31}} , 0x00, 0xC0, GTextAlignmentRight , FONT_KEY_GOTHIC_28_BOLD       , NULL},      //  disp_pbat
    {NULL, {{0, 94},    {144, 29}} , 0x00, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_24_BOLD       , NULL},      //  disp_bt  
    {NULL, {{0, 115},   {144, 29}} , 0x00, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_24_BOLD       , NULL},      //  disp_wifi
    {NULL, {{0, 115},   {144, 29}} , 0x00, 0xC0, GTextAlignmentRight , FONT_KEY_GOTHIC_24_BOLD       , NULL},      //  disp_net 
    {NULL, {{0, 139},   {144, 31}} , 0x00, 0xFF, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       , NULL},      //  disp_away
    {NULL, {{0, 139},   {144, 31}} , 0x00, 0xFF, GTextAlignmentRight , FONT_KEY_GOTHIC_28_BOLD       , NULL},      //  disp_dnd 
};

static struct {
    BitmapLayer *layer;
    GRect rect;
    uint8_t color;
} bg[] = {
    {NULL, {{0, 0}, {144, 21}}, 0xC0},
    {NULL, {{28, 70}, {88, 26}}, 0xC0},
    {NULL, {{0, 146}, {144, 22}}, 0xC0},
};

#define BG (sizeof(bg) / sizeof(bg[0]))

void disp_create(Layer *window_layer) {
    for (size_t i = 0; i < BG; i++) {
        BitmapLayer *layer = bitmap_layer_create(bg[i].rect);
        bitmap_layer_set_background_color(layer, (GColor8){.argb=bg[i].color});
        bitmap_layer_set_compositing_mode(layer, GCompOpAnd);
        layer_add_child(window_layer, bitmap_layer_get_layer(layer));
        bg[i].layer = layer;
    }
    
    for (disp_t index = disp_none + 1; index < disp_end; index++) {
        TextLayer *layer = text_layer_create(disp[index].rect);
        text_layer_set_background_color(layer, (GColor8){.argb=disp[index].back});
        text_layer_set_text_color(layer, (GColor8){.argb=disp[index].front});
        text_layer_set_text(layer, "");
        text_layer_set_font(layer, fonts_get_system_font(disp[index].font));
        text_layer_set_text_alignment(layer, disp[index].align);
        layer_add_child(window_layer, text_layer_get_layer(layer));
        disp[index].layer = layer;
    }
}

void disp_destroy(void) {
    for (disp_t index = disp_none + 1; index < disp_end; index++) {
        text_layer_destroy(disp[index].layer);
    }

    for (size_t i = 0; i < BG; i++) {
        bitmap_layer_destroy(bg[i].layer);
    }
}

void disp_set(disp_t index, char *text) {
    text_layer_set_text(disp[index].layer, text);
    disp[index].text = text;
}

void disp_refresh(disp_t index) {
    text_layer_set_text(disp[index].layer, disp[index].text);

}
