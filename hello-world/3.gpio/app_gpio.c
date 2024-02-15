#include <stdio.h>
#include <furi.h>
#include <furi_hal.h>

#define LOG_TAG "HWSPACE"
#define LOG_SHOW true

#define log_info(format, ...) \
    if(LOG_SHOW) FURI_LOG_I(LOG_TAG, format, ##__VA_ARGS__)

#define log_exception(format, ...) \
    if(LOG_SHOW) FURI_LOG_E(LOG_TAG, format, ##__VA_ARGS__)

#define log_warning(format, ...) \
    if(LOG_SHOW) FURI_LOG_W(LOG_TAG, format, ##__VA_ARGS__)

int32_t app_gpio(void* p) {
    UNUSED(p);
    log_info("Hardware Hacking Space");
    log_info("[+] Hello GPIO!");

    //PA7 (pin 2)   gpio_ext_pa7
    //PA6 (pin 3)   gpio_ext_pa6
    //PA4 (pin 4)   gpio_ext_pa4
    //PB3 (pin 5)   gpio_ext_pb3
    //PB2 (pin 6)   gpio_ext_pb2
    //PC3 (pin 7)   gpio_ext_pc3
    //PC1 (pin 15)  gpio_ext_pc1
    //PC0 (pin 16)  gpio_ext_pc0

    //El pin 1 de 5V está apagado por menú de configuración cuando se alimenta por bateria
    //Los pines pueden generar unos +/-8mA

    //gpio_ext_pc3 es el pin C3 del Flipper
    GpioPin led = gpio_ext_pc3;

    log_info("[+] Configurando pin de salida");

    //Se inicializa el pin como salida tipo push-pull
    //PushPull significa que si el valor es falso, el pin su salida será de 0v 
    //y si es verdadero su salida será de 3.3v
    furi_hal_gpio_init_simple(&led, GpioModeOutputPushPull);

    log_info("[+] Encendiendo el led");
    furi_hal_gpio_write(&led, true);

    furi_delay_ms(1000); //Esperar 1 segundo

    log_info("[+] Apagando el led");
    furi_hal_gpio_write(&led, false);

    furi_delay_ms(1000); //Esperar 1 segundo

    log_info("[+] Bye!");

    return 0;
}
