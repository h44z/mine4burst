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

#ifdef __linux__
long long get_file_size(char *file_path) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return (long long) st.st_size;
    return -1;
}
#elif _WIN32

long long get_file_size(char *file_path) {
    HANDLE h_file = CreateFile(file_path, GENERIC_READ,
                               FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL, NULL);
    if (h_file == INVALID_HANDLE_VALUE)
        return -1; // error condition, could call GetLastError to find out more

    LARGE_INTEGER size;
    if (!GetFileSizeEx(h_file, &size)) {
        CloseHandle(h_file);
        return -1; // error condition, could call GetLastError to find out more
    }

    CloseHandle(h_file);
    return size.QuadPart;
}

#endif