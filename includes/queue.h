#ifndef __QUEUE_H__
#define __QUEUE_H__

#define BUNDLE_SIZE 32

struct Bundle {
    void *array[BUNDLE_SIZE];
    int head;
    int tail;
    struct Bundle *next;
};

struct Queue {
    struct Bundle *head;
    struct Bundle *tail;
};

struct QueueOp {
    struct Queue *(*Instance)();
    void (*Enqueue)(struct Queue *queue, void *element);
    void *(*Dequeue)(struct Queue *queue);
    int (*Empty)(struct Queue *queue);
    void (*ForEach)(struct Queue *queue, void (*Function)(void *data));
    void (*Free)(struct Queue *queue);
    void (*FreeWithItems)(struct Queue *queue);
};

extern const struct QueueOp queue_op;

#endif  // __QUEUE_H__