#include <stdio.h>
#include <furi.h>
#include <furi_hal.h>
#include <infrared_worker.h>
#include <infrared_transmit.h>
#include <infrared/encoder_decoder/infrared.h>

#define LOG_TAG "HWSPACE"
#define LOG_SHOW true

#define log_info(format, ...) \
    if(LOG_SHOW) FURI_LOG_I(LOG_TAG, format, ##__VA_ARGS__)

#define log_exception(format, ...) \
    if(LOG_SHOW) FURI_LOG_E(LOG_TAG, format, ##__VA_ARGS__)

#define log_warning(format, ...) \
    if(LOG_SHOW) FURI_LOG_W(LOG_TAG, format, ##__VA_ARGS__)

int32_t app_ir(void* p) {
    UNUSED(p);
    log_info("Hardware Hacking Space");
    log_info("[+] Hello IR!");
    log_info("[+] Enviando ON");

    //En el archivo laser.ir se encuentra la configuración que se obtuvo del Flipper
    //cuando se capturó la señal desde el control remoto del equipo.
    //Puede observar que address es 0x00 y el comando es 0x45.

    InfraredMessage message_on;
    message_on.protocol = InfraredProtocolNEC;
    message_on.address = 0x00;
    message_on.command = 0x45;
    
    //Se envia el mensaje para encender el laser
    infrared_send(&message_on, 1); 

    furi_delay_ms(3000);

    log_info("[+] Enviando OFF");

    //Mensaje de apagado
    InfraredMessage message_off;

    message_off.protocol = InfraredProtocolNEC;
    message_off.address = 0x00;
    message_off.command = 0x47;

    infrared_send(&message_off, 1);
    
    log_info("[+] Bye!");

    return 0;
}
