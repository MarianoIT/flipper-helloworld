#include <stdio.h>
#include <furi.h>
#include <notification/notification_messages.h>

#define LOG_TAG "HWSPACE"
#define LOG_SHOW true

#define log_info(format, ...) \
    if(LOG_SHOW) FURI_LOG_I(LOG_TAG, format, ##__VA_ARGS__)

#define log_exception(format, ...) \
    if(LOG_SHOW) FURI_LOG_E(LOG_TAG, format, ##__VA_ARGS__)

#define log_warning(format, ...) \
    if(LOG_SHOW) FURI_LOG_W(LOG_TAG, format, ##__VA_ARGS__)

int32_t app_notification_1(void* p) {
    UNUSED(p);
    log_info("Hardware Hacking Space");
    log_info("[+] Hello Sexy Flipper!");

    //Se abre un canal de comunicacion con el servicio de notificaciones
    
    //La ubicación dentro del firmware la encontras en:
    //applications/services/notification/notification_messages.c

    NotificationApp* notification = furi_record_open(RECORD_NOTIFICATION);

    log_info("[+] Encendiendo vibrador");

    //De esta manera se pueden enviar mensajes al servicio de notificaciones 
    //de a una por vez
    //sequence_set_vibro_on se encuentra definida en el firware.

    notification_message(notification, &sequence_set_vibro_on);

    log_info("[+] Encendiendo luz roja");
    notification_message(notification, &sequence_set_red_255);

    furi_delay_ms(1000); //primitiva del kernel que permite esperar 1 segundo (o 1000 milisegundos)

    log_info("[+] Encendiendo luz verde");
    notification_message(notification, &sequence_set_green_255);

    log_info("[+] Apagando vibrador");
    notification_message(notification, &sequence_reset_vibro);

    furi_delay_ms(1000);

    log_info("[+] Apagando luz verde");
    notification_message(notification, &sequence_reset_green);

    //Al finalizar, se debe cierra el canal de comunicacion con el servicio de notificaciones
    furi_record_close(RECORD_NOTIFICATION);

    log_info("[+] Bye!");
    return 0;
}
