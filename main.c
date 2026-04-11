#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *home_dir = getenv("HOME");
    if (home_dir == nullptr) {
        fprintf(stderr, "HOME/ directory not found\n");
        return EXIT_FAILURE;
    }
    printf("HOME/ found in: %s\n", home_dir);
    return EXIT_SUCCESS;
}
