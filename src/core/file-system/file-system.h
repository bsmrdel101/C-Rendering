#pragma once
#include <cJSON/cJSON.h>

cJSON* read_file(char *path);
GameObject parse_game_object(cJSON *json);
