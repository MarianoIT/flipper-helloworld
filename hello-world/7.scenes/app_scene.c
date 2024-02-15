#include "app_scene.h"

static bool app_navigation_event_callback(void* ctx) {
    log_info("Navigation event received");
    furi_assert(ctx);
    Context* context = ctx;
    return scene_manager_handle_back_event(context->scene_manager);
}

static Context* context_alloc() {
    log_info("Context alloc");

    Context* context = malloc(sizeof(Context));

    context->gui = furi_record_open(RECORD_GUI);

    context->scene_manager = scene_manager_alloc(&app_scene_handlers, context);

    context->view_dispatcher = view_dispatcher_alloc();

    view_dispatcher_enable_queue(context->view_dispatcher);

    view_dispatcher_set_event_callback_context(context->view_dispatcher, context);

    view_dispatcher_set_navigation_event_callback(
        context->view_dispatcher, app_navigation_event_callback);

    context->submenu = submenu_alloc();
    view_dispatcher_add_view(
        context->view_dispatcher, ViewSubmenu, submenu_get_view(context->submenu));

    context->widget = widget_alloc();
    view_dispatcher_add_view(
        context->view_dispatcher, ViewWidget, widget_get_view(context->widget));

    return context;
}

static void context_free(Context* context) {
    log_info("Context free");
    furi_assert(context);

    view_dispatcher_remove_view(context->view_dispatcher, ViewWidget);
    widget_free(context->widget);

    view_dispatcher_remove_view(context->view_dispatcher, ViewSubmenu);
    submenu_free(context->submenu);

    view_dispatcher_free(context->view_dispatcher);
    scene_manager_free(context->scene_manager);

    furi_record_close(RECORD_GUI);
    context->gui = NULL;

    free(context);
}

static void run(Context* context) {
    log_info("run");
    furi_assert(context);

    view_dispatcher_attach_to_gui(
        context->view_dispatcher, context->gui, ViewDispatcherTypeFullscreen);

    scene_manager_next_scene(context->scene_manager, AppSceneMenu);

    view_dispatcher_run(context->view_dispatcher);
}

int32_t app_scenes(void* p) {
    UNUSED(p);

    Context* context = context_alloc();

    run(context);

    context_free(context);

    return 0;
}