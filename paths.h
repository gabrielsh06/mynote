#pragma once
#define MYNOTE_PATHS_H

char *get_home_dir();
char *get_combined_path(const char *dir, const char *path);
char *get_dir_path();
char *get_file_path();