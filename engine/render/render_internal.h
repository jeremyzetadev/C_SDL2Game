#ifndef RENDER_INTERNAL_H
#define RENDER_INTERNAL_H

#include <SDL2/SDL.h>

#include "../types.h"
#include "render.h"

typedef struct render_state_internal {
    u32 vao_quad;
    u32 vbo_quad;
    u32 ebo_quad;
} Render_State_Internal;

SDL_Window *render_init_window(u32 width, u32 height);

#endif
