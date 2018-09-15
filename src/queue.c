#include "queue.h"
#include "common.h"
#include <stdlib.h>

static struct Bundle *NewBundle() {
    struct Bundle *bundle = (struct Bundle *)malloc(sizeof(struct Bundle));
    bundle->head = 0;
    bundle->tail = 0;
    bundle->next = NULL;

    return bundle;
}

static void FreeBundle(struct Bundle *bundle) {
    free(bundle);
}

struct Queue *Instance() {
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->head = NewBundle();
    queue->tail = queue->head;

    return queue;
}

void Enqueue(struct Queue *queue, void *element) {
    struct Bundle *tail_bundle = queue->tail;
    if (tail_bundle->tail != BUNDLE_SIZE) {
        tail_bundle->array[tail_bundle->tail++] = element;
        return;
    }

    queue->tail = NewBundle();
    tail_bundle->next = queue->tail;
    tail_bundle = tail_bundle->next;
    tail_bundle->array[tail_bundle->tail++] = element;
}

void *Dequeue(struct Queue *queue) {
    struct Bundle *head_bundle = queue->head;

    void *data = head_bundle->array[head_bundle->head++];
    if (head_bundle->head == BUNDLE_SIZE) {
        if (queue->head == queue->tail) {
            head_bundle->head = 0;
            head_bundle->tail = 0;
        } else {
            queue->head = head_bundle->next;
            FreeBundle(head_bundle);
        }
    }
    return data;
}

int Empty(struct Queue *queue) {
    return queue->head == queue->tail && queue->head->head == queue->head->tail;
}

void ForEach(struct Queue *queue, void (*Function)(void *data)) {
    int i;
    struct Bundle *current = queue->head;

    while (current) {
        for (i = current->head; i < current->tail; i++) {
            Function(current->array[i]);
        }
        current = current->next;
    }
}

void Free(struct Queue *queue) {
    struct Bundle *current = queue->head;
    struct Bundle *next;

    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
}

void FreeWithItems(struct Queue *queue) {
    int i;
    struct Bundle *current = queue->head;
    struct Bundle *next;

    while (current) {
        next = current->next;
        for (i = current->head; i < current->tail; i++) {
            free(current->array[i]);
        }
        free(current);
        current = next;
    }
}

const struct QueueOp queue_op = {
    .Instance = Instance,
    .Enqueue = Enqueue,
    .Dequeue = Dequeue,
    .Empty = Empty,
    .ForEach = ForEach,
    .Free = Free,
    .FreeWithItems = FreeWithItems,
};