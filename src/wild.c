#include "wild.h"

bool isWild(char *string) {
    for (int i = 0; string[i] != '\0'; i++) if (string[i] == WILD) return true;
    return false;
}

bool checkWild(char *pattern, char *string) {
    bool wild = false;

    int j = 0;
    for (int i = 0; pattern[i] != '\0'; i++) {
        if (pattern[i] == WILD) {
            wild = true;
            while (pattern[i] == WILD) i++;
        }
        if (wild) {
            if (pattern[i] == '\0') return true;
            int len = 0;
            while (pattern[i + len] != WILD && pattern[i + len] != '\0') len++;

            if (pattern[i + len] == '\0') while (string[j + len] != '\0') j++;
            while (strncmp(&pattern[i], &string[j], len) != 0 && string[j] != '\0') j++;

            if (string[j] == '\0') return false;
            i += len - 1;
            j += len;
            wild = false;
        } else {
            if (string[j] == '\0') return (pattern[i] == '\0');
            if (pattern[i] != string[j++]) return false;
            if (pattern[i + 1] == '\0' && string[j] != '\0') return false;
            if (pattern[i + 1] != '\0' && string[j] == '\0') return false;
        }
    }
    if (string[j] != '\0') return false;
    return true;
}