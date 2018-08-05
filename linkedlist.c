//Linked list
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* ListPointer;

struct Node {
    int element;
    ListPointer next;
};

ListPointer MakeEmpty(ListPointer list);
int IsEmpty(ListPointer list);
int IsLast(ListPointer current);
void DeleteNode(int data, ListPointer list);
ListPointer FindPrevious(int data, ListPointer list);
ListPointer Find(int data, ListPointer list);
void Insert(int data, int position, ListPointer list);
void DeleteList(ListPointer list);

int main(){
    char command;
    int target, position;
    FILE *fp = fopen("lab2_input.txt", "r");

    if (fp == NULL) {    
        printf("Input Error");
        return 1;
    }

    ListPointer list = malloc(sizeof(struct Node));
    list = MakeEmpty(list);

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
                    if (previous->element == 0) {
                        printf("Key of the previous node of %d is header.\n", target);
                    } 
                    else {
                        printf("Key of the previous node of %d is %d.\n", target, previous->element);
                    } 
                } 
                break;
            }
            case'p': {
                ListPointer current = list->next;
                while (current != NULL) {
                    printf("Key: %d ", current->element);
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

ListPointer MakeEmpty(ListPointer list) {
    list->next = NULL;
    list->element = 0;    
    return list;
}

int IsEmpty(ListPointer list) {
    return list->next == NULL;
}

int IsLast(ListPointer current) {
    return current->next == NULL;
}

void DeleteNode(int data, ListPointer list) {
    ListPointer previous, tmp_cell;
    previous = FindPrevious(data, list);    
    if (previous->next == NULL) {
        printf("Deletion failed : element %d is not int the list \n", data);
    }   
    else {
        if (!IsLast(previous)) {
            tmp_cell = previous->next;
            previous->next = tmp_cell->next;
            free(tmp_cell);
        }
    }
}

ListPointer FindPrevious(int data, ListPointer list) {
    ListPointer previous = list;
    while (previous->next != NULL && previous->next->element != data)
        previous = previous->next;    
    return previous;
}

ListPointer Find(int data, ListPointer list) {
    ListPointer current = list->next;
    while (current != NULL && current->element != data)
        current = current->next;
    return current;
}

void Insert(int data, int position, ListPointer list) {
    ListPointer after_data, tmp_cell;
    tmp_cell = malloc(sizeof(struct Node));
    tmp_cell->element = data;
    if (position == -1) {
        if (IsLast(list)) {
            list->next = tmp_cell;
        }
        else {
            tmp_cell->next = list->next;
            list->next = tmp_cell;
        } 
    }
    else {
        after_data = Find(position, list);
        if (after_data == NULL) {
            printf("Insertion(%d) Failed : element %d is not in the list \n", data, position);
        } 
        else {
            tmp_cell->next = after_data->next;
            after_data->next = tmp_cell;
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
