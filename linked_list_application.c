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

int main(int argc, const char *argv[]) {
    return 0;
}
