#pragma once
#include <stdint.h>
#include <SDL3/SDL.h>
#include <cJSON/cJSON.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct {
  int x;
  int y;
} Vec2;

typedef struct {
  char *type;
  u8 color[4];
} Shape;

typedef struct {
  int id;
  char *name;
  char **tags;
  char *sprite;
  Shape shape;
  SDL_FRect rect;
  i16 rotation;
  bool active;
  cJSON components;
} GameObject;


int error(char *msg, ...);
void console_log(char *msg, ...);
