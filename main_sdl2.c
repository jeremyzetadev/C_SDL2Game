#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
// On linux compile with:
// g++ -std=c++17 main.c glad/src/glad.c -I./glad/include -o main -lSDL2 -ldl

#include "glad/include/glad/glad.h"
#include <SDL2/SDL.h>

int main(int argc, char *argv[]){
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);

    if(SDL_Init(SDL_INIT_VIDEO) <0){
        printf("Could not init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow(
            "MyGame",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_OPENGL
            );

    if(!window){
        printf("Failed to init window: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_GL_CreateContext(window);
    // if(!gladLOADGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
    // // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    //     printf("Failed to load GL: %s\n", SDL_GetError());
    //     exit(1);
    // }
    gladLoadGL();

    puts("OpenGL Loaded");
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));

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
    }
    return 0;
}
