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
        fprintf(stderr, "memory allocation failed\n");
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

    free(dir_path);
    return EXIT_SUCCESS;
}
