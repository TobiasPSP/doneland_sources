#pragma once
// Configuration for pinned LVGL 9.2.2. Font inclusion and memory hooks must match
// firmware widgets and native simulation. This is project configuration, not a
// vendor library modification; update both embedded and native builds together.
#define LV_LABEL_TEXT_SELECTION 1
#define LV_CONF_H
#define LV_COLOR_DEPTH 16
#define LV_THEME_DEFAULT_DARK 1
#define LV_USE_OS LV_OS_NONE
#define LV_MEM_SIZE (512U * 1024U)
#ifndef TABLET_PREVIEW
#define LV_MEM_POOL_INCLUDE "lv_pool.h"
#define LV_MEM_POOL_ALLOC tablet_lvgl_pool_alloc
#endif
#ifdef TABLET_PREVIEW
#define LV_ASSERT_HANDLER_INCLUDE <stdlib.h>
#define LV_ASSERT_HANDLER exit(99);
#endif
#define LV_FONT_MONTSERRAT_18 1
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_10 1
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_UNSCII_8 1
#define LV_FONT_DEFAULT &lv_font_montserrat_18
#ifdef TABLET_PREVIEW
#define LV_USE_LOG 1
#define LV_LOG_PRINTF 1
#else
#define LV_USE_LOG 0
#endif
#define LV_USE_DEMO_WIDGETS 0
