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

int main(int argc, const char *argv[]) {
    return 0;
}
