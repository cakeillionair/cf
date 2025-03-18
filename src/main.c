/**
 * @author Jan Breithaupt
 * @date 15-03-2025
 * @version 1.4.1
 * @brief this program counts how many files are in a directory
 */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "args.h"
#include "dirl.h"
#include "list.h"

// TODO clean_up_flags fix_patterns exclude_dot_files_by_default add_readme_and_license

int main(int argc, char *argv[]) {
    List *folderList = emptyList();
    List *patternList = emptyList();
    int maxdepth = PATH_MAX / 2;

    flag_t flags = parseArgs(argc, argv, folderList, patternList, &maxdepth);
    if (flags == ERROR) return EXIT_FAILURE;
    if (CHECKFLAG(flags, QUIET) && CHECKFLAG(flags, LIST_FILES)) flags &= ~(LIST_FILES);
    if (patternList->size != 0) flags |= PATTERN;

    Count result, tmp;
    result.dirs = 0;
    result.files = 0;
    result.links = 0;
    result.other = 0;

    if (folderList->size == 0 && !CHECKFLAG(flags, ERROR)) listAppend(folderList, ".");
    foreach(folderList) {
        char *path = folderList->current->val;
        if (CHECKFLAG(flags, REALPATH)) {
            path = realpath(path, NULL);
        }
        if (countFiles(path, flags, patternList, &tmp, maxdepth) == 0) {
            result.dirs += tmp.dirs;
            result.files += tmp.files;
            result.links += tmp.links;
            result.other += tmp.other;
        }
        
        if (CHECKFLAG(flags, REALPATH)) free(path);
    }

    if (CHECKFLAG(flags, QUIET) || CHECKFLAG(flags, LIST_FILES)) {
        char fmt[128];
        sprintf(fmt, "TOTAL:\n%s%s%s%s"
            , (CHECKFLAG(flags, COUNT_DIRS) ? "- directories - %ld\n" : "")
            , (CHECKFLAG(flags, COUNT_FILES) ? "- files - %ld\n" : "")
            , (CHECKFLAG(flags, COUNT_REST) ? "- links - %ld\n" : "")
            , (CHECKFLAG(flags, COUNT_REST) ? "- other - %ld\n" : "")
        );
        printf(fmt
            , result.dirs
            , result.files
            , result.links
            , result.other);
    }

    freeList(folderList);
    free(folderList);
    freeList(patternList);
    free(patternList);

    return CHECKFLAG(flags, ERROR);
}