#include "plot.h"

#ifdef __linux__

PlotFile **getPlotFilesInDirectory(char * directory) {
    DIR           *plot_directory;
    struct dirent *dir_entry;
    
    plot_directory = opendir(directory);
    
    if(plot_directory) {
        while ((dir_entry = readdir(plot_directory)) != NULL) {
            if(strncmp(dir_entry->d_name, ".", 1) != 0 && strncmp(dir_entry->d_name, "..", 2) != 0) {
                printf("File: %s\n", dir_entry->d_name);
            }
        }
        
        closedir(plot_directory);
    } else {
        printf("Plot directory not found!\n");
    }
}

#elif _WIN32

// windows does not support strsep -.-
char *strsep(char **stringp, const char *delim) {
    if (*stringp == NULL) { return NULL; }
    char *token_start = *stringp;
    *stringp = strpbrk(token_start, delim);
    if (*stringp) {
        **stringp = '\0';
        (*stringp)++;
    }
    return token_start;
}

PlotFile **get_plotfiles_in_directory(char *directory) {
    HANDLE h_find;
    WIN32_FIND_DATA fd_file;

    char plot_path[4069];
    snprintf(plot_path, sizeof(plot_path), "%s\\*.*", directory);

    h_find = FindFirstFile(plot_path, &fd_file);

    if (h_find != INVALID_HANDLE_VALUE) {
        while (FindNextFile(h_find, &fd_file)) {
            if (FILE_ATTRIBUTE_DIRECTORY & fd_file.dwFileAttributes) continue; //Skip directories
            if (strncmp(fd_file.cFileName, ".", 1) == 0 && strncmp(fd_file.cFileName, "..", 2) == 0)
                continue; // Skip base dir

            printf("File: %s\n", fd_file.cFileName);
            PlotFile p = _parse_filename(fd_file.cFileName);
            printf("%llu, %llu\n", p.address, p.start_nonce);
        }
    } else {
        printf("Plot directory not found!\n");
    }

    // Close the file handle
    FindClose(h_find);

    return NULL;
}

#endif


PlotFile _parse_filename(char *file_name) {
    char *name = strdup(file_name);
    char *token = name, *end = name;
    PlotFile plot;
    _init_plotfile(&plot);

    int counter = 0;
    while (token != NULL) {
        strsep(&end, "_");
        switch (counter++) {
            case 0:
                plot.address = strtoull(token, 0, 10);
                break;
            case 1:
                plot.start_nonce = strtoull(token, 0, 10);
                break;
            case 2:
                plot.nonces = strtoul(token, 0, 10);
                break;
            case 3:
                plot.staggeramt = strtoul(token, 0, 10);
                break;
            default:
                break;
        }
        token = end;
    }

    free(name);

    return plot;
}

void _init_plotfile(PlotFile *plot) {
    plot->path = 0;
    plot->size = 0;
    plot->address = 0;
    plot->start_nonce = 0;
    plot->nonces = 0;
    plot->staggeramt = 0;
}