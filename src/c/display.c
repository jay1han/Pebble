#include <pebble.h>

#include "display.h"

static struct {
    TextLayer *layer;
    GRect rect;
    uint8_t color;
    GTextAlignment align;
    const char *font;
} disp[disp_end] = {
    {NULL, {{0, -10},   {144, 31}}, 0xFF, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_quiet
    {NULL, {{0, -10},   {144, 31}}, 0xFF, GTextAlignmentCenter, FONT_KEY_GOTHIC_28_BOLD       },      //  disp_date
    {NULL, {{0, -10},   {144, 31}}, 0xFF, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_dnd !TODO
    {NULL, {{0, 15},    {144, 31}}, 0xC0, GTextAlignmentLeft ,  FONT_KEY_GOTHIC_18_BOLD       },      //  disp_conn
    {NULL, {{0, 16},    {144, 51}}, 0xC0, GTextAlignmentCenter, FONT_KEY_ROBOTO_BOLD_SUBSET_49},      //  disp_home
    {NULL, {{0, 68},    {144, 31}}, 0xFF, GTextAlignmentCenter, FONT_KEY_GOTHIC_28_BOLD       },      //  disp_noti
    {NULL, {{0, 96},    {144, 29}}, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_24_BOLD       },      //  disp_btc
    {NULL, {{24, 96},   {144, 29}}, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_24_BOLD       },      //  disp_btid
    {NULL, {{0, 117},   {144, 29}}, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_24_BOLD       },      //  disp_net 
    {NULL, {{24, 117},  {144, 29}}, 0xC0, GTextAlignmentLeft  , FONT_KEY_GOTHIC_24_BOLD       },      //  disp_wifi
    {NULL, {{0, 140},   {140, 31}}, 0xFF, GTextAlignmentCenter, FONT_KEY_GOTHIC_28_BOLD       },      //  disp_away
    {NULL, {{0, 140},   {144, 31}}, 0xFF, GTextAlignmentLeft  , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_wbat
    {NULL, {{0, 140},   {144, 31}}, 0xFF, GTextAlignmentRight , FONT_KEY_GOTHIC_28_BOLD       },      //  disp_pbat
};

static struct {
    BitmapLayer *layer;
    GRect rect;
    uint8_t color;
} bg[] = {
    {NULL, {{0, 0},   {144, 21}}, 0xC0},
    {NULL, {{0, 74},  {144, 26}}, 0xC0},
    {NULL, {{0, 147}, {144, 22}}, 0xC0},
};

#define BG (sizeof(bg) / sizeof(bg[0]))

static bool quiet_time = false;

static void check_quiet_time() {
    bool is_active = quiet_time_is_active();
    APP_LOG(APP_LOG_LEVEL_INFO, "Quiet %d -> %d", (int)quiet_time, (int)is_active);
    if (quiet_time != is_active) {
        quiet_time = is_active;
        text_layer_set_text(disp[disp_quiet].layer, quiet_time ? "Q" : "");
    }
}

void disp_create(Layer *window_layer) {
    for (size_t i = 0; i < BG; i++) {
        BitmapLayer *layer = bitmap_layer_create(bg[i].rect);
        bitmap_layer_set_background_color(layer, (GColor8){.argb=bg[i].color});
        bitmap_layer_set_compositing_mode(layer, GCompOpAnd);
        layer_add_child(window_layer, bitmap_layer_get_layer(layer));
        bg[i].layer = layer;
    }
    
    for (disp_t i = 0; i < disp_end; i++) {
        TextLayer *layer = text_layer_create(disp[i].rect);
        text_layer_set_background_color(layer, GColorClear);
        text_layer_set_text_color(layer, (GColor8){.argb=disp[i].color});
        text_layer_set_text(layer, "");
        text_layer_set_font(layer, fonts_get_system_font(disp[i].font));
        text_layer_set_text_alignment(layer, disp[i].align);
	text_layer_set_overflow_mode(layer, GTextOverflowModeTrailingEllipsis);
        layer_add_child(window_layer, text_layer_get_layer(layer));
        disp[i].layer = layer;
    }

    check_quiet_time();
}

void disp_destroy(void) {
    for (disp_t i = 0; i < disp_end; i++) {
        text_layer_destroy(disp[i].layer);
    }

    for (size_t i = 0; i < BG; i++) {
        bitmap_layer_destroy(bg[i].layer);
    }
}

void disp_set(disp_t index, char *text) {
    text_layer_set_text(disp[index].layer, text);
    check_quiet_time();
}

void disp_focus(bool in_focus) {
    if (in_focus) check_quiet_time();
}
