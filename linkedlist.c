//Linked list
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* ListPointer;

struct Node {
    int target;
    ListPointer next;
};

ListPointer CreateNode(int target);
int IsEmpty(ListPointer list);
int IsLast(ListPointer current);
void DeleteNode(int target, ListPointer list);
ListPointer FindPrevious(int target, ListPointer list);
ListPointer Find(int target, ListPointer list);
void Insert(int target, int position, ListPointer list);
void DeleteList(ListPointer list);

int main(){
    char command;
    int target, position;
    FILE *fp = fopen("lab2_input.txt", "r");

    if (fp == NULL) {    
        printf("Input Error");
        return 1;
    }

    ListPointer list = CreateNode(0);

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
                ListPointer previous;
                previous = FindPrevious(target, list);
                if (previous->next == NULL) {
                    printf("Could not find %d in the list \n", target);
                } 
                else {
                    if (previous->target == 0) {
                        printf("Key of the previous node of %d is header.\n", target);
                    } 
                    else {
                        printf("Key of the previous node of %d is %d.\n", target, previous->target);
                    } 
                } 
                break;
            }
            case'p': {
                ListPointer current = list->next;
                while (current != NULL) {
                    printf("Key: %d ", current->target);
                    current = current->next;
                }
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

ListPointer CreateNode(int target) {
    ListPointer new_node = malloc(sizeof(struct Node));
    new_node->target = target;
    new_node->next = NULL;
    return new_node;
}

int IsEmpty(ListPointer list) {
    return list->next == NULL;
}

int IsLast(ListPointer current) {
    return current->next == NULL;
}

void DeleteNode(int target, ListPointer list) {
    ListPointer previous, tmp_cell;
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

ListPointer FindPrevious(int target, ListPointer list) {
    ListPointer previous = list;
    while (previous->next != NULL && previous->next->target != target)
        previous = previous->next;    
    return previous;
}

ListPointer Find(int target, ListPointer list) {
    ListPointer current = list->next;
    while (current != NULL && current->target != target)
        current = current->next;
    return current;
}

void Insert(int target, int position, ListPointer list) {
    ListPointer after_target, tmp_cell;
    tmp_cell = CreateNode(target);
    if (position == -1) {
        tmp_cell->next = list->next;
        list->next = tmp_cell;
       
    }
    else {
        after_target = Find(position, list);
        if (after_target == NULL) {
            printf("Insertion(%d) Failed : element %d is not in the list \n", target, position);
        } 
        else {
            tmp_cell->next = after_target->next;
            after_target->next = tmp_cell;
        }
    }     
}

void DeleteList(ListPointer list) {
    ListPointer deleting, tmp_cell;
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
