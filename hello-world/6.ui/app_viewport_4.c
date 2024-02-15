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

#define UPDATE_PERIOD_MS 1000UL
#define THREAD_EXIT 1

//Datos que se intercambian en la aplicación
typedef struct {
    int counter;
} Data;

typedef struct {
    Gui* gui;
    ViewPort* view_port;
    FuriMessageQueue* event_queue;
    FuriThread* job; //Se agrega un hilo para ejecutar acciones en segundo plano no bloqueantes
    Data data; //Se agrega una estructura de datos para intercambiar información entre hilos
} Context;


//Hilo donde se realizan las tareas de la aplicación
static int32_t job_callback(void* ctx) {
    Context* context = ctx;
    context->data.counter = 0;
    
    uint32_t flags = 0;
    log_info("[+] Iniciando hilo secundario");

    do {
        context->data.counter += 1;

        flags = furi_thread_flags_wait(THREAD_EXIT, FuriFlagWaitAny, UPDATE_PERIOD_MS);
    } while (flags == (unsigned)FuriFlagErrorTimeout);

    log_info("[+] Terminando hilo secundario");
    return 0;
}

static void input_callback(InputEvent* event, void* ctx) {
    Context* context = ctx;
    furi_message_queue_put(context->event_queue, event, FuriWaitForever);
}

static void draw_callback(Canvas* canvas, void* ctx) {
    log_info("[+] Dibujando interfaz de usuario");

    Context* context = ctx;
    
    const uint8_t ancho_display = canvas_width(canvas);
    const uint8_t alto_display = canvas_height(canvas);
    
    char text_buffer[30];

    canvas_set_font(canvas, FontPrimary);

    const uint8_t altura_linea = canvas_current_font_height(canvas);    

    canvas_draw_str(canvas, 0, altura_linea * 1, "Hello Flipper!");

    snprintf(text_buffer, sizeof(text_buffer), "Display: %ix%i", ancho_display, alto_display);
    canvas_draw_str(canvas, 0, altura_linea * 2, text_buffer);

    snprintf(text_buffer, sizeof(text_buffer), "Linea: %i", altura_linea);
    canvas_draw_str(canvas, 0, altura_linea * 3, text_buffer);

    snprintf(text_buffer, sizeof(text_buffer), "Contador: %i", context->data.counter);
    canvas_draw_str(canvas, 0, altura_linea * 4, text_buffer);

}

static Context* context_alloc() {
    log_info("[+] Solicitando recursos al sistema");

    Context* context = malloc(sizeof(Context));

    //event_queue es quien maneja los eventos del sistema
    context->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    //gui es quien maneja toda la pantalla
    context->gui = furi_record_open(RECORD_GUI); 
    
    //view_port es quien maneja la porción disponible de esa pantalla según la configuración establecida
    context->view_port = view_port_alloc();      

    //Se agrega el view_port al manejador de pantalla y se configura la vista en modo Fullscreen
    gui_add_view_port(context->gui, context->view_port, GuiLayerFullscreen); 

    //Se asigna la función de dibujado
    view_port_draw_callback_set(context->view_port, draw_callback, context); 

    //Se asigna la función de callback para recibir eventos
    view_port_input_callback_set(context->view_port, input_callback, context);


    context->job = furi_thread_alloc();
    furi_thread_set_stack_size(context->job, 1024U);
    furi_thread_set_context(context->job, context);
    furi_thread_set_callback(context->job, job_callback);

    return context;
}

static void run(Context* context) {
    bool is_running = true;
    InputEvent event;

    furi_thread_start(context->job);

    while(is_running) {
        log_info("[+] Solicitando eventos al sistema");
        
        const FuriStatus status =
            furi_message_queue_get(context->event_queue, &event, FuriWaitForever);

        if(status == FuriStatusOk 
            && event.type == InputTypeLong
            && event.key == InputKeyBack) 
        {
            is_running = false;
        }
    }

    // Envia la señal para avisar que el hilo principal se termina 
    furi_thread_flags_set(furi_thread_get_id(context->job), THREAD_EXIT);
    
    // Espera a que el hilo secundario termine 
    furi_thread_join(context->job);
}

static void context_free(Context* context) {
    log_info("[+] Limpiando los recursos solicitados");

    view_port_enabled_set(context->view_port, false);
    gui_remove_view_port(context->gui, context->view_port);
    furi_record_close(RECORD_GUI);

    furi_thread_free(context->job);
    furi_message_queue_free(context->event_queue);
    view_port_free(context->view_port);
}

int32_t app_viewport_4(void* p) {
    UNUSED(p);

    log_info("Hardware Hacking Space");
    log_info("[+] Hello ViewPort!");

    Context* context = context_alloc();

    run(context);

    context_free(context);

    log_info("[+] Bye!");
    return 0;
}
