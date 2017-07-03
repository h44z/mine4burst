#ifndef mineconfig__h
#define mineconfig__h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../external/cJSON/cJSON_Utils.h"
#include "helper.h"

#ifdef __linux__
#define DEFAULT_CONFIG_PATH "~/.config/mine4burst/config.json"
#elif _WIN32
#define DEFAULT_CONFIG_PATH "%appdata%/mine4burst/config.json"
#endif

#define CONFIG_FIELD_SERVER "server"
#define CONFIG_FIELD_PORT "port"
#define CONFIG_FIELD_TARGET_DEADLINE "targetdeadline"
#define CONFIG_FIELD_PATHS "paths"

typedef struct MinerConfig {
    char *server;
    char **paths;
    int port;

    int target_deadline;
} MinerConfig;

// private/internal
char **_load_plot_paths(cJSON *root_path_item);

void _init_config(MinerConfig *config);

// public
MinerConfig load_miner_config(char *config_file_path);

int check_config(MinerConfig config);

#endif