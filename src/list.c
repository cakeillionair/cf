#include "list.h"

List *emptyList() {
    List *list = malloc(sizeof(List));
    list->size = 0;
    list->start = NULL;
    list->current = NULL;
    list->end = NULL;
    return list;
}

void listAppend(List *list, void *val) {
    ListNode *tmp = malloc(sizeof(ListNode));

    tmp->val = val;
    tmp->next = NULL;

    if (list->end == NULL) {
        list->start = tmp;
        list->end = list->start;
    } else {
        list->end->next = tmp;
        list->end = tmp;
    }

    list->size++;
}

void listPrepend(List *list, void *val) {
    ListNode *tmp = malloc(sizeof(ListNode));

    tmp->val = val;
    tmp->next = NULL;

    if (list->start == NULL) {
        list->start = tmp;
        list->end = tmp;
    } else {
        tmp->next = list->start;
        list->start = tmp;
    }

    list->size++;
}

void *pop(List *list) {
    if (list == NULL) return NULL;
    if (list->start == NULL) return NULL;
    
    ListNode *tmp = list->start;
    if (tmp == list->current) list->current = NULL;
    list->start = tmp->next;
    list->size--;
    
    void *val = tmp->val;
    free(tmp);

    return val;
}

void freeList(List *list) {
    ListNode *tmp;

    while (list->start != NULL) {
        tmp = list->start;
        list->start = tmp->next;
        free(tmp);
    }

    list->current = NULL;
    list->end = NULL;
    list->size = 0;
}