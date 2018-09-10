//Postfix Evaluation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DATACHAR 100

char target_line[DATACHAR];

struct Stack {
    int* key;
    int top;
    int max_stack_size;
};

//스택을 초기화
void MakeEmpty(struct Stack* S) {
    S->top = -1;
    S->max_stack_size = 40;
    S->key = (int*)malloc(S->max_stack_size);
}

//스택이 비어있는지 확인
int IsStackEmpty(struct Stack* S) {
    return S->top == -1;
}

//Push하기, top을 기준으로 계속 쌓아올라가는 형태
void Push(int* digit, struct Stack* S) {
    S->top++;
    S->key[S->top] = *digit;
}

//Pop하기, top을 기준으로 위에서부터 하나씩 뻬서 operand에 담아주고 크기 줄임
void Pop(struct Stack* S, int* operand) {
    *operand = S->key[S->top];
    S->top--;
}

//계산 함수, 인자: 계산대상, 결과물을 담을 곳, 피연산자를 담아둘 스택
void PostfixEval(char* target_line, int* result, struct Stack* S) {
    int operand1, operand2 = 0;
    for (int i = 0; i < DATACHAR; i++) {
        //피연산자와 연산자 구분 및 처리
        //피연산자인 경우에는 스택에 Push
        if (isdigit(target_line[i])) {
            int target;
            //숫자가 한자리 정수인 경우 -'0'으로 변환 가능
            target = target_line[i] - '0';
            Push(&target, S);
            continue;
        }
        
        //마지막에 #를 마치면 스택에 있는 최종결과 출력
        if (target_line[i] == '#') {
            while(S->top != -1) {
                Pop(S, result);
            }
        }
        else {
        //연산자를 만나면 스택에서 2개의 피연산자를 pop하기
            Pop(S, &operand1);
            Pop(S, &operand2);
        //연산자로 계산을 해주고 결과값을 다시 스택에 Push 
            switch (target_line[i]) {
                case '*':
                    *result = operand2 * operand1;
                    break;
                case '%':
                    *result = operand2 % operand1;
                    break;
                case '+':
                    *result = operand2 + operand1;
                    break;
                case '-':
                    *result = operand2 - operand1;
                    break;
                case '/':
                    *result = operand2 / operand1;
                    break;
                default:
                    *result;
            }
            Push(result, S);
        }      
    }
}

int main(int argc, const char *argv[]) {
    if (argc == 2) {
        FILE* fp = fopen(argv[1], "r");
        if (fp) {
            int result;

            //스택을 만들고 초기화 설정
            struct Stack* S;
            S = malloc(sizeof(struct Stack));
            MakeEmpty(S);

            while(fgets(target_line, sizeof(target_line), fp)) {
                PostfixEval(target_line, &result, S);

                printf("converted postfix form : %s", target_line);
                printf("evaluation result : %d \n", result);
            }
        }
        else
            printf("input error!");
    }
    return 0;
}
