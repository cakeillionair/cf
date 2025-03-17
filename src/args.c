#include "args.h"

#define VERSION "1.3.4"

void usage(char *arg0) {
    printf(
        "Usage: %s [OPTION]... [DIRECTORY]... [PATTERN]..."                                        "\n"
        "Counts the amount of regular files in the DIRECTORYs (the current directory by default)." "\n"
        ""                                                                                         "\n"
        "  -a, --all                  count all files (excluding . and ..)"                        "\n"
        "  -c, --color                forces colored output"                                       "\n"
        "      --no-color             disables colored output"                                     "\n"
        "  -d, --directories          only counts directories (included in --all)"                 "\n"
        "  -f, --files                only counts files. This is the default behaviour"            "\n"
        "                             can be combined with other file types such as -d"            "\n"
        "  -l, --list                 lists files that are counted"                                "\n"
        "  -q, --quiet                only prints the total amount counted and nothing else"       "\n"
        "  -r, --recursive            counts files in subdirectories recursively"                  "\n"
        "  -p, --realpath             prints the real paths of files and directories"              "\n"
        "      --help                 display this help and exit"                                  "\n"
        ""                                                                                         "\n"
        "Color is set to auto by default."                                                         "\n"
        ""                                                                                         "\n"
        "If a PATTERN (or multiple) is given, only file that fit the pattern are counted."         "\n"
        "To create a pattern use the character '%c' as a wildcard."                                "\n"
        ""                                                                                         "\n"
        "Exit status:"                                                                             "\n"
        " 0  if Ok,"                                                                               "\n"
        " 1  if error."                                                                            "\n"
        , arg0, WILD
    );
}

void version() {
    printf(
        "cf " VERSION               "\n"
        ""                          "\n"
        "Written by Jan Breithaupt" "\n"
    );
}

flag_t parseArgs(int argc, char *argv[], List *folders, List *patterns) {
    flag_t flags = 0;
    flag_t defaults = DEFAULT_FLAGS;
    if (isatty(STDOUT_FILENO)) defaults |= COLOR;
    
    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];

        if (arg[0] == '-' && arg[1] == '-') {
            flags |= parseLongFlag(argv[0], arg, &defaults);
            if (CHECKFLAG(defaults, ERROR)) return flags;
        } else if (arg[0] == '-') {
            flags |= parseFlag(arg, &defaults);
            if (CHECKFLAG(defaults, ERROR)) return flags;
        } else {
            if (isWild(arg)) {
                listAppend(patterns, arg);
                continue;
            }

            DIR *dir = opendir(arg);
            if (dir == NULL) {
                printf("Error: could not open folder \"%s\"\n", arg);
                flags |= ERROR;
            } else {
                closedir(dir);
                listAppend(folders, arg);
            }
        }
    }

    return flags | defaults;
}

flag_t parseFlag(char *flag, flag_t *flags) {
    flag_t newflags = 0;

    for (int i = 1; flag[i] != '\0'; i++) {
        switch (flag[i]) {
            case 'r': {
                newflags |= RECURSIVE;
            }break;
            case 'p': {
                newflags |= REALPATH;
            }break;
            case 'a': {
                newflags |= COUNT_ALL;
            }break;
            case 'd': {
                newflags |= COUNT_DIRS;
                *flags &= ~(COUNT_ALL);
            }break;
            case 'f': {
                newflags |= COUNT_FILES;
                *flags &= ~(COUNT_ALL);
            }break;
            case 'q': {
                newflags |= QUIET;
            }break;
            case 'l': {
                newflags |= LIST_FILES;
            }break;
            case 'c': {
                newflags |= COLOR;
            }break;
            default: {
                printf("Error: unknown flag - '%c'\n", flag[i]);
                *flags = ERROR;
                return ERROR;
            }break;
        }
    }

    return newflags;
}

flag_t parseLongFlag(char *arg0, char *flag, flag_t *flags) {
    flag_t newflags = 0;

    if (strcmp(flag + 2, "help") == 0) {
        usage(arg0);
        exit(0);
    } else if (strcmp(flag + 2, "version") == 0) {
        version();
        exit(0);
    } else if (strcmp(flag + 2, "recursive") == 0) {
        newflags = RECURSIVE;
    } else if (strcmp(flag + 2, "realpath") == 0) {
        newflags = REALPATH;
    } else if (strcmp(flag + 2, "all") == 0) {
        newflags = COUNT_ALL;
    } else if (strcmp(flag + 2, "directories") == 0) {
        newflags = COUNT_DIRS;
        *flags &= ~(COUNT_FILES);
    } else if (strcmp(flag + 2, "files") == 0) {
        newflags = COUNT_FILES;
    } else if (strcmp(flag + 2, "quiet") == 0) {
        newflags = QUIET;
    } else if (strcmp(flag + 2, "list") == 0) {
        newflags = LIST_FILES;
    } else if (strcmp(flag + 2, "color") == 0) {
        newflags = COLOR;
    } else if (strcmp(flag + 2, "no-color") == 0) {
        *flags &= ~(COLOR);
    } else {
        printf("Error: unknown flag - '%s'\n", flag + 2);
        *flags = ERROR;
        return ERROR;
    }

    return newflags;
}