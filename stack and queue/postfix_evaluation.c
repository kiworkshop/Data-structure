#include <stdio.h>
#include <stdlib.h>

struct Stack {
    char *key;
    int top;
    int capacity;
};

struct Stack *CreateStack(int capacity) {
    struct Stack *new = (struct Stack *) malloc(sizeof(struct Stack));
    new->capacity = capacity;
    new->top = -1;
    new->key = (char *) malloc(sizeof(char) * new->capacity);
    return new;
}

int IsFull(struct Stack *stack) {
    int top = stack->top;
    return ++top == stack->capacity;
}

int IsEmpty(struct Stack *stack) {
    return stack->top == -1;
}

void Push(struct Stack *stack, int element) { 
    if (!IsFull(stack)) {
        stack->key[++stack->top] = element;
    }
}

int Pop(struct Stack *stack) {
    if (!IsEmpty(stack)) { 
        return stack->key[stack->top--];
    }
}

int Top(struct Stack *stack) {
    if (!IsEmpty(stack)) {
        return stack->key[stack->top];
    }
}

void PrintStack(struct Stack *stack) {
    if (!IsEmpty(stack)) {
        for (int i = 0; i < stack->top; i++) {
            printf("%d", stack->key[i]);
        }
    }
}
void FreeStack(struct Stack *stack) {
    free(stack->key);
    free(stack);
}

int CalculateTwoOperands(struct Stack *stack, char operator, int *result) {
    int operand1 = Pop(stack);
    int operand2 = Pop(stack);

    switch (operator) {
        case '+': return operand2 + operand1; break;
        case '-': return operand2 - operand1; break;
        case '*': return operand2 * operand1; break;
        case '/': return operand2 / operand1; break;
        case '%': return operand2 % operand1; break;
    }
}

int CharToInt(char letter) {
    return letter - 48;
}

int IsOperand(char letter) {
    return letter > 48 && letter < 58;
}

void Evaluate(struct Stack *stack, char letter) {
    int result = 0;
    if (IsOperand(letter)) {
        Push(stack, CharToInt(letter));
    } else {
        result = CalculateTwoOperands(stack, letter, &result);
        Push(stack, result);
    }
}

int main(int argc, const char *argv[]) {
    if (argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
            printf("File Open error. \n");
            return 0;
        }
        char buf;
        struct Stack *stack = CreateStack(10);
        printf("Converted postfix form: ");
        while (1) {
            buf = fgetc(fp);
            if (buf == '#') {
                break;
            }
            printf("%c",buf);
            Evaluate(stack, buf);
        }
        printf("\nevaluation result:%d\n", Top(stack));
        FreeStack(stack);   
    } else {
       printf("Wrong argument\n");
    }
    return 0;
}
