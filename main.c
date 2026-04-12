#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static const char* const DIR_PATH = "/.local/share/note";
static const char* const FILE_PATH = "/notes.txt";

char* get_combined_path (const char *dir, const char *path);

int main(void) {
    FILE *file = nullptr;
    char *file_path = nullptr;
    char *dir_path = nullptr;
    int status = EXIT_FAILURE;

    const char *home_dir = getenv("HOME");
    if (!home_dir) {
        fprintf(stderr, "HOME/ directory not found\n");
        goto cleanup;
    }

    printf("HOME/ found in: %s\n", home_dir);

    dir_path = get_combined_path(home_dir, DIR_PATH);
    if (!dir_path) {
        fprintf(stderr, "memory allocation failed for dir_path\n");
        goto cleanup;
    }
    if (mkdir(dir_path, 0755) == -1) {
        if (errno != EEXIST) {
            perror("error creating directory");
            goto cleanup;
        }
        fprintf(stdout, "directory exists in: %s\n", dir_path);
    } else {
        fprintf(stdout, "directory created in: %s\n", dir_path);
    }

    file_path = get_combined_path(dir_path, FILE_PATH);
    if (!file_path) {
        fprintf(stderr, "memory allocation failed for file_path\n");
        goto cleanup;
    }
    file = fopen(file_path, "a");
    if (!file) {
        perror("failed to create or open file");
        goto cleanup;
    }

    status = EXIT_SUCCESS;
    cleanup:
    if (file) fclose(file);
    free(file_path);
    free(dir_path);
    return status;
}

char* get_combined_path (const char *dir, const char *path) {
    const int len = snprintf(nullptr, 0, "%s%s", dir, path);
    if (len < 0) return nullptr;

    char *full_path = malloc(len + 1);
    if (full_path) {
        snprintf(full_path, len + 1,"%s%s", dir, path);
    }
    return full_path;
}