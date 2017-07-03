#include "helper.h"

char *load_file_to_string(char *file_path) {
    char *buffer = 0;
    long length;
    FILE *file = fopen(file_path, "rb");

    if (file) {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, file);
        }
        fclose(file);
    } else {
        printf("File not found or not accessible!\n");
    }

    return buffer;
}