#ifndef DIRL_H
#define DIRL_H

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "flags.h"

/**
 * @brief counts files in a directory
 * @param path is the path of the directory
 * @param flags gives more control over the behaviour
 * @return the amount of files in a directory
 */
long countFiles(char *path, flag_t flags);

#endif