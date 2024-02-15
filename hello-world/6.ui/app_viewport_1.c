#include <stdio.h>
#include <furi.h>

#include <gui/gui.h>

#define LOG_TAG "HWSPACE"
#define LOG_SHOW true //CWE-779: Logging of Excessive Data

#define log_info(format, ...) \
    if(LOG_SHOW) FURI_LOG_I(LOG_TAG, format, ##__VA_ARGS__)

#define log_exception(format, ...) \
    if(LOG_SHOW) FURI_LOG_E(LOG_TAG, format, ##__VA_ARGS__)

#define log_warning(format, ...) \
    if(LOG_SHOW) FURI_LOG_W(LOG_TAG, format, ##__VA_ARGS__)

typedef struct {
    Gui* gui;
    ViewPort* view_port;
} Context;

//2. Dibujamos la pantalla
static void draw_callback(Canvas* canvas, void* ctx) {
    log_info("[+] Dibujando interfaz de usuario");

    UNUSED(canvas);
    UNUSED(ctx);
}

//1. Obtenemos recursos necesarios
static Context* context_alloc() {
    log_info("[+] Solicitando recursos al sistema");

    Context* context = malloc(sizeof(Context));

    //GUI es quien maneja toda la pantalla
    context->gui = furi_record_open(RECORD_GUI);

    //view_port es quien maneja la porción disponible de esa pantalla
    //según la configuración establecida
    context->view_port = view_port_alloc();

    //Se agrega el view_port al manejador de pantalla y se configura
    //la vista en modo Fullscreen
    gui_add_view_port(context->gui, context->view_port, GuiLayerFullscreen);

    //Se asigna la función de dibujado
    view_port_draw_callback_set(context->view_port, draw_callback, context);

    return context;
}

//3. Liberamos los recursos solicitado
static void context_free(Context* context) {
    log_info("[+] Limpiando los recursos solicitados");

    view_port_enabled_set(context->view_port, false);
    gui_remove_view_port(context->gui, context->view_port);
    view_port_free(context->view_port);
    furi_record_close(RECORD_GUI);
}

//Función de inicio
int32_t app_viewport_1(void* p) {
    UNUSED(p);

    log_info("Hardware Hacking Space");
    log_info("[+] Hello ViewPort!");

    Context* context = context_alloc();

    furi_delay_ms(5000);

    context_free(context);

    log_info("[+] Bye!");
    return 0;
}
