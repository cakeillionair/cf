/**
 * @author Jan Breithaupt
 * @date 15-03-2025
 * @version 1.0.0
 * @brief this program counts how many files are in a directory
 */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "args.h"
#include "dirl.h"
#include "list.h"

// TODO add_more_file_types add_color add_max_depth add_regex

int main(int argc, char *argv[]) {
    List *folderList = emptyList();

    flag_t flags = parseArgs(argc, argv, folderList);
    if (flags == ERROR) return EXIT_FAILURE;
    if (CHECKFLAG(flags, QUIET) && CHECKFLAG(flags, LIST_FILES)) flags &= ~(LIST_FILES);

    long count = 0;
    if (folderList->size == 0) listAppend(folderList, ".");
    foreach(folderList) {
        char *path = folderList->current->val;
        if (CHECKFLAG(flags, REALPATH)) {
            path = realpath(path, NULL);
        }
        count += countFiles(path, flags);
        if (CHECKFLAG(flags, REALPATH)) free(path);
    }

    if (CHECKFLAG(flags, QUIET)) printf("count - %ld\n", count);

    freeList(folderList);
    free(folderList);

    return CHECKFLAG(flags, ERROR);
}