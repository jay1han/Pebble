#include <pebble.h>

#include "dict.h"
#include "watch.h"
#include "phone.h"

enum {
    KEY_MSG_TYPE_I8 = 1,
    KEY_TZ_MINS_I16,
    KEY_PHONE_DND_I8,
    KEY_PHONE_BATT_I8,
    KEY_PHONE_CHG_I8,
    KEY_NET_I8,
    KEY_WIFI_S20,
    KEY_BTID_S20,
    KEY_BTC_I8,
    KEY_NOTI_S12,
    KEY_ACTION_I8,
    KEY_MODEL_I8,
    KEY_VERSION_U32,
    KEY_WBATT_I8,
};

typedef enum {
    MSG_INFO = 1,
    MSG_TZ,
    MSG_PHONE_DND,
    MSG_PHONE_CHG,
    MSG_NET,
    MSG_WIFI,
    MSG_BT,
    MSG_NOTI,
    MSG_ACTION
} msg_type_t;

typedef enum {
    ACTION_FIND = 1,
    ACTION_DND,
    ACTION_TBD
} action_t;

static struct {
    msg_type_t message_type;
    int16_t    timezone_minutes;
    bool       phone_dnd;
    int8_t     phone_battery;
    bool       phone_charging;
    int8_t     network_type;
    char       *wifi_ssid;
    char       *bt_device;
    int8_t     bt_battery;
    char       *notifications;
    action_t   action;
} message;

void send_info() {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);

    dict_write_int8(iter, KEY_MSG_TYPE_I8, MSG_INFO);
    dict_write_int8(iter, KEY_MODEL_I8, watch_info_get_model());
    WatchInfoVersion version = watch_info_get_firmware_version();
    uint32_t version_u32 = ((uint32_t)version.major << 16) | ((uint32_t)version.minor << 8) | (uint32_t)version.patch;
    dict_write_uint32(iter, KEY_VERSION_U32, version_u32);
    dict_write_int8(iter, KEY_WBATT_I8, watch_battery);
    dict_write_int16(iter, KEY_TZ_MINS_I16, tz_get());
    
    app_message_outbox_send();
}

void dict_parse(DictionaryIterator *iter, void *context) {
    Tuple *tuple = dict_read_first(iter);
    while (tuple) {
        switch(tuple->key) {

        case KEY_MSG_TYPE_I8:
            if (tuple->type == TUPLE_INT && tuple->length == 1)
                message.message_type = (msg_type_t)tuple->value->int8;
            break;
            
        case KEY_TZ_MINS_I16:
            if (tuple->type == TUPLE_INT && tuple->length == 2)
                message.timezone_minutes = tuple->value->int16;
            break;
            
        case KEY_PHONE_DND_I8:
            if (tuple->type == TUPLE_INT && tuple->length == 1)
                message.phone_dnd = (bool)tuple->value->int8;
            break;
            
        case KEY_PHONE_BATT_I8:
            if (tuple->type == TUPLE_INT && tuple->length == 1)
                message.phone_battery = tuple->value->int8;
            break;
            
        case KEY_PHONE_CHG_I8:
            if (tuple->type == TUPLE_INT && tuple->length == 1)
                message.phone_charging = (bool)tuple->value->int8;
            break;
            
        case KEY_NET_I8:
            if (tuple->type == TUPLE_INT && tuple->length == 1)
                message.network_type = tuple->value->int8;
            break;
            
        case KEY_WIFI_S20:
            if (tuple->type == TUPLE_CSTRING && tuple->length <= 20)
                message.wifi_ssid = tuple->value->cstring;
            break;
            
        case KEY_BTID_S20:
            if (tuple->type == TUPLE_CSTRING && tuple->length <= 20)
                message.bt_device = tuple->value->cstring;
            break;
            
        case KEY_BTC_I8:
            if (tuple->type == TUPLE_INT && tuple->length == 1)
                message.bt_battery = tuple->value->int8;
            break;
            
        case KEY_NOTI_S12:
            if (tuple->type == TUPLE_CSTRING && tuple->length <= 12)
                message.notifications = tuple->value->cstring;
            break;
            
        }
        
        tuple = dict_read_next(iter);
    }

    switch(message.message_type) {

    case MSG_INFO: send_info(); break;
    case MSG_TZ: tz_change(message.timezone_minutes); break;
    case MSG_PHONE_DND: phone_dnd(message.phone_dnd); break;
    case MSG_PHONE_CHG: phone_charge(message.phone_battery, message.phone_charging); break;
    case MSG_NET: phone_net(message.network_type); break;
    case MSG_WIFI: phone_wifi(message.wifi_ssid); break;
    case MSG_BT: phone_bt(message.bt_device, message.bt_battery); break;
    case MSG_NOTI: phone_noti(message.notifications); break;
    case MSG_ACTION: break;
        
    }
}
