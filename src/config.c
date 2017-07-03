#include "config.h"

char **_load_plot_paths(cJSON *root_path_item) {
    // first count number of file paths
    cJSON *path_item = root_path_item->child;
    int path_count = 0;
    while (path_item) {
        if (cJSON_IsString(path_item)) {
            path_count++;
        }
        path_item = path_item->next;
    }

    // allocate memory for path array
    char **paths = malloc(path_count * sizeof(char *));

    // copy paths to array
    path_item = root_path_item->child;
    int path_index = 0;
    while (path_item) {
        if (cJSON_IsString(path_item)) {
            paths[path_index] = strdup(path_item->valuestring);
            path_index++;
        }

        path_item = path_item->next;
    }

    return paths;
}

MinerConfig load_miner_config(char *config_file_path) {
    char *config_buffer = load_file_to_string(config_file_path);
    MinerConfig config;

    _init_config(&config);

    if (config_buffer) {
        cJSON *root = cJSON_Parse(config_buffer);
        cJSON *server_item = cJSON_GetObjectItem(root, CONFIG_FIELD_SERVER);
        cJSON *port_item = cJSON_GetObjectItem(root, CONFIG_FIELD_PORT);
        cJSON *deadline_item = cJSON_GetObjectItem(root, CONFIG_FIELD_TARGET_DEADLINE);
        cJSON *root_path_item = cJSON_GetObjectItem(root, CONFIG_FIELD_PATHS);

        if (cJSON_IsString(server_item)) {
            config.server = strdup(server_item->valuestring);
        }
        if (cJSON_IsNumber(port_item)) {
            config.port = port_item->valueint;
        }
        if (cJSON_IsNumber(deadline_item)) {
            config.target_deadline = deadline_item->valueint;
        }
        if (cJSON_IsArray(root_path_item)) {
            config.paths = _load_plot_paths(root_path_item);
        }

        cJSON_Delete(root); // clean up json
        free(config_buffer); // clean config string buffer
    } else {
        printf("Config loading failed!\n");
    }

    return config;
}

void _init_config(MinerConfig *config) {
    config->server = 0;
    config->paths = 0;
    config->port = 0;
    config->target_deadline = 0;
}

int check_config(MinerConfig config) {
    int status = 1;

    if (!config.server) status = 0;
    if (!config.port) status = 0;
    if (!config.target_deadline) status = 0;
    if (!config.paths) status = 0;

    return status;
}