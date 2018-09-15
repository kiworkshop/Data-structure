#ifndef __STACK_H__
#define __STACK_H__

#define INIT_STACK_SIZE 16

struct Stack {
    void **array;
    int length;
    int array_size;
};

struct StackOp {
    struct Stack *(*Instance)();
    void (*Push)(struct Stack *stack, void *element);
    void *(*Pop)(struct Stack *stack);
    int (*Empty)(struct Stack *stack);
    void (*ForEach)(struct Stack *stack, void (*Function)(void *data));
    void (*Free)(struct Stack *stack);
    void (*FreeWithItems)(struct Stack *stack);
};

extern const struct StackOp stack_op;

#endif  // __STACK_H__