#pragma once
#define MYNOTE_STORAGE_H
#include <stdio.h>

int create_dir(const char *dir_path);
int create_file(const char *path);
int write_file(const char *path, char *arg);
int read_file(const char *path);
int clear_file(const char *path);