#include <errno.h>
#include <sys/stat.h>

#include "paths.h"
#include "storage.h"

int create_dir(const char *dir_path) {
    if (mkdir(dir_path, 0755) == 1) {
        if (errno != EEXIST) {
            perror("HOME/ directory not found");
            return 1;
        }
    }
    return 0;
}

int create_file(const char *path) {
    FILE *file = fopen(path, "a");
    if (!file) {
        perror("failed to create or open file");
        return 1;
    }
    fclose(file);
    return 0;
}

int write_file(const char *path, char *arg) {
    FILE *file = fopen(path, "a");
    if (!file) {
        perror("failed to create or open file");
        return 1;
    }
    fprintf(file, "%s\n", arg);
    fclose(file);
    return 0;
}

int read_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        perror("failed to open file");
        return 1;
    }
    char linea[256];
    while (fgets(linea, sizeof(linea), file) != nullptr) {
        printf("%s", linea);
    }
    fclose(file);
    return 0;
}

int clear_file(const char *path) {
    FILE *file = fopen(path, "w");
    if (!file) {
        perror("failed to clear file");
        return 1;
    }
    fclose(file);
    return 0;
}