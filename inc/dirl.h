#ifndef DIRL_H
#define DIRL_H

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "list.h"
#include "flags.h"
#include "wild.h"

/**
 * @brief counts files in a directory
 * @param path is the path of the directory
 * @param flags gives more control over the behaviour
 * @param patterns is a pointer to a list containing patterns
 * @return the amount of files in a directory
 */
long countFiles(char *path, flag_t flags, List *patterns);

#endif