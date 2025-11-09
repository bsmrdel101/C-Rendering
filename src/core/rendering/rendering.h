#pragma once
#include "../system/system.h"
#include <SDL3/SDL.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern Vec2 windowSize;

int init();
void draw_frame();
void set_background(char *path);
void load_img(char *path, const SDL_FRect *frame, const SDL_FRect *transform);
// int loadAnim(char *path, SDL_FRect *frames, i8 frameCount, SDL_FRect *transform);
