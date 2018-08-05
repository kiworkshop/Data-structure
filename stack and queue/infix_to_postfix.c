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

void Push(struct Stack *stack, char element) {
    if (!IsFull(stack)) {
        stack->key[++(stack->top)] = element;
    }
}

char Pop(struct Stack *stack) {
    if (!IsEmpty(stack)) { 
        return stack->key[stack->top--];
    }
}

char Top(struct Stack *stack) {
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

void Printout(char *converted) {
    printf("\nconverted postfix form: ");
    for (int i = 0; i < 64; i++) {
        printf("%c", converted[i]);
    }
    printf("\n");
}

// Operand is 1 ~ 9 single digit integer.
int IsOperand(char letter) {
    return letter > 48 && letter < 58;
} 

int Priority(char operator) {
    switch (operator) {
        case '+': return 1; break;
        case '-': return 1; break;
        case '*': return 2; break;
        case '/': return 2; break;
        case '%': return 2; break;
        case '(': return 3; break;
        case ')': return 3; break;
        default: return 0; break;
    }
}

void ConvertToPostfix(char letter, char *output, int *count, struct Stack *stack){
    if (IsOperand(letter)) {
        output[*count] = letter;
    } else {
        char top = Top(stack);
        if (top != '(') {
            while (!IsEmpty(stack) && Priority(letter) <= Priority(top)) {
                if (Top(stack) == '(' || Top(stack) == ')') {
                    Pop(stack);
                } else {
                    output[*count] = Pop(stack);
                    *count = *count + 1;
                }
            }
        }
        Push(stack, letter);
    }
}

int main(int argc, const char *argv[]) {
    if (argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        char buf;
        char *output = (char *) malloc(sizeof(char) * 64);
        int count = 0;
        struct Stack *stack = CreateStack(10);
        printf("Original infix form: ");
        if (fp) {
            while (buf != '#') {
                buf = fgetc(fp);
                printf("%c", buf);
                ConvertToPostfix(buf, output, &count, stack);
                count++;
            }
            Printout(output);
            FreeStack(stack);
            free(output);
        } else {
            printf("Cannot open file\n");
        }
    } else {
       printf("Wrong argument\n");
    }
    return 0;
}
