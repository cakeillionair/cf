#ifndef WILD_H
#define WILD_H

#include <stdbool.h>
#include <string.h>

// DEBUG
#include <stdio.h>

/**
 * @brief character used for patterns
 */
#define WILD '+'

/**
 * @brief checks whether a string is a pattern
 * @param string is the string
 * @return true if it contains the character used for patters and false otherwise
 */
bool isWild(char *string);

/**
 * @brief checks whether a string fits a given pattern
 * @param pattern is the pattern
 * @param string is the string
 * @return true if it fits and false otherwise
 */
bool checkWild(char *pattern, char *string);

#endif