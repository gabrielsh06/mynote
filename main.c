#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paths.h"
#include "storage.h"

int main(const int argc, char *argv[]) {
    char *file_path = nullptr;
    char *dir_path = nullptr;
    int status = EXIT_FAILURE;

    if (argc < 2) {
        fprintf(stdout, "use: mynote \"your notes\"\n");
        fprintf(stdout, "     mynote --list\n");
        fprintf(stdout, "     mynote --clear\n");
        status = EXIT_SUCCESS;
        goto cleanup;
    }

    dir_path = get_dir_path();
    if (!dir_path) {
        perror("memory allocation failed for dir_path");
        goto cleanup;
    }

    if (create_dir(dir_path)) {
        goto cleanup;
    }

    file_path = get_file_path();
    if (!file_path) {
        perror("memory allocation failed for file_path");
        goto cleanup;
    }


    if (create_file(file_path)) {
        goto cleanup;
    }

    if (strcmp(argv[1], "--list") == 0) {
        if (read_file(file_path)) {
            goto cleanup;
        }
    } else if (strcmp(argv[1], "--clear") == 0) {
        if (clear_file(file_path)) {
            goto cleanup;
        }
    } else {
        if (write_file(file_path, argv[1])) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;
    cleanup:
    free(file_path);
    free(dir_path);
    return status;
}