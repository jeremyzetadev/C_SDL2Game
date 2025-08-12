#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
// On linux compile with:
// g++ -std=c++17 main.c glad/src/glad.c -I./glad/include -o main -lSDL2 -ldl

#include "engine/global.h"
#include "glad/include/glad/glad.h"
#include <SDL2/SDL.h>

int main(int argc, char *argv[]){
    puts("Hello there!");

    bool should_quit =false;

    while(!should_quit){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    should_quit=true;
                    break;
                default:
                    break;
            }
        }
        
        render_begin();

        render_quad(
                (vec2){global.render.width * 0.5, global.render.height *0.5},
                (vec2){50,50},
                (vec4){1,1,1,1});

        render_end();
    }
    return 0;
}
