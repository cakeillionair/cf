#include "dirl.h"

int countFiles(char *path, flag_t flags, List *patterns, Count *result) {
    List *dirList = emptyList();
    result->dirs = 0;
    result->files = 0;
    result->other = 0;

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
                    if (counts) result->dirs++;
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
                if (counts) result->files++;
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
                if (counts) result->other++;
            }break;
        }

        if (counts && CHECKFLAG(flags, LIST_FILES)) {
            char buf[128];

            printf("%s", fmtinfo(path, entry->d_name, buf, CHECKFLAG(flags, COLOR)));
        }
    }

    if (!CHECKFLAG(flags, QUIET) && CHECKFLAG(flags, LIST_FILES)) printf("- directories - %ld\n- files - %ld\n- other %ld\n\n"
        , result->dirs, result->files, result->other);

    if (CHECKFLAG(flags, RECURSIVE)) {
        char *newpath = pop(dirList);
        Count newCount;

        while (newpath != NULL) {
            if (countFiles(newpath, flags, patterns, &newCount) == 0) {
                result->dirs += newCount.dirs;
                result->files += newCount.files;
                result->other += newCount.other;
            }
            free(newpath);
            newpath = pop(dirList);
        }
    }
    free(dirList);

    if (!CHECKFLAG(flags, QUIET) && !CHECKFLAG(flags, LIST_FILES)) {
        printf("%s:\n- directories - %ld\n- files - %ld\n- other - %ld\n", path, result->dirs, result->files, result->other);
    }

    closedir(dir);

    return 0;
}