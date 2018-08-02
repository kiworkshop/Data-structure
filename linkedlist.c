//Linked list
#include<stdio.h>
#include<stdlib.h>

typedef struct Node* ListPointer;
typedef int ElementType;

struct Node {
    ElementType element;
    ListPointer next;
};

ListPointer MakeEmpty(ListPointer list_start);
int IsEmpty(ListPointer list_start);
int IsLast(ListPointer list_current_position, ListPointer list_start);
void Delete(ElementType data, ListPointer list_current_position, ListPointer list_start);
ListPointer FindPrevious(ElementType data, ListPointer list_start);
ListPointer Find(ElementType data, ListPointer list_start);
void Insert(ElementType data, ListPointer list_start, ListPointer list_current_position);
void DeleteList(ListPointer list_start);


int main(){
    char input_char;
    int buffer1, buffer2;
    FILE *fp = fopen("lab2_input.txt", "r");
    
    if (fp == NULL) {     //error handling
        printf("Input Error");
        return 1;
    }

    ListPointer list_start = malloc(sizeof(struct Node));
    list_start = MakeEmpty(list_start);

    while (!feof(fp)) {

    fscanf(fp, "%c %d %d", &input_char, &buffer1, &buffer2);

    switch (input_char) {
      case'i': {
          if (buffer2 == -1) {
              ListPointer list_current_position_i = list_start;
              Insert(buffer1, list_start, list_current_position_i);
          }
          else {
              ListPointer list_current_position_i;
              list_current_position_i = Find(buffer2, list_start);
              if (list_current_position_i == NULL) {
                  printf("Insertion(%d) Failed : element %d is not in the list \n", buffer1, buffer2);
              }
              else
                  Insert(buffer1, list_start, list_current_position_i);
          }
          break;
        }

      case'd': { 
          ListPointer list_current_position_d;
          list_current_position_d = FindPrevious(buffer1, list_start);
          if (list_current_position_d->next == NULL) {
              printf("Deletion failed : element %d is not int the list \n", buffer1);
          }   
          else
              Delete(buffer1, list_current_position_d, list_start);
          break;
       }            

      case'f': {
          ListPointer list_current_position_f;
          list_current_position_f = FindPrevious(buffer1, list_start);
          if (list_current_position_f->next == NULL) {
              printf("Could not find %d in the list \n", buffer1);
          }
          else {
              if (list_current_position_f->element == 0) {
                  printf("Key of the previous node of %d is header.\n", buffer1);
              }
              else {
                  printf("Key of the previous node of %d is %d.\n", buffer1, list_current_position_f->element);
              }
          }
          break;
      }

      case'p': {
          ListPointer list_current_position_p = list_start->next;
          while (list_current_position_p != NULL) {
              printf("Key: %d ", list_current_position_p->element);
              list_current_position_p = list_current_position_p->next;
          }
          break;
      }

      default:
          continue;
      }
    }
    DeleteList(list_start);
    fclose(fp);
    return 0;
}

ListPointer MakeEmpty(ListPointer list_start) {
    list_start->next = NULL;
    list_start->element = 0;
    return list_start;
}

int IsEmpty(ListPointer list_start) {
    return list_start->next == NULL;
}

int IsLast(ListPointer list_current_position, ListPointer list_start) {
    return list_current_position->next == NULL;
}

void Delete(int data, ListPointer list_current_position, ListPointer list_start) {
    ListPointer tmp_cell;
    
    if (!IsLast(list_current_position, list_start)) {
        tmp_cell = list_current_position->next;
        list_current_position->next = tmp_cell->next;
        free(tmp_cell);
    }
}

ListPointer FindPrevious(int data, ListPointer list_start) {
    
    ListPointer list_current_position;

    list_current_position = list_start;
    while (list_current_position->next != NULL && list_current_position->next->element != data)
        list_current_position = list_current_position->next;

    return list_current_position;
}

ListPointer Find(int data, ListPointer list_start) {
    ListPointer list_current_position;

    list_current_position = list_start->next;
    while (list_current_position != NULL && list_current_position->element != data)
        list_current_position = list_current_position->next;

    return list_current_position;
}

void Insert(int data, ListPointer list_start, ListPointer list_current_position) {
    ListPointer tmp_cell;

    tmp_cell = malloc(sizeof(struct Node));
    tmp_cell->element = data;

    if (IsLast(list_start,list_current_position)) {
        list_start->next = tmp_cell;
    }
    else {
        tmp_cell->next = list_current_position->next;
        list_current_position->next = tmp_cell;
    }   
}

void DeleteList(ListPointer list_start) {
    free(list_start);
}
