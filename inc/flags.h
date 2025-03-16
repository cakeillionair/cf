#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>

typedef enum Flag {
    RECURSIVE = 01,
    LIST_FILES = 02,
    QUIET = 04,
    COUNT_FILES = 010,
    COUNT_DIRS = 020,
    COUNT_REST = 040,
    COUNT_ALL = 070,
    REALPATH = 0100,
    ERROR = 01000
} Flag;

typedef uint32_t flag_t;

/**
 * @brief default flags for the program
 */
#define DEFAULT_FLAGS (COUNT_FILES | COUNT_DIRS)

/**
 * @brief checks flag
 * @param flags is a flag_t struct
 * @param name is the name of the flag
 * @return whether or not the flag is activated
 */
#define CHECKFLAG(flags, name) (((flags) & (name)) != 0)

#endif