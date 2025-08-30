#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "engine/global/global.h"
#include "engine/input/input.h"
#include "engine/time/time.h"

#include "engine/physics/physics.h"

static bool should_quit = false;
static vec2 pos;

static void input_handle(void){
    if(global.input.left == KS_PRESSED || global.input.left == KS_HELD)
        pos[0] -= 500 *global.time.delta;
    if(global.input.right == KS_PRESSED || global.input.right == KS_HELD)
        pos[0] += 500 *global.time.delta;
    if(global.input.up == KS_PRESSED || global.input.up == KS_HELD)
        pos[1] += 500 *global.time.delta;
    if(global.input.down == KS_PRESSED || global.input.down == KS_HELD)
        pos[1] -= 500 *global.time.delta;
    if(global.input.escape == KS_PRESSED || global.input.escape == KS_HELD)
        should_quit = true;
}

int main(int argc, char *argv[]) {
    time_init(60);
    config_init();
    render_init();
    physics_init();

    // Spawn physics body
    u32 body_count = 100;
    for(u32 i=0; i<body_count; ++i){
        size_t body_index = physics_body_create(
                (vec2){ rand()%(i32)global.render.width, rand()%(i32)global.render.height},
                (vec2){ rand()%100, rand()%100});
        Body *body = physics_body_get(body_index);
        body->acceleration[0] = (rand() % 200) - 100;
        body->acceleration[1] = (rand() % 200) - 100;
    }
    // Spawn physics body

    pos[0] = global.render.width * 0.5;
    pos[1] = global.render.height * 0.5;

    while (!should_quit) {
        time_update();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                should_quit = true;
                break;
            default:
                break;
            }
        }
        input_update();
        input_handle();
        physics_update();

        render_begin();

        render_quad(
            // (vec2){global.render.width * 0.5, global.render.height * 0.5},
            pos,
            (vec2){50, 50},
            (vec4){0, 1, 0, 1});

        // Render physics body
        for(u32 i=0; i<body_count; ++i){
            Body *body = physics_body_get(i);
            render_quad(body->aabb.position, body->aabb.half_size,(vec4){1,0,0,1});

            if(body->aabb.position[0]>global.render.width || body->aabb.position[0]<0)
                body->velocity[0] *= -1;
            if(body->aabb.position[1]>global.render.height || body->aabb.position[1]<0)
                body->velocity[1] *= -1;

            if(body->velocity[0] > 500)
                body->velocity[0] = 500;
            if(body->velocity[0] < -500)
                body->velocity[0] = -500;
            if(body->velocity[1] > 500)
                body->velocity[1] = 500;
            if(body->velocity[1] < -500)
                body->velocity[1] = -500;
        }
        // Render physics body
        
        render_end();
        time_update_late();
    }

    return 0;
}
