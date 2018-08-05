//infix to postfix

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DATACHAR 100

char target_line[DATACHAR];

struct Stack{
    char* key;
    int top;
    int max_stack_size;
};

void MakeEmpty(struct Stack* S) {
    S->top = -1;
    S->max_stack_size = 40;
    S->key =(char*)malloc(S->max_stack_size);
}

int IsStackEmpty(struct Stack* S) {
    return S->top == -1;
}

//우선순위 정하기
int Priority(char operator){
    switch (operator) {
      case '(': case')': 
          return 3;         
          break;
      case '*': case'/': case'%':
          return 2;
          break;
      case '+': case'-':
          return 1;
          break;
      default:
          return -1;
    }
}

void Push(char word, struct Stack* S) {
    S->top = S->top + 1;
    S->key[S->top] = word;
}

void Pop(struct Stack* S, char* converted_line) {
    if (S->key[S->top] == '(') {
        S->top--;
    }
    else {
        strncat(converted_line, &S->key[S->top], 1);
        S->top--;
    }
}

      
void InfixToPostfix(char* target_line, char* converted_line, struct Stack* S){
    for (int i = 0; i < DATACHAR; i++) {
        
        //피연산자와 연산자 구분 및 처리
        if (isdigit(target_line[i])) {
            strncat(converted_line, &target_line[i], 1);
        }
        else {
            int p = Priority(target_line[i]);
            if (target_line[i] == '#') {
                while (S->top != -1) { 
                    Pop(S, converted_line);
                }
            }
            else if (S->key[S->top] == '(') {
                Push(target_line[i], S);
            }
            else if (target_line[i] == ')') {
                while(S->key[S->top] != '(') {
                    Pop(S, converted_line);
                }
                Pop(S,converted_line);
            }
            else {
                //스택의 탑에 있는 문자 우선순위가 들어오는 문자의 우선순위보다 낮은 경우, 푸쉬
                if (p > Priority(S->key[S->top])) {
                    //test
                    //printf("들어갈놈%c: %d, 스택안에 있는놈%c: %d\n",targetLine[i],p,S->key[S->top],Priority(S->key[S->top]));
                    Push(target_line[i], S);
                }
                else {
                    //스택의 탑에 있는 문자 우선순위가 같거나 낮은 연산자를 만나면 팝
                    Pop(S, converted_line);
                    Push(target_line[i], S);
                }
            }
        }
    }
}

int main(int argc, const char* argv[]) {
    if (argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        if (fp) {
            char converted_line[DATACHAR];
            
            //스택만들고 초기화 설정
            struct Stack* S;
            S = malloc(sizeof(struct Stack));
            MakeEmpty(S);

            while (fgets(target_line, sizeof(target_line), fp)) {
                InfixToPostfix(target_line, converted_line, S);

                printf("original infix form : %s", target_line);
                printf("converted postfix form : %s", converted_line);
            }
        } 
        else {
            printf("input error!");
        }
    }
   return 0;
}

