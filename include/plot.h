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
    unsigned long int size;
    unsigned long long int address;
    unsigned long long int start_nonce;
    unsigned long int nonces;
    unsigned long int staggeramt;
} PlotFile;

// private
PlotFile _parse_filename(char *file_name);

void _init_plotfile(PlotFile *file);

// public
PlotFile **get_plotfiles_in_directory(char *directory);

#endif