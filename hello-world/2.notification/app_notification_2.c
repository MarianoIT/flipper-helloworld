#include <stdio.h>
#include <furi.h>
#include <notification/notification_messages.h>

#define LOG_TAG "HWSPACE"
#define LOG_SHOW true //CWE-779: Logging of Excessive Data

#define log_info(format, ...) \
    if(LOG_SHOW) FURI_LOG_I(LOG_TAG, format, ##__VA_ARGS__)

#define log_exception(format, ...) \
    if(LOG_SHOW) FURI_LOG_E(LOG_TAG, format, ##__VA_ARGS__)

#define log_warning(format, ...) \
    if(LOG_SHOW) FURI_LOG_W(LOG_TAG, format, ##__VA_ARGS__)


//Se puede definir una secuencia de notificaciones para llamarlas de manera mas sencilla
static const NotificationSequence notification_on = {
    &message_blink_start_10,
    &message_blink_set_color_red,
    &message_vibro_on,
    &message_display_backlight_on,
    &message_do_not_reset,
    NULL,
};

static const NotificationSequence notification_off = {
    &message_blink_stop,
    &message_vibro_off,
    &message_display_backlight_off,
    NULL,
};

int32_t app_notification_2(void* p) {
    UNUSED(p);
    log_info("Hardware Hacking Space");
    log_info("[+] Hello Sexy Flipper!");

    NotificationApp* notification = furi_record_open(RECORD_NOTIFICATION);

    log_info("[+] Encendiendo notificaciones por dos segundos");
    //A diferencia de app_notification_1, se envia una secuencia de notificaciones definida
    notification_message(notification, &notification_on);

    furi_delay_ms(2000);

    log_info("[+] Apagando notificaciones");
    notification_message(notification, &notification_off);

    furi_delay_ms(1000);

    log_info("[+] Encendiendo notificaciones por un segundo");
    notification_message(notification, &notification_on);

    furi_delay_ms(1000);

    log_info("[+] Apagando notificaciones");
    notification_message(notification, &notification_off);

    furi_record_close(RECORD_NOTIFICATION);

    log_info("[+] Bye!");
    return 0;
}
