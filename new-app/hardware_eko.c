#include <furi.h>

/* generated by fbt from .png files in images folder */
#include <hardware_eko_icons.h>

int32_t hardware_eko_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm hardware_eko!");

    return 0;
}
