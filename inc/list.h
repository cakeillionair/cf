#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct ListNode ListNode;
struct ListNode {
    void *val;
    ListNode *next;
};

typedef struct List {
    int size;
    ListNode *start;
    ListNode *current;
    ListNode *end;
} List;

/**
 * @brief pushes a value onto a list
 * @param list is the pointer to the List struct
 * @param val is the pointer to the value
 * @return nothing
 */
#define push(list, val) listPrepend((list), (val))

/**
 * @brief sets the field "current" of a List struct to the start of the list
 * @param list is a pointer to the List struct
 */
#define toStart(list) ((list)->current = (list)->start)

/**
 * @brief checks whether the field "current" of a list is not NULL
 * @param list is a pointer to the List struct
 * @return true if "current" is not NULL and false otherwise
 */
#define hasAccess(list) ((list)->current != NULL)

/**
 * @brief advances the "current" pointer of a list
 * @param list is a pointer to the List struct
 */
#define next(list) ((list)->current = (list)->current->next)

/**
 * @brief equivalent to a for loop going through each element of a list
 * @param list is a pointer to the List struct
 */
#define foreach(list) for (toStart(list); hasAccess(list); next(list))

/**
 * @brief creates an empty list
 * @return a pointer to the list
 */
List *emptyList();

/**
 * @brief appends a value to a list
 * @param list is a pointer to the List struct
 * @param val is a pointer to the value
 * @return nothing
 */
void listAppend(List *list, void *val);

/**
 * @brief prepends a value to a list
 * @param list is a pointer to the List struct
 * @param val is a pointer to the value
 * @return nothing
 */
void listPrepend(List *list, void *val);

/**
 * @brief pops the first value of a list
 * @param list is a pointer to the List struct
 * @return a pointer to the value
 */
void *pop(List *list);

/**
 * @brief frees all elements of a list
 * @param list is a pointer of the List struct
 * @return nothing
 */
void freeList(List *list);

#endif