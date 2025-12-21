#include <pebble.h>

static TextLayer *date_layer;
static TextLayer *home_layer;
static TextLayer *away_layer;

void time_update() {
  time_t temp = time(NULL);
  static char home[8], away[12], date[12];
  struct tm *now = localtime(&temp);
  
  strftime(home, sizeof(home), "%H:%M", now);
  text_layer_set_text(home_layer, home);

  strftime(date, sizeof(date), "%a %d %b", now);
  text_layer_set_text(date_layer, date);

  temp += 8 * 3600;
  strftime(away, sizeof(away), " %a %H:%M", localtime(&temp));
  text_layer_set_text(away_layer, away);
}

void time_create(Layer *window_layer, GRect *bounds) {
  home_layer = text_layer_create(GRect(0, 11, bounds->size.w, 51));
  text_layer_set_background_color(home_layer, GColorWhite);
  text_layer_set_text_color(home_layer, GColorBlack);
  text_layer_set_text(home_layer, "00:00");
  text_layer_set_font(home_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  text_layer_set_text_alignment(home_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(home_layer));

  date_layer = text_layer_create(GRect(0, -10, bounds->size.w, 31));
  text_layer_set_background_color(date_layer, GColorWhite);
  text_layer_set_text_color(date_layer, GColorBlack);
  text_layer_set_text(date_layer, "Sun 31 Dec");
  text_layer_set_font(date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(date_layer));

  away_layer = text_layer_create(GRect(0, 140, bounds->size.w, 30));
  text_layer_set_background_color(away_layer, GColorWhite);
  text_layer_set_text_color(away_layer, GColorBlack);
  text_layer_set_text(away_layer, " Mon 00:00");
  text_layer_set_font(away_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(away_layer, GTextAlignmentLeft);
  layer_add_child(window_layer, text_layer_get_layer(away_layer));
}

void time_destroy() {
  text_layer_destroy(home_layer);
  text_layer_destroy(date_layer);
  text_layer_destroy(away_layer);
}
