#include <stdio.h>
#include <stdlib.h>

#include "paths.h"

static const char* const DIR_PATH = "/.local/share/note";
static const char* const FILE_PATH = "/notes.txt";

char *get_home_dir() {
    char* home_dir = getenv("HOME");
    if (!home_dir) {
        return nullptr;
    }
    return home_dir;
}

char *get_combined_path(const char *dir, const char *path) {
    const int len = snprintf(nullptr, 0, "%s%s", dir, path);
    if (len < 0) return nullptr;

    char *full_path = malloc(len + 1);
    if (full_path) {
        snprintf(full_path, len + 1,"%s%s", dir, path);
    }
    return full_path;
}

char *get_dir_path() {
    char *home_dir = get_home_dir();
    if (!home_dir) {
        return nullptr;
    }
    char *dir_path = get_combined_path(home_dir, DIR_PATH);
    if (!dir_path) {
        return nullptr;
    }
    return dir_path;
}

char *get_file_path() {
    char *full_dir_path = get_dir_path();
    if (!full_dir_path) {
        return nullptr;
    }
    char *file_path = get_combined_path(full_dir_path, FILE_PATH);
    if (!file_path) {
        return nullptr;
    }
    free(full_dir_path);
    return file_path;
}