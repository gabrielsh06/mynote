#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void) {
    const char *home_dir = getenv("HOME");
    if (home_dir == nullptr) {
        fprintf(stderr, "HOME/ directory not found\n");
        return EXIT_FAILURE;
    }

    printf("HOME/ found in: %s\n", home_dir);

    const int len_dir_path = snprintf(nullptr, 0, "%s/.local/share/note", home_dir);
    char *dir_path = malloc(len_dir_path + 1);
    if (dir_path == nullptr) {
        fprintf(stderr, "memory allocation failed for dir_path\n");
        free(dir_path);
        return EXIT_FAILURE;
    }
    snprintf(dir_path, len_dir_path + 1, "%s/.local/share/note", home_dir);
    if (mkdir(dir_path, 0755) == -1) {
        if (errno == EEXIST) {
            fprintf(stdout, "directory exists in: %s\n", dir_path);
        } else {
            perror("error creating directory");
            free(dir_path);
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stdout, "directory created in: %s\n", dir_path);
    }

    const int len_file_path = snprintf(nullptr, 0, "%s/notes.txt", dir_path);
    char *file_path = malloc(len_file_path + 1);
    if (file_path == nullptr) {
        fprintf(stderr, "memory allocation failed for file_path\n");
        free(dir_path);
        free(file_path);
        return EXIT_FAILURE;
    }
    snprintf(file_path, len_file_path + 1, "%s/notes.txt", dir_path);
    FILE *file = fopen(file_path, "a");
    if (file == nullptr) {
        perror("failed to create or open file");
        free(dir_path);
        free(file_path);
        return EXIT_FAILURE;
    }

    fclose(file);
    free(file_path);
    free(dir_path);
    return EXIT_SUCCESS;
}
