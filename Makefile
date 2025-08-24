io=src/engine/io/io.c
render=src/engine/render/render.c src/engine/render/render_init.c src/engine/render/render_util.c
files=src/main.c src/engine/global.c $(render) $(io)

glad=deps/src/glad.c -I./deps/include
libs=-lm `sdl2-config --cflags --libs` -lSDL2_mixer `pkg-config --libs glfw3` -ldl

build:
	gcc -g3 -O0 $(glad) $(files) $(libs) -o mainrun

clean:
	rm *.o mainrun
