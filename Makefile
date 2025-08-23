render=engine/render/render.c engine/render/render_init.c
files=main.c engine/global.c $(render)

glad=glad/src/glad.c -I./glad/include
libs=-lm `sdl2-config --cflags --libs` -lSDL2_mixer `pkg-config --libs glfw3` -ldl

build:
	gcc -g3 -O0 $(glad) $(files) $(libs) -o mainrun

clean:
	rm *.o mainrun
