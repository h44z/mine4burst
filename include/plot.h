#ifndef mineplot__h
#define mineplot__h

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <dirent.h>
#elif _WIN32

#include <windows.h>

#endif

typedef struct PlotFile {
    char *path;
    long long size;
    unsigned long long address;
    unsigned long long start_nonce;
    unsigned long nonces;
    unsigned long staggeramt;
} PlotFile;

// private
PlotFile _parse_filename(char *path, char *file_name);

void _init_plotfile(PlotFile *file);

// public
PlotFile **get_plotfiles_in_directory(char *directory);

#endif