#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "core/system/system.h"
#include "core/rendering/rendering.h"
#include "core/file-system/file-system.h"


int main(int argc, char *argv[]) {
  if(init() == 1) {
    return error("Error during initialization");
  }

  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) running = false;
    }

    draw_frame();
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
