#include <stdio.h>
#include <stdlib.h>
#define MAX_ENROLLMENT 30

struct Node {
    char *student_id;
    char *student_name;
    struct Node *next;
};

struct Node *MakeNode(char *student_id, char *student_name) {
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->student_id = student_id;
    new->student_name = student_name;
    new->next = NULL;
    return new;
}

void MakeList(struct Node **init) {
    *init = MakeNode("000000", NULL);
}

int IsEmpty(struct Node *list) {
    return (list->next == NULL);
}

int IsLast(struct Node *node) {
    return (node->next == NULL);
}

int IdToInteger(char *student_id) {
    int transfered_id;
    transfered_id = 100000 * student_id[0] + 10000 * student_id[1] + 1000 * student_id[2] + 100 * student_id[3] + 10 * student_id[4] + student_id[5];
    return transfered_id;
}

struct Node *FindNode(struct Node *list, char *student_id) {
    struct Node *checked = list;    //list의 header에서부터 찾기 시작
    int integer_finding = IdToInteger(student_id);
    while ((checked != NULL) && (IdToInteger(checked->student_id) != integer_finding)) {
        checked = checked->next;
    }
    return checked;
}

struct Node *FindPrevNode(struct Node *list, char *student_id) {
    if (IsEmpty(list)) {
        return NULL;
    }
    else {
        struct Node *checked = list;
        int integer_finding = IdToInteger(student_id);
        while (IdToInteger(checked->next->student_id) != integer_finding) {
            checked = checked->next;
            if (IsLast(checked)) 
                return NULL;
        }
        return checked;
    }
}

void PrintList(struct Node *list) {
    struct Node *printed = list->next;
    while (printed!=NULL) {
        printf("%s  %s      ", printed->student_id, printed->student_name);
        printed = printed->next;
    }
    printf("\n");
}

void PrintNode(struct Node *list, char *student_id) {
    struct Node *printed = FindNode(list, student_id);
    if (printed == NULL) {
        printf("There is no element having student ID %s", student_id);
    }
    else {
        printf("%s\n", printed->student_name);
    }
}

void Insert(struct Node *list, char *student_id, char *student_name) {
    struct Node *prev_of_inserted = list;    //list의 header에서부터 inserted될 node의 prev 찾기 시작
    int integer_prev = IdToInteger(prev_of_inserted->student_id);
    int integer_inserted = IdToInteger(student_id);
    int integer_next = 0;   //insert될 node의 next node student_id의 integer 변환값을 저장할 변수
    
    if (IsEmpty(list)) {   //line 50~62 : prev_of_inserted를 찾는 code
        //list에 어떠한 node도 없는 경우, list의 header의 next에 insert
    }
    else {
        integer_next = IdToInteger(prev_of_inserted->next->student_id);
        while (integer_inserted > integer_next) {
            prev_of_inserted = prev_of_inserted->next;
            if (IsLast(prev_of_inserted))
                break;
            integer_next = IdToInteger(prev_of_inserted->next->student_id);
        }
    }

    if (integer_inserted == integer_next) {     //insert되는 학생의 id가 list에 존재하는 경우 error message
        printf("There already is an element with key %s. Insertion failed.\n", student_id);
    }
    else {      //찾은 prev_of_inserted의 next node에 새로운 node를 추가
        struct Node *new = MakeNode(student_id, student_name);
        struct Node *temp;    //insert되는 node의 next node를 저장하기 위한 변수        
        temp = prev_of_inserted->next;
        prev_of_inserted->next = new;
        new->next = temp;

        printf("Insertion success : %s\n", student_id);        
        printf("Current List> ");
        PrintList(list);
    }
}

void Delete(struct Node *list, char *student_id) {
    struct Node *prev_deleted = FindPrevNode(list, student_id);
    if (!prev_deleted) {
        printf("Deletion failed : element %s is not in the list\n", student_id);
    }
    else {
        struct Node *temp;
        temp = prev_deleted->next;    //temp에 delete 할 node를 할당
        prev_deleted->next = temp->next;
        free(temp);
        
        printf("Deletion success : %s\n", student_id);
        printf("Current List> ");
        PrintList(list);
    }
}

void ChooseOperations(struct Node *list, char *buffer) {
    char command;
    command = buffer[0];

    switch (command) {
        case 'i': {
            char *student_id_m = (char *)malloc(sizeof(char)*6);
            char *student_name_m = (char *)malloc(sizeof(char)*30);
            sscanf(buffer, "%c %s %[^\n]s", &command, student_id_m, student_name_m);
            Insert(list, student_id_m, student_name_m);
            break;
        }
        case 'd': {
            char student_id[5];
            sscanf(buffer, "%c %s", &command, student_id);
            Delete(list, student_id);
            break;
        }
        case 'f': {
            char student_id[5];
            sscanf(buffer, "%c %s", &command, student_id);
            PrintNode(list, student_id);
            break;
        }
        case 'p': {
            PrintList(list);
            break;
        }
        default:
            printf("Wrong instruction.\n");
    }
}

int main(int argc, const char *argv[]) {
    struct Node *student_list;
    MakeList(&student_list);
    char buffer[50];
    
    FILE *fp = fopen(argv[1],"r");
    while (1) {
        if (fgets(buffer, sizeof(buffer), fp) == NULL)
            break;      
        ChooseOperations(student_list, buffer);
    }
    fclose(fp);

    return 0;
}
