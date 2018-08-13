#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

static struct Node *NewNode(void *data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;

    return node;
}

struct LinkedList *Instance() {
    struct LinkedList *linked_list =
        (struct LinkedList *)malloc(sizeof(struct LinkedList));
    linked_list->head = NewNode(NULL);
    linked_list->tail = linked_list->head;

    return linked_list;
}

void Append(struct LinkedList *linked_list, void *element) {
    struct Node *node = NewNode(element);
    linked_list->tail->next = node;
    linked_list->tail = node;
}

void Prepend(struct LinkedList *linked_list, void *element) {
    struct Node *node = NewNode(element);
    node->next = linked_list->head->next;
    linked_list->head->next = node;
}

void *Delete(struct LinkedList *linked_list, void *element,
            int (*Equals)(void *compared, void *item)) {
    struct Node *prev = linked_list->head;
    struct Node *current = prev->next;
    void *data;

    while (current) {
        if (Equals(element, current->data)) {
            prev->next = current->next;
            data = current->data;
            free(current);
            return data;
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}

void *Find(struct LinkedList *linked_list, void *element,
           int (*Equals)(void* compared, void* item)) {
    struct Node *current = linked_list->head->next;
    while (current) {
        if (Equals(element, current->data))
            return current->data;
        current = current->next;
    }
    return NULL;
}

void ForEach(struct LinkedList *linked_list, void (*Function)(void *data)) {
    struct Node *current = linked_list->head->next;
    while (current) {
        Function(current->data);
        current = current->next;
    }
}

void Free(struct LinkedList *linked_list) {
    struct Node *current = linked_list->head;
    struct Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(linked_list);
}

void FreeWithItems(struct LinkedList *linked_list) {
    struct Node *current = linked_list->head;
    struct Node *next;

    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    free(linked_list);
}

const struct LinkedListOp linked_list_op = {
    .Instance = Instance,
    .Append = Append,
    .Prepend = Prepend,
    .Delete = Delete,
    .Find = Find,
    .ForEach = ForEach,
    .Free = Free,
    .FreeWithItems = FreeWithItems,
};