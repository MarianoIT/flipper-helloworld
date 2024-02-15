#include "../app_scene.h"

void app_scene_demo2_button_ok_click(GuiButtonType type, InputType inputType, void* ctx) {
    UNUSED(type);
    UNUSED(inputType);
    log_info("app_scene_demo2_button_ok_click");
    Context* context = ctx;
    scene_manager_previous_scene(context->scene_manager);
}

void app_scene_demo2_on_enter(void* ctx) {
    log_info("app_scene_demo2_on_enter");
    Context* context = ctx;
    Widget* widget = context->widget;
    widget_add_string_element(widget, 64, 0, AlignCenter, AlignTop, FontPrimary, "--- Demo 2 ---");
    widget_add_button_element(
        widget, GuiButtonTypeRight, "OK!", app_scene_demo2_button_ok_click, context);
    view_dispatcher_switch_to_view(context->view_dispatcher, ViewWidget);
}

bool app_scene_demo2_on_event(void* ctx, SceneManagerEvent event) {
    log_info("app_scene_demo2_on_event");
    UNUSED(ctx);
    UNUSED(event);
    return false;
}

void app_scene_demo2_on_exit(void* ctx) {
    log_info("app_scene_demo2_on_exit");
    Context* context = ctx;
    widget_reset(context->widget);
}