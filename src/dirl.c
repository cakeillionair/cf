#include "dirl.h"

long countFiles(char *path, flag_t flags, List *patterns) {
    List *dirList = emptyList();
    long count = 0;

    if (access(path, R_OK | X_OK) != 0) {
        printf("Error: access to '%s' denied\n", path);
        free(dirList);
        return -1;
    }
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (CHECKFLAG(flags, LIST_FILES)) printf("%s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        bool counts = false;

        switch (entry->d_type) {
            case DT_DIR: {
                if ((strcmp(".", entry->d_name) == 0) || (strcmp("..", entry->d_name) == 0)) break;
                if (CHECKFLAG(flags, COUNT_DIRS)) {
                    counts = true;
                    if (CHECKFLAG(flags, PATTERN)) {
                        counts = false;
                        foreach(patterns) {
                            if (checkWild(patterns->current->val, entry->d_name)) {
                                counts = true;
                                break;
                            }
                        }
                    }
                    if (counts) count++;
                }

                if (!CHECKFLAG(flags, RECURSIVE)) break;
                
                char *newpath = malloc(PATH_MAX);
                sprintf(newpath, "%s/%s", path, entry->d_name);
                listAppend(dirList, newpath);
            }break;
            case DT_REG: {
                if (!CHECKFLAG(flags, COUNT_FILES)) break;
                counts = true;
                if (CHECKFLAG(flags, PATTERN)) {
                    counts = false;
                    foreach(patterns) {
                        if (checkWild(patterns->current->val, entry->d_name)) {
                            counts = true;
                            break;
                        }
                    }
                }
                if (counts) count++;
            }break;
            default: {
                if (!CHECKFLAG(flags, COUNT_REST)) break;
                counts = true;
                if (CHECKFLAG(flags, PATTERN)) {
                    counts = false;
                    foreach (patterns) {
                        if (checkWild(patterns->current->val, entry->d_name)) {
                            counts = true;
                            break;
                        }
                    }
                }
                if (counts) count++;
            }break;
        }

        if (counts && CHECKFLAG(flags, LIST_FILES)) {
            char buf[128];

            printf("%s", fmtinfo(path, entry->d_name, buf, CHECKFLAG(flags, COLOR)));
        }
    }

    if (!CHECKFLAG(flags, QUIET) && CHECKFLAG(flags, LIST_FILES)) printf("count - %ld\n\n", count);

    if (CHECKFLAG(flags, RECURSIVE)) {
        char *newpath = pop(dirList);
        while (newpath != NULL) {
            long newcount = countFiles(newpath, flags, patterns);
            if (newcount != -1) count += newcount;
            free(newpath);
            newpath = pop(dirList);
        }
    }
    free(dirList);

    if (!CHECKFLAG(flags, QUIET) && !CHECKFLAG(flags, LIST_FILES)) printf("%s - %ld\n\n", path, count);

    closedir(dir);

    return count;
}