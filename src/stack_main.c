#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void PrintFunction(void *data) { printf("%d ,", *(int *)data); }

int main() {
    struct StackOp op = stack_op;

    int i;
    int element1 = 1;
    int element2 = 2;
    int element3 = 3;
    int element4 = 4;

    int *array = (int *)malloc(sizeof(int) * 1000);

    struct Stack *stack = op.Instance();

    printf("isEmpty: %d\n", op.Empty(stack));

    // result: isEmpty: 1

    op.Push(stack, &(element1));
    op.Push(stack, &(element2));
    op.Push(stack, &(element3));
    void *data = op.Pop(stack);
    printf("top: %d\n", *(int *)data);

    // result: top: 3

    op.Push(stack, &(element4));
    op.ForEach(stack, PrintFunction);
    printf("\n");

    // result: 1, 2, 4

    printf("isEmpty: %d\n", op.Empty(stack));

    // result: isEmpty: 0

    for (i = 0; i < 1000; i++) {
        op.Push(stack, &array[i]);
    }

    for (i = 0; i < 1000; i++) {
        op.Pop(stack);
    }

    printf("top: %d\n", *(int *)op.Pop(stack));

    // result: top: 4

    op.Free(stack);

    return 0;
}