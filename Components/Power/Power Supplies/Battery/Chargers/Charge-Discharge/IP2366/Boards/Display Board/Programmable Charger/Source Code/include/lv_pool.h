#pragma once
// Long-lived LVGL pool allocation boundary. Embedded allocation prefers external
// PSRAM; native fixtures supply their own allocator. The pool must outlive all
// widgets and must not be replaced while LVGL retains pointers into it.
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
void *tablet_lvgl_pool_alloc(size_t size);
#ifdef __cplusplus
}
#endif
