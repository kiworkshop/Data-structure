//infix to postfix

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DATACHAR 100
#define MAX 100

char target_line[DATACHAR];

struct Stack {
    char* key;
    int top;
    int max_stack_size;
};

void MakeEmpty(struct Stack* stack) {
    stack->top = -1;
    stack->max_stack_size = MAX;
    stack->key =(char*)malloc(stack->max_stack_size);
}

int IsStackEmpty(struct Stack* stack) {
    return stack->top == -1;
}

//우선순위 정하기
int Priority(char operator) {
    switch (operator) {
        case '(': 
        case ')': 
            return 3;         
            break;
        case '*': 
        case '/': 
        case '%':
            return 2;
            break;
        case '+': 
        case '-':
            return 1;
            break;
        default:
            return -1;
    }
}

void Push(char word, struct Stack* stack) {
    stack->top++;
    stack->key[stack->top] = word;
}

void Pop(struct Stack* stack, char* converted_line) {
    if (stack->key[stack->top] == '(') {
        stack->top--;
    }
    else {
        strncat(converted_line, &stack->key[stack->top], 1);
        stack->top--;
    }
}

void InfixToPostfix(char* target_line, char* converted_line, struct Stack* stack) {
    for (int i = 0; i < DATACHAR; i++) {
        //피연산자와 연산자 구분 및 처리
        if (isdigit(target_line[i])) {
            strncat(converted_line, &target_line[i], 1);
            continue;
        }
        
        if (target_line[i] == '#') {
            while (stack->top != -1) {
                Pop(stack, converted_line);
            }
            continue;
        }

        if (stack->key[stack->top] == '(') {
            Push(target_line[i], stack);
            continue;
        }

        if (target_line[i] == ')') {
            while(stack->key[stack->top] != '(') {
                Pop(stack, converted_line);
            }
            Pop(stack,converted_line);
            continue;
        }

        if (Priority(target_line[i] > Priority(stack->key[stack->top]))) {
            Push(target_line[i], stack);
        }
        else {
            //스택의 탑에 있는 문자 우선순위가 같거나 낮은 연산자를 만나면 팝
            Pop(stack, converted_line);
            Push(target_line[i], stack);
        }
    }
}

int main(int argc, const char* argv[]) {
    if (argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        if (fp) {
            char converted_line[DATACHAR];
            
            //스택만들고 초기화 설정
            struct Stack* stack;
            stack = (struct Stack*)malloc(sizeof(struct Stack));
            MakeEmpty(stack);

            while (fgets(target_line, sizeof(target_line), fp)) {
                InfixToPostfix(target_line, converted_line, stack);
                printf("original infix form : %s", target_line);
                printf("converted postfix form : %s", converted_line);
            }
        } 
        else {
            return EXIT_FAILURE;
        }
    }
   return 0;
}

