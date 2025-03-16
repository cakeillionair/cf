/**
 * @author Jan Breithaupt
 * @date 15-03-2025
 * @version 1.3.2
 * @brief this program counts how many files are in a directory
 */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "args.h"
#include "dirl.h"
#include "list.h"

// TODO add_more_file_types add_max_depth clean_up_flags

int main(int argc, char *argv[]) {
    List *folderList = emptyList();
    List *patternList = emptyList();

    flag_t flags = parseArgs(argc, argv, folderList, patternList);
    if (flags == ERROR) return EXIT_FAILURE;
    if (CHECKFLAG(flags, QUIET) && CHECKFLAG(flags, LIST_FILES)) flags &= ~(LIST_FILES);
    if (patternList->size != 0) flags |= PATTERN;

    Count result, tmp;
    if (folderList->size == 0 && !CHECKFLAG(flags, ERROR)) listAppend(folderList, ".");
    foreach(folderList) {
        char *path = folderList->current->val;
        if (CHECKFLAG(flags, REALPATH)) {
            path = realpath(path, NULL);
        }
        if (countFiles(path, flags, patternList, &tmp) == 0) {
            result.dirs += tmp.dirs;
            result.files += tmp.files;
            result.other += tmp.other;
        }
        
        if (CHECKFLAG(flags, REALPATH)) free(path);
    }

    if (CHECKFLAG(flags, QUIET) || CHECKFLAG(flags, LIST_FILES)) {
        printf("TOTAL:\n- directories - %ld\n- files - %ld\n- other - %ld\n", result.dirs, result.files, result.other);
    }

    freeList(folderList);
    free(folderList);
    freeList(patternList);
    free(patternList);

    return CHECKFLAG(flags, ERROR);
}