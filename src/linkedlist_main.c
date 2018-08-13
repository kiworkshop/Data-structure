#include <stdio.h>
#include "common.h"
#include "linkedlist.h"

void PrintFunction(void *data) { printf("%d, ", *((int *)data)); }

int Equals(void *target, void *source) { return *((int *)target) == *((int *)source); }

int main(int argc, char **argv) {
    struct LinkedListOp op = linked_list_op;
    struct LinkedList *linked_list;

    int element1 = 1;
    int element2 = 2;
    int element3 = 3;
    int element4 = 4;

    int same_as_e2 = 2;

    linked_list = op.Instance();
    op.Append(linked_list, &(element1));
    op.Append(linked_list, &(element2));
    op.Append(linked_list, &(element3));
    op.ForEach(linked_list, PrintFunction);
    printf("\n");

    // result: 1, 2, 3,

    int *data = (int *)op.Find(linked_list, &element1, Equals);
    printf("Found Data: %d\n", *data);

    // result: Found Data: 1

    op.Delete(linked_list, &(same_as_e2), Equals);
    op.Prepend(linked_list, &(element4));
    op.ForEach(linked_list, PrintFunction);
    printf("\n");

    // result: 4, 1, 3

    op.Free(linked_list);

    return 0;
}