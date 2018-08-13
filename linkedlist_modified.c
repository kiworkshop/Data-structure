//Linked list
#include <stdio.h>
#include <stdlib.h>

#define MIN -1

struct Node {
    int item;
    struct Node* next;
};

struct Node* CreateNode(int target);
int IsEmpty(struct Node* list);
int IsLast(struct Node* current);
void DeleteNode(int target, struct Node* list);
struct Node* FindPrevious(int target, struct Node* list);
struct Node* Find(int target, struct Node* list);
void Insert(int target, int position, struct Node* list);
void FindPrint(int target, struct Node* list);
void ListPrint(struct Node* list);
void DeleteList(struct Node* list);

int main(){
    char command;
    int target, position;
    FILE *fp = fopen("lab2_input.txt", "r");

    if (fp == NULL) {    
        printf("Input Error");
        return 1;
    }

    struct Node* list = CreateNode(0);

    while (!feof(fp)) {
        fscanf(fp, "%c %d %d", &command, &target, &position);
        switch (command) {
            case'i': {
                Insert(target, position, list);
                break;                
            }
            case'd': { 
                DeleteNode(target, list);
                break;
            }            
            case'f': {
                FindPrint(target, list);
                break;
            }
            case'p': {
                ListPrint(list);
                break;
            }
            default:
                continue;
        }
    }
    DeleteList(list);
    fclose(fp);
    return 0;
}

struct Node* CreateNode(int target) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->item = target;
    new_node->next = NULL;
    return new_node;
}

int IsEmpty(struct Node* list) {
    return list->next == NULL;
}

int IsLast(struct Node* current) {
    return current->next == NULL;
}

void DeleteNode(int target, struct Node* list) {
    struct Node *previous, *tmp_cell;
    previous = FindPrevious(target, list);    
    if (previous->next == NULL) {
        printf("Deletion failed : element %d is not int the list \n", target);
    }   
    else {
        if (!IsLast(previous)) {
            tmp_cell = previous->next;
            previous->next = tmp_cell->next;
            free(tmp_cell);
        }
    }
}

struct Node* FindPrevious(int target, struct Node* list) {
    struct Node* previous = list;
    while (previous->next && previous->next->item != target)
        previous = previous->next;    
    return previous;
}

struct Node* Find(int target, struct Node* list) {
    struct Node* current = list->next;
    while (current != NULL && current->item != target)
        current = current->next;
    return current;
}

void Insert(int target, int position, struct Node* list) {
    struct Node *after_target, *tmp_cell;
    tmp_cell = CreateNode(target);
    if (position == MIN) {
        tmp_cell->next = list->next;
        list->next = tmp_cell;
        return;
    }
    else {
        after_target = Find(position, list);
        if (after_target == NULL) {
            printf("Insertion(%d) Failed : element %d is not in the list \n", target, position);
            return;
        } 
        else {
            tmp_cell->next = after_target->next;
            after_target->next = tmp_cell;
        }
    }     
}
void FindPrint(int target, struct Node* list) {
    struct Node* previous;
    previous = FindPrevious(target, list);
    if (previous->next == NULL) {
        printf("Could not find %d in the list \n", target);
        return;
    } 
    else {
        if (previous->item == 0) {
            printf("Key of the previous node of %d is header.\n", target);
        } 
        else {
            printf("Key of the previous node of %d is %d.\n", target, previous->item);
        } 
    } 
}

void ListPrint(struct Node* list) {
    struct Node* current = list->next;
    while (current != NULL) {
        printf("Key: %d ", current->item);
        current = current->next;
    }    
}

void DeleteList(struct Node* list) {
    struct Node *deleting, *tmp_cell;
    if (!IsEmpty(list)) {
        deleting = list;
        tmp_cell = list->next;
        while (tmp_cell != NULL) {
            free(deleting);
            deleting = tmp_cell;
            tmp_cell = tmp_cell->next;
        }
        free(deleting); //마지막에 남은 deleting노드 free
    }
}

