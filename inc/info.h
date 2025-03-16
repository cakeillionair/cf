#ifndef INFO_H
#define INFO_H

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "colors.h"

/**
 * @brief filler character for displaying file permissions
 */
#define FILLER '-'

/**
 * @brief formats information of a file
 * @param path is the folder the file is in
 * @param file is the filename
 * @param buf is a buffer for storing the formatted information
 * @param color controls whether colors are used
 * @return a pointer to the buffer
 */
char *fmtinfo(char *path, char *file, char *buf, bool color);

#endif