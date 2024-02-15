#include <stdio.h>
#include <furi.h>

int32_t app_log_1(void* p) {
    UNUSED(p);

    //Las bitácoras se ven en el cli de Flipper con el comando log
    
    FURI_LOG_I("HWSPACE", "Hardware Hacking Space");
    FURI_LOG_I("HWSPACE", "[+] Hello logs!");
    FURI_LOG_I("HWSPACE", "[+] Bye!");
    
    return 0;
}
