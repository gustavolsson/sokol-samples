//------------------------------------------------------------------------------
//  touch-sapp.c
//------------------------------------------------------------------------------
#include "sokol_gfx.h"
#include "sokol_app.h"

#include <string.h>

sg_pass_action pass_action;

typedef struct {
    float r;
    float g;
    float b;
} color_t;

typedef struct {
    uintptr_t id;
    color_t col;
    float x;
    float y;
} touch_t;

touch_t touches[SAPP_MAX_TOUCHPOINTS];
int32_t touch_count;

void init(void) {
    sg_setup(&(sg_desc) {
        .mtl_device = sapp_metal_get_device(),
        .mtl_renderpass_descriptor_cb = sapp_metal_get_renderpass_descriptor,
        .mtl_drawable_cb = sapp_metal_get_drawable,
        .d3d11_device = sapp_d3d11_get_device(),
        .d3d11_device_context = sapp_d3d11_get_device_context(),
        .d3d11_render_target_view_cb = sapp_d3d11_get_render_target_view,
        .d3d11_depth_stencil_view_cb = sapp_d3d11_get_depth_stencil_view
    });
    pass_action = (sg_pass_action) {
        .colors[0] = { .action=SG_ACTION_CLEAR, .val={0.2f, 0.2f, 0.2f, 1.0f} }
    };

    // (re-)initialize globals (cannot be done on declaration on Android unfortunately)
    memset(&touches, 0, sizeof(touches));
    touch_count = 0;
}

void event(const sapp_event* e) {
    switch (e->type) {
        case SAPP_EVENTTYPE_TOUCHES_BEGAN:
            break;
        case SAPP_EVENTTYPE_TOUCHES_MOVED:
            break;
        case SAPP_EVENTTYPE_TOUCHES_ENDED:
            break;
        case SAPP_EVENTTYPE_TOUCHES_CANCELLED:
            break;
        default:
            break;
    }
}

void frame(void) {
    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
    sg_end_pass();
    sg_commit();
}

void cleanup(void) {
    sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[]) {
    return (sapp_desc) {
        .init_cb = init,
        .event_cb = event,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .width = 1280,
        .height = 720,
        .high_dpi = false,
        .window_title = "Touch (sokol app)",
    };
}