#include <stdio.h>
#include <stdlib.h>
#define MAX_BUF 128

enum Command {
    UNKNOWN,
    ENQUEUE,
    DEQUEUE,
    PRINTFRONT,
    PRINTREAR,
    CREATE
};

struct CommandLine {
    char buf[MAX_BUF];
    enum Command command;
    int argument;
};

struct Queue {
    int *array;
    int front;
    int rear;
    int size;
    int capacity;
};

struct Queue *CreateQueue(struct Queue *queue, int max) {
    queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->capacity = max;
    queue->array = (int *)malloc(sizeof(int));
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    return queue;
}

int IsEmpty(struct Queue *queue) {
    return queue->size == 0;
}
int IsFull(struct Queue *queue) {
    return queue->size == queue->capacity;
}
int Succ(int index, struct Queue *queue) {
    return ++index == queue->capacity ? 0 : index;
}

void PrintAll(struct Queue *queue) {
    int pos;
    if (IsEmpty(queue)) {
        printf("The queue is empty. \t");
    } else {
        for (int i = 0; i < queue->size; i++) {
            pos = i + queue->front < queue->capacity ? i + queue->front : i + queue->front - queue->capacity;
            printf("%d\t", queue->array[pos]);
        }
    }
    printf("f: %d, r: %d\n", queue->front, queue->rear);
}

struct Queue *Dequeue(struct Queue *queue) {
    if (IsEmpty(queue)) {
       printf("ERROR: The queue is empty.\n");
    } else {
       queue->size--;
       queue->front = Succ((queue->front)++, queue);
       printf("Dequeued:\t");
       PrintAll(queue);
    }
    return queue;
}

struct Queue *Enqueue(struct Queue *queue, int new) {
    if (IsFull(queue)) {
        printf("ERROR:The queue is Full.\n");
    } else {
        queue->size++;
        queue->array[queue->rear] = new;
        queue->rear = Succ((queue->rear)++, queue);
    }
    printf("Enqueued:\t");
    PrintAll(queue);
    return queue;
}

void PrintFront(struct Queue *queue) {
    printf("Front: %d\n", queue->array[queue->front]);
}

void PrintRear(struct Queue *queue) {
    printf("Rear: %d\n", queue->array[queue->rear]);
}

void FreeQueue(struct Queue *queue) {
    free(queue->array);
    free(queue);
}

void ParseCommandLine(struct CommandLine *commandline) {
    char command = commandline->buf[0];
    
    switch (command) {
        case 'n': 
            commandline->command = CREATE;
            sscanf(commandline->buf, "%*c %d", &commandline->argument);
            break;
        case 'e': 
            commandline->command = ENQUEUE;
            sscanf(commandline->buf, "%*c %d", &commandline->argument);
            break;
        case 'd': 
            commandline->command = DEQUEUE;
            break;
        case 'f': 
            commandline->command = PRINTFRONT;
            break;
        case 'r': 
            commandline->command = PRINTREAR;
            break;
        default:
            commandline->command = UNKNOWN;
    }
}

int main(int argc, const char *argv[]) {
    if (argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        if (!fp) {
            printf("file open error \n"); 
        }
        struct CommandLine commandline;
        struct Queue *queue;
        while (fgets(commandline.buf, sizeof(commandline.buf),fp)) {
            ParseCommandLine(&commandline);
            switch (commandline.command) {
                case CREATE:
                    queue = CreateQueue(queue, commandline.argument); break;
                case ENQUEUE:
                    queue = Enqueue(queue, commandline.argument);
                    break;
                case DEQUEUE: queue = Dequeue(queue); break;
                case PRINTFRONT: PrintFront(queue); break;
                case PRINTREAR: PrintRear(queue); break;
                default:
                    printf("Unknown command\n");
            }
        }
        FreeQueue(queue);
    } else {
        printf("Execute with an input text file.\n");
    } 
    return 0;
}
