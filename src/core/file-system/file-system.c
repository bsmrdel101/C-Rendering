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
