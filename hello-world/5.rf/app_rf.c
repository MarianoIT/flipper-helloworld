#include <stdio.h>
#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>

#include <applications/drivers/subghz/cc1101_ext/cc1101_ext_interconnect.h>

#include <lib/subghz/subghz_keystore.h>
#include <lib/subghz/receiver.h>
#include <lib/subghz/transmitter.h>
#include <lib/subghz/devices/cc1101_int/cc1101_int_interconnect.h>
#include <lib/subghz/devices/devices.h>
#include <lib/subghz/devices/cc1101_configs.h>

#define LOG_TAG "HWSPACE"
#define LOG_SHOW true

#define log_info(format, ...) \
    if(LOG_SHOW) FURI_LOG_I(LOG_TAG, format, ##__VA_ARGS__)

#define log_exception(format, ...) \
    if(LOG_SHOW) FURI_LOG_E(LOG_TAG, format, ##__VA_ARGS__)

#define log_warning(format, ...) \
    if(LOG_SHOW) FURI_LOG_W(LOG_TAG, format, ##__VA_ARGS__)

int32_t app_rf(void* p) {
    UNUSED(p);
    log_info("Hardware Hacking Space");
    log_info("[+] Hello RF!");

    //La frecuencia es 433.92MHz
    uint32_t frequency = 433920000;

    log_info("Frecuencia %lu Hz\r\n", frequency);

    furi_hal_subghz_reset();

    //Configura los parámetros de la radio
    //Observe que subghz_device_cc1101_preset_ook_650khz_async_regs es un preset definido en el Firmware
    //y no están todos los presets disponibles en el CC1101
    furi_hal_subghz_load_custom_preset(subghz_device_cc1101_preset_ook_650khz_async_regs);
    frequency = furi_hal_subghz_set_frequency_and_path(frequency);

    subghz_devices_init(); //Inicia el dispositivo
    furi_hal_subghz_rx(); //Configura en modo recepción

    for(int i = 0; i < 100; i++) {
        double rssi = furi_hal_subghz_get_rssi(); //obtiene el RSSI (fuerza señal)
        log_info("[+] RSSI: %03.1fdbm\r", rssi);
        furi_delay_ms(100);
    }

    furi_hal_subghz_set_path(FuriHalSubGhzPathIsolate);
    furi_hal_subghz_sleep(); //Pone el dispositivo en modo de bajo consumo
    subghz_devices_deinit(); //Deja de usarlo

    log_info("[+] Bye!");
    return 0;
}
