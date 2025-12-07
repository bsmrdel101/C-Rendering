#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include "../system/system.h"
#include "../file-system/file-system.h"


const u16 WIDTH = 800, HEIGHT = 600;
const u8 FRAME_DELAY = 16;
const u8 BG_COLOR[] = {0, 0, 0, 255};
char *background = NULL;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Vec2 windowSize = { 0, 0 };

/*
  INITIALIZATION
*/

int init() {
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
    return error("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }

  window = SDL_CreateWindow("Game", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    return error("Could not create window: %s\n", SDL_GetError());
  }

  renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    return error("Renderer Creation Error: %s\n", SDL_GetError());
  }
  return 0;
}

void set_background(char *path) {
  background = path;
}

/*
  IMAGE FUNCTIONS
*/

void load_img(char *path, const SDL_FRect *frame, const SDL_FRect *transform) {
  SDL_Texture *texture = IMG_LoadTexture(renderer, path);
  if(!texture) {
    error("Error creating texture: %s\n", SDL_GetError());
    return;
  }

  SDL_RenderTexture(renderer, texture, frame, transform);
  SDL_DestroyTexture(texture);
}

/*
  SHAPE FUNCTIONS
*/

void draw_square(Shape shape, const SDL_FRect *rect) {
  SDL_SetRenderDrawColor(renderer, shape.color[0], shape.color[1], shape.color[2], shape.color[3]);
  if (!SDL_RenderFillRect(renderer, rect)) {
    error("Error drawing square: %s\n", SDL_GetError());
    return;
  }
}

void draw_shape(Shape shape, const SDL_FRect *rect) {
  if (strcmp(shape.type, "square") == 0) {
    draw_square(shape, rect);
  }
}

/*
  DRAWING
*/

void draw_frame() {
  SDL_SetRenderDrawColor(renderer, BG_COLOR[0], BG_COLOR[1], BG_COLOR[2], BG_COLOR[3]);
  SDL_RenderClear(renderer);

  // Background
  int bgWidth, bgHeight;
  SDL_GetWindowSizeInPixels(window, &bgWidth, &bgHeight);
  windowSize.x = bgWidth;
  windowSize.y = bgHeight;
  SDL_FRect bgTransform = { 0, 0, (float)windowSize.x, (float)windowSize.y };
  load_img("assets/sprites/background.png", NULL, &bgTransform);

  // Sprites
  // cJSON *json = read_file("resources/game/game-objects.json");
  // for (int i = 0; i < cJSON_GetArraySize(json); i++) {
  //   cJSON *obj = cJSON_GetArrayItem(json, i);
  //   if (!cJSON_IsObject(obj)) continue;

  //   GameObject gameObject = parse_game_object(obj);
  //   draw_shape(gameObject.shape, &gameObject.rect);
  // }

  SDL_RenderPresent(renderer);
  SDL_Delay(FRAME_DELAY);
}
