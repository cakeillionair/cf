#include "dirl.h"

long countFiles(char *path, flag_t flags) {
    List *dirList = emptyList();
    long count = 0;

    DIR *dir = opendir(path);
    struct dirent *entry;

    if (CHECKFLAG(flags, LIST_FILES)) printf("%s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        switch (entry->d_type) {
            case DT_DIR: {
                if ((strcmp(".", entry->d_name) == 0) || (strcmp("..", entry->d_name) == 0)) break;
                if (CHECKFLAG(flags, COUNT_DIRS)) {
                    count++;
                    if (CHECKFLAG(flags, LIST_FILES)) printf("  %s/%s/\n", path, entry->d_name);
                }

                if (!CHECKFLAG(flags, RECURSIVE)) break;
                
                char *newpath = malloc(PATH_MAX);
                sprintf(newpath, "%s/%s", path, entry->d_name);
                listAppend(dirList, newpath);
            }break;
            case DT_REG: {
                if (!CHECKFLAG(flags, COUNT_FILES)) break;
                count++;
                if (CHECKFLAG(flags, LIST_FILES)) printf("  %s/%s\n", path, entry->d_name);
            }break;
            default: {
                if (!CHECKFLAG(flags, COUNT_ALL)) break;
                count++;
                if (CHECKFLAG(flags, LIST_FILES)) printf("  %s/%s\n", path, entry->d_name);
            }break;
        }
    }

    if (CHECKFLAG(flags, RECURSIVE)) {
        char *newpath = pop(dirList);
        while (newpath != NULL) {
            long newcount = countFiles(newpath, flags);
            if (newcount != -1) count += newcount;
            free(newpath);
            newpath = pop(dirList);
        }
    }
    free(dirList);

    if (!CHECKFLAG(flags, QUIET)) {
        if (CHECKFLAG(flags, LIST_FILES)) {
            printf("count - %ld\n\n", count);
        } else printf("%s - %ld\n\n", path, count);
    }

    closedir(dir);

    return count;
}