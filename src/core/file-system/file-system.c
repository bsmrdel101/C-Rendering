#include <stdio.h>
#include <stdlib.h>
#include <cJSON/cJSON.h>
#include "../system/system.h"


cJSON* read_file(char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    error("Failed to open file");
    return NULL;
  }

  // Get file length
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *buffer = (char *)malloc(file_size + 1);
  if (buffer == NULL) {
    error("Failed to allocate buffer");
    fclose(file);
    return NULL;
  }

  // Read file contents to buffer
  size_t bytes_read = fread(buffer, 1, file_size, file);
  if (bytes_read != file_size) {
    error("Failed to read entire file: %i read, %i total", bytes_read, file_size);
    free(buffer);
    fclose(file);
    return NULL;
  }
  buffer[file_size] = '\0';
  fclose(file);

  cJSON *json = cJSON_Parse(buffer);
  if (json == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      console_log("ERROR before:");
      error("%s\n", error_ptr);
    }
    free(buffer);
    return NULL;
  }
  free(buffer);
  return json;
}

GameObject parse_game_object(cJSON *json) {
  cJSON *idJson = cJSON_GetObjectItemCaseSensitive(json, "id");
  cJSON *nameJson = cJSON_GetObjectItemCaseSensitive(json, "name");
  cJSON *spriteJson = cJSON_GetObjectItemCaseSensitive(json, "sprite");
  cJSON *rotationJson = cJSON_GetObjectItemCaseSensitive(json, "rotation");
  cJSON *activeJson = cJSON_GetObjectItemCaseSensitive(json, "active");
  cJSON *rectJson = cJSON_GetObjectItemCaseSensitive(json, "rect");
  cJSON *xJson = cJSON_GetObjectItemCaseSensitive(rectJson, "x");
  cJSON *yJson = cJSON_GetObjectItemCaseSensitive(rectJson, "y");
  cJSON *wJson = cJSON_GetObjectItemCaseSensitive(rectJson, "w");
  cJSON *hJson = cJSON_GetObjectItemCaseSensitive(rectJson, "h");
  SDL_FRect rect = { .x = xJson->valuedouble, .y = yJson->valuedouble, .w = wJson->valuedouble, .h = hJson->valuedouble };

  cJSON *tagsJson = cJSON_GetObjectItemCaseSensitive(json, "tags");
  char **tags = malloc(sizeof(char*) * (cJSON_GetArraySize(tagsJson) + 1));
  for (int i = 0; i < cJSON_GetArraySize(tagsJson); i++) {
    cJSON *item = cJSON_GetArrayItem(tagsJson, i);
    tags[i] = item->valuestring;
  }

  cJSON *shapeJson = cJSON_GetObjectItemCaseSensitive(json, "shape");
  cJSON *typeJson = cJSON_GetObjectItemCaseSensitive(shapeJson, "type");
  cJSON *colorJson = cJSON_GetObjectItemCaseSensitive(shapeJson, "color");
  u8 colorValues[4] = {0, 0, 0, 255};
  for (int i = 0; i < cJSON_GetArraySize(colorJson); i++) {
    cJSON *item = cJSON_GetArrayItem(colorJson, i);
    colorValues[i] = (u8)item->valueint;
  }
  Shape shape;
  shape.type = typeJson->valuestring;
  memcpy(shape.color, colorValues, sizeof(shape.color));
  free(tags);

  return (GameObject){ 
    .id = idJson->valueint,
    .name = nameJson->valuestring,
    .tags = tags,
    .sprite = spriteJson->valuestring,
    .shape = shape,
    .rect = rect,
    .rotation = rotationJson->valuedouble,
    .active = (bool)activeJson->valueint
  };
}
