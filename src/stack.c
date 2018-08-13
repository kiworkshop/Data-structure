#include "stack.h"
#include <stdlib.h>

struct Stack *Instance() {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack *));
    stack->array = (void **)malloc(sizeof(void *) * INIT_STACK_SIZE);
    stack->length = 0;
    stack->array_size = INIT_STACK_SIZE;

    return stack;
}

void Push(struct Stack *stack, void *element) {
    if (stack->length == stack->array_size) {
        stack->array = (void **)realloc(
            stack->array, sizeof(void *) * (stack->array_size << 1));
        stack->array_size = stack->array_size << 1;
    }

    stack->array[stack->length++] = element;
}

void *Pop(struct Stack *stack) {
    if (stack->length > INIT_STACK_SIZE &&
        stack->length < (stack->array_size >> 2)) {
        stack->array = (void **)realloc(
            stack->array, sizeof(void *) * (stack->array_size >> 1));
        stack->array_size = stack->array_size >> 1;
    }
    return stack->array[--stack->length];
}

int Empty(struct Stack *stack) { return stack->length == 0; }

void ForEach(struct Stack *stack, void (*Function)(void *data)) {
    int i;
    for (i = 0; i < stack->length; i++) {
        Function(stack->array[i]);
    }
}

void Free(struct Stack *stack) {
    free(stack->array);
    free(stack);
}

void FreeWithItems(struct Stack *stack) {
    int i;
    for (i = 0; i < stack->length; i++) {
        free(stack->array[i]);
    }
    Free(stack);
}

const struct StackOp stack_op = {
    .Instance = Instance,
    .Push = Push,
    .Pop = Pop,
    .Empty = Empty,
    .ForEach = ForEach,
    .Free = Free,
    .FreeWithItems = FreeWithItems,
};
