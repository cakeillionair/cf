#include "args.h"

#define VERSION "1.0.0"

void usage(char *arg0) {
    printf(
        "Usage: %s [OPTION]... [DIRECTORY]..."                                                     "\n"
        "Counts the amount of regular files in the DIRECTORYs (the current directory by default)." "\n"
        ""                                                                                         "\n"
        "  -a, --all                  count all files (excluding . and ..)"                        "\n"
        "  -d, --directories          only counts directories (included in --all)"                 "\n"
        "  -f, --files                only counts files. This is the default behaviour"            "\n"
        "                             can be combined with other file types such as -d"            "\n"
        "  -l, --list                 lists files that are counted"                                "\n"
        "  -q, --quiet                only prints the total amount counted and nothing else"       "\n"
        "  -r, --realpath             prints the real paths of files and directories"              "\n"
        "  -R, --recursive            counts files in subdirectories recursively"                  "\n"
        "      --help                 display this help and exit"                                  "\n"
        ""                                                                                         "\n"
        "Color is not supported at the moment"                                                     "\n"
        ""                                                                                         "\n"
        "Exit status:"                                                                             "\n"
        " 0  if Ok,"                                                                               "\n"
        " 1  if error."                                                                            "\n"
        , arg0
    );
}

void version() {
    printf(
        "cf " VERSION               "\n"
        ""                          "\n"
        "Written by Jan Breithaupt" "\n"
    );
}

flag_t parseArgs(int argc, char *argv[], List *folders) {
    flag_t flags = 0;
    flag_t defaults = DEFAULT_FLAGS;
    
    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];

        if (arg[0] == '-' && arg[1] == '-') {
            flags |= parseLongFlag(argv[0], arg, &defaults, folders);
            if (CHECKFLAG(defaults, ERROR)) return flags;
        } else if (arg[0] == '-') {
            flags |= parseFlag(arg, &defaults);
            if (CHECKFLAG(defaults, ERROR)) return flags;
        } else {
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
            case 'R': {
                newflags |= RECURSIVE;
            }break;
            case 'r': {
                newflags |= REALPATH;
            }break;
            case 'a': {
                newflags |= COUNT_ALL;
            }break;
            case 'd': {
                newflags |= COUNT_DIRS;
                *flags &= ~(COUNT_FILES);
            }break;
            case 'f': {
                newflags |= COUNT_FILES;
            }break;
            case 'q': {
                newflags |= QUIET;
            }break;
            case 'l': {
                newflags |= LIST_FILES;
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

flag_t parseLongFlag(char *arg0, char *flag, flag_t *flags, List *folderList) {
    flag_t newflags = 0;

    if (strcmp(flag + 2, "help") == 0) {
        usage(arg0);
        freeList(folderList);
        free(folderList);
        exit(0);
    } else if (strcmp(flag + 2, "version") == 0) {
        version();
        freeList(folderList);
        free(folderList);
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
    } else {
        printf("Error: unknown flag - '%s'\n", flag + 2);
        *flags = ERROR;
        return ERROR;
    }

    return newflags;
}