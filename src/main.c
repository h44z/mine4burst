#include <stdio.h>

#include "config.h"
#include "plot.h"
#include "tinycthread.h"

MinerConfig config;

int main(int argc, char **argv) {

    if (argc < 2) {
        config = load_miner_config(DEFAULT_CONFIG_PATH);
    } else {
        config = load_miner_config(argv[1]);
    }

    if (check_config(config)) {
        printf("Server: %s, Port: %d\n", config.server, config.port);

        for (int i = 0; i < sizeof(config.paths); i++) {
            printf("Found config path: %s\n", config.paths[i]);
            get_plotfiles_in_directory(config.paths[i]);
        }

    } else {
        printf("Invalid configuration loaded!\n");
    }

    return 0;
}