arraylist=src/engine/arraylist/arraylist.c
config=src/engine/config/config.c
global=src/engine/global/global.c
io=src/engine/io/io.c
render=src/engine/render/render.c src/engine/render/render_init.c src/engine/render/render_util.c
input=src/engine/input/input.c
physics=src/engine/physics/physics.c
time=src/engine/time/time.c

files=src/main.c $(arraylist) $(config) $(global) $(input) $(io) $(render) $(physics) $(time)

glad=deps/src/glad.c -I./deps/include
libs=-lm `sdl2-config --cflags --libs` -lSDL2_mixer `pkg-config --libs glfw3` -ldl

build:
	gcc -g3 -O0 $(glad) $(files) $(libs) -o mainrun

clean:
	rm *.o mainrun
