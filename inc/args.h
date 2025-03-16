#ifndef ARGS_H
#define ARGS_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "flags.h"
#include "list.h"
#include "wild.h"

/**
 * @brief parses arguments
 * @param argc is the amount of arguments
 * @param argv is an array of arguments
 * @param folders is a pointer to a list of folders
 * @param patterns is a pointer to a list of patterns
 * @return the parsed flags in a flag_t struct
 */
flag_t parseArgs(int argc, char *argv[], List *folders, List *patterns);

/**
 * @brief parses flags from a string
 * @param flag is a pointer to the string
 * @param flags is a pointer to a flag_t struct with the default flags
 * @return the parsed flags in a flag_t struct
 */
flag_t parseFlag(char *flag, flag_t *flags);

/**
 * @brief parses long flag starting with "--" from a string
 * @param arg0 is the name of the program
 * @param flag is a char pointer pointing to the string
 * @param flags is a pointer to a flag_t struct with the default flags
 * @return the parsed flag in a flag_t struct
 */
flag_t parseLongFlag(char *arg0, char *flag, flag_t *flags);

#endif