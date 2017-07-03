#ifndef minehelper__h
#define minehelper__h

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <sys/stat.h>
#elif _WIN32

#include <windows.h>

#endif

char *load_file_to_string(char *file_path);
long long get_file_size(char *file_path);

#endif