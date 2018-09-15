#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void PrintFunction(void* data) {
    printf("%d ,", *(int*)data);
}

#define ITERATION 512

int main() {

    struct QueueOp op = queue_op;

    int i;

    int element1 = 1;
    int element2 = 2;

    int *array = (int*)malloc(sizeof(int)*ITERATION);
    for (i = 0; i < ITERATION; i++) {
        array[i] = i;
    }

    struct Queue *queue = op.Instance();

    printf("isEmpty: %d\n", op.Empty(queue));

    // result: isEmpty: 1

    op.Enqueue(queue, &element1);
    op.Enqueue(queue, &element2);

    printf("isEmpty: %d\n", op.Empty(queue));

    // result: isEmpty: 0

    printf("dequeue: %d\n", *(int*)op.Dequeue(queue));
    printf("dequeue: %d\n", *(int*)op.Dequeue(queue));

    // result:
    //  dequeue: 1
    //  dequeue: 2

    for (i = 0; i < ITERATION; i++) {
        op.Enqueue(queue, &array[i]);
    }

    op.ForEach(queue, PrintFunction);
    printf("\n");

    // result: 0, 1, 2, 3, 4, ... 511

    for (i = 0; i < ITERATION; i++) {
        printf("%d ,", *(int*)op.Dequeue(queue));
    }
    printf("\n");

    // result: 0, 1, 2, 3, 4, ... 511

    printf("isEmpty: %d\n", op.Empty(queue));

    // result: isEmpty: 1

    op.Free(queue);

    return 0;
}