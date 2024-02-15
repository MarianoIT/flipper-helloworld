#pragma once

#include <furi.h>
#include <furi_hal.h>
#include <furi/core/log.h>
#include <furi_hal_gpio.h>
#include <furi_hal_resources.h>

#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/submenu.h>
#include <gui/modules/widget.h>

#include "scenes/app_event_helper.h"

#define LOG_TAG "HWSPACE"
#define LOG_SHOW true

#define log_info(format, ...) \
    if(LOG_SHOW) FURI_LOG_I(LOG_TAG, format, ##__VA_ARGS__)

#define log_exception(format, ...) \
    if(LOG_SHOW) FURI_LOG_E(LOG_TAG, format, ##__VA_ARGS__)

#define log_warning(format, ...) \
    if(LOG_SHOW) FURI_LOG_W(LOG_TAG, format, ##__VA_ARGS__)

typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    SceneManager* scene_manager;
    Submenu* submenu;
    Widget* widget;
} Context;

typedef enum {
    ViewSubmenu,
    ViewWidget,
} ViewType;
