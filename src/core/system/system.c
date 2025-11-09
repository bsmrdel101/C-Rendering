#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>


int error(char *msg, ...) {
  SDL_Log(msg);
  return 1;
}

void console_log(char *msg, ...) {
  SDL_Log(msg);
}
