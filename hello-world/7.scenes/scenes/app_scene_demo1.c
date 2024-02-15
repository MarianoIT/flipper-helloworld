#include "../app_scene.h"

void app_scene_demo1_on_enter(void* ctx) {
    log_info("app_scene_demo1_on_enter");

    Context* context = ctx;
    Widget* widget = context->widget;
    widget_add_string_element(widget, 64, 0, AlignCenter, AlignTop, FontPrimary, "--- Demo 1 ---");
    widget_add_text_scroll_element(
        widget,
        0,
        16,
        128,
        48,
        "Lorem ipsum dolor sit amet,\nconsectetur adipiscing elit,\nsed do eiusmod tempor incididunt ut \nlabore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation\nullamco laboris nisi ut aliquip ex ea commodo\nconsequat.");

    view_dispatcher_switch_to_view(context->view_dispatcher, ViewWidget);
}

bool app_scene_demo1_on_event(void* ctx, SceneManagerEvent event) {
    log_info("app_scene_demo1_on_event");
    UNUSED(ctx);
    UNUSED(event);
    return false;
}

void app_scene_demo1_on_exit(void* ctx) {
    log_info("app_scene_demo1_on_exit");
    Context* context = ctx;
    widget_reset(context->widget);
}