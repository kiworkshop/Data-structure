#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

struct LinkedList* Instance() {
    struct LinkedList *linkedList = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    linkedList->head = (struct Node*) malloc(sizeof(struct Node));
    linkedList->head->next = NULL;

    return linkedList;
}

void Append(struct LinkedList *linkedList, void *element) {

}
void Delete(struct LinkedList *linkedList, int index) {

}
void* Find(struct LinkedList *linkedList, int index) {
    return NULL;
}
void Print(struct LinkedList *linkedList) {

}

void Free(struct LinkedList *linkedList) {
    struct Node *current = linkedList->head;
    struct Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(linkedList);
}

const struct LinkedListOp linkedListOp = {
    .Instance = Instance,
    .Append = Append,
    .Delete = Delete,
    .Find = Find,
    .Print = Print,
    .Free = Free,
};