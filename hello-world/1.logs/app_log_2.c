#include <stdio.h>
#include <furi.h>

#define LOG_TAG "HWSPACE"
#define LOG_SHOW true //CWE-779: Logging of Excessive Data

// Estas definiciones permiten ahorrar tiempo con el manejo de logs

#define log_info(format, ...) \
    if(LOG_SHOW) FURI_LOG_I(LOG_TAG, format, ##__VA_ARGS__)

#define log_exception(format, ...) \
    if(LOG_SHOW) FURI_LOG_E(LOG_TAG, format, ##__VA_ARGS__)

#define log_warning(format, ...) \
    if(LOG_SHOW) FURI_LOG_W(LOG_TAG, format, ##__VA_ARGS__)


int32_t app_log_2(void* p) {
    UNUSED(p);

    log_info("Hardware Hacking Space");
    log_info("Hello logs!");
    log_info("[+] Esta es una salida con formato: %s! %i", "tipo printf", 1);
    log_exception("[-] Así se muestra un error");
    log_warning("[-] Así se muestra un warning");
    log_info("[+] Bye!");

    return 0;
}
