#include "../app_scene.h"

void app_scene_menu_submenu_callback(void* ctx, uint32_t index) {
    Context* context = ctx;
    log_info("Menu item selected %lu", index);
    scene_manager_next_scene(context->scene_manager, index);
}

void app_scene_menu_on_enter(void* ctx) {
    Context* context = ctx;
    Submenu* submenu = context->submenu;

    submenu_set_header(submenu, "Hello World!");
    submenu_add_item(submenu, "Demo 1", AppSceneDemo1, app_scene_menu_submenu_callback, context);
    submenu_add_item(submenu, "Demo 2", AppSceneDemo2, app_scene_menu_submenu_callback, context);

    submenu_set_selected_item(
        context->submenu, scene_manager_get_scene_state(context->scene_manager, ViewSubmenu));

    view_dispatcher_switch_to_view(context->view_dispatcher, ViewSubmenu);
}

bool app_scene_menu_on_event(void* ctx, SceneManagerEvent event) {
    Context* context = ctx;
    UNUSED(context);

    log_info("Menu on event: %i / %lu", event.type, event.event);

    if(event.type == SceneManagerEventTypeBack) {
        //Exit
    }

    return false;
}

void app_scene_menu_on_exit(void* ctx) {
    log_info("Menu scene exit");
    Context* context = ctx;
    submenu_reset(context->submenu);
}
