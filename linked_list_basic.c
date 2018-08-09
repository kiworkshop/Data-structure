#include <stdio.h>
#include <stdlib.h>

struct Node {
    int element;
    struct Node *next;
};

struct Node *MakeNode(int element) {
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->element = element;
    new->next = NULL;
    return new;
}

void MakeNewList(struct Node **initial) {
    *initial = MakeNode(-1);     //Make element of header node -1
}

struct Node *FindNode(struct Node *list, int key_element) {
    struct Node *checked = list;
    while ((checked != NULL) && (checked->element != key_element)) {
        checked = checked->next;
    }
    return checked;
}

struct Node *FindPrevNode(struct Node *list, int key_element) {      
    struct Node *checked = list;
    while ((checked->next != NULL) && (checked->next->element != key_element)) {
        checked = checked->next;
    }

    if (checked->next == NULL) {
        checked = NULL;    //checked의 next가 NULL인 경우 key_element가 list 내에 존재하지 않는다.
    }
    return checked;
}

void Insert(struct Node *list, int prev_node_element, int element) {
    struct Node *prev = FindNode(list, prev_node_element);
    if (prev) {
        struct Node *new = MakeNode(element);
        new->next = prev->next;
        prev->next = new;
    }
    else {
        printf("Insertion (%d) Failed : element %d is not in the list \n", element, prev_node_element);
    }
}

void Delete(struct Node *list, int key_element) {
    struct Node *prev = FindPrevNode(list, key_element);    //Delete 하려는 node는 prev->next이다. 
    struct Node *temp;
    if (!prev) {
        printf("Deletion failed : element %d is not in the list.\n", key_element);
    }
    else if (prev->next == list) {    //Delete 하려는 element가 header인 경우, error message
        printf("Deletion failed : Could not delete header.\n");
    }
    else {
        struct Node *deleted = prev->next;
        temp = deleted;
        prev->next = deleted->next;
        free(temp);
    }
}

int IsEmpty(struct Node *list) {
    return (list->next == NULL);
}

void PrintList(struct Node *list) {
    struct Node *printed = list->next;
    int index = 1;
    while (printed != NULL) {
        printf("[%d] key : %d    ", index++, printed->element);
        printed = printed->next;
    }
    printf("\n");

    if (IsEmpty(list)) {
        printf("List is empty\n");
    }
}

void ExecuteBufferLine(struct Node *list, char *buffer) {
    char command;
    int new_element;
    int key_element;
    command = buffer[0];

    switch (command) {
        case 'i':
            sscanf(buffer, "%c %d %d", &command, &new_element, &key_element);
            Insert(list, key_element, new_element);
            break;
        case 'd':
            sscanf(buffer, "%c %d", &command, &key_element);
            Delete(list, key_element);
            break;
        case 'f':
            sscanf(buffer, "%c %d", &command, &key_element);
            struct Node *p = FindPrevNode(list, key_element);
            if (p == list)
                printf("Key of the previous node of %d is header\n", key_element);
            else if (p == NULL)
                printf("Could not find %d in the list\n", key_element);
            else
                printf("Key of the previous node of %d is %d\n", key_element, p->element);
            break;
        case 'p':
            PrintList(list);
            break;
        default:
            printf("Wrong instruction.\n");
    }
}

int main(int argc, const char *argv[]) {
    struct Node *list;
    char buffer[10];
    MakeNewList(&list);
    
    FILE *fp = fopen(argv[1], "r");
    while (1) {
        if (fgets(buffer, sizeof(buffer), fp) == NULL)
            break;
        ExecuteBufferLine(list, buffer);
    }
    fclose(fp);

    return 0;
}
