//list-studentID

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENROLLMENT 30
#define MAX_BUF 128
#define MAX_ARGUMENT 8

enum command_t{
    UNKNOWN,
    INSERT,
    DELETE,
    FIND,
    PRINT,
};

struct commandline_t{
    char buf[MAX_BUF];
    enum command_t command;
    char student_id[MAX_ARGUMENT];     
    char student_name[MAX_ENROLLMENT];
};

struct Node{
    char given_id[MAX_ARGUMENT];
    char given_name[MAX_ENROLLMENT];
    struct Node* next;
};

void ParseCommandLine(struct commandline_t* commandline) {
    char command = commandline->buf[0];

    switch (command) {
      case 'i':
          commandline->command = INSERT;
          sscanf(commandline->buf, "%*c %s %[^\n]s", commandline->student_id, commandline->student_name);
          break;
      case 'd':
          commandline->command = DELETE;
          sscanf(commandline->buf, "%*c %s", commandline->student_id);
          break;
      case 'f':
          commandline->command = FIND;
          sscanf(commandline->buf, "%*c %s", commandline->student_id);
          break;
      case 'p':
          commandline->command = PRINT;
          break;
      default:
          commandline->command = UNKNOWN;
    }
}

void MakeEmpty(struct Node* L);
struct Node* Find(char* student_id,struct Node* L);
void InsertF(char* student_id, char* student_name, struct Node* L);
void PrintNode(struct Node* L);
void Delete(char* student_id, struct Node* L);

int main(int argc, const char* argv[]){
    if (argc == 2) {
        FILE *fp = fopen(argv[1],"r");
        if (fp) {
            struct commandline_t commandline;
            
            //make new node
            struct Node* L = (struct Node*)malloc(sizeof(struct Node));

            //initialize the node
            MakeEmpty(L);    

            while(fgets(commandline.buf, sizeof(commandline.buf),fp)) {
                ParseCommandLine(&commandline);
                switch (commandline.command) {
                  case INSERT:
                      {
                       //duplicate check with Find function
                           struct Node* duplicate;
                           duplicate = Find(commandline.student_id, L);
                           if (duplicate != NULL) {
                               printf("There already is an element with key %s . Insertion failed\n", commandline.student_id);
                               break;
                           }
                           else {
                           //Insertion function
                               InsertF(commandline.student_id, commandline.student_name, L);
                           }
                           
                           //Print all node
                           printf("Insertion Success : %s \n", commandline.student_id);
                           printf("Current List>");
                           PrintNode(L);
                           printf("\n");
                           break;
                       }
                  case DELETE:
                      {
                           struct Node* check;
                           check = Find(commandline.student_id, L);
                           if (check == NULL) {
                               printf("Deletion failed : element %s is not in the list \n", commandline.student_id);
                               break;
                           }
                           else {
                               //Delete function
                               Delete(commandline.student_id, L);

                               //Print all node
                               printf("Deletion Success : %s\n", commandline.student_id);
                               printf("Current List>");
                               PrintNode(L);
                               printf("\n");
                               break;
                            }
                      }
                  case FIND:
                      {
                           //FIND
                           struct Node* find;
                           find = (commandline.student_id, L);
                           if (find == NULL) {
                               printf("Find failed : element %s is not in the list", commandline.student_id);
                               break;
                           } 
                           else {
                               //Print the node
                               printf("Find Success : %s\n", find->given_id);
                               break;
                            }
                      }

                  case PRINT:
                      {
                           //Print all node
                           PrintNode(L);
                           printf("\n");
                           break;
                      }
                  default:
                      continue;
                }
            }
        }
        else {
            printf("file open error \n");
        }
    }
    return 0;
}

void MakeEmpty(struct Node* L) {
    L->given_id;
    L->given_name;
    L->next = NULL;
}

struct Node* Find(char* student_id, struct Node* L) {
    struct Node* search = L->next;

    int s_given_id = 1;
    int s_stu_id = atoi(student_id);

    while (search != NULL) {
        s_given_id = atoi(search->given_id);
        if (s_stu_id == s_given_id) {
            break;
        }
        else {
            search = search->next;
        }   
    }   

    return search;
}

void InsertF(char* student_id, char* student_name, struct Node* L) {
    //create new node
    struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
    strcpy(tmp->given_id, student_id);
    strcpy(tmp->given_name, student_name);

    int compare_target = atoi(student_id);
    //Insert with sorted position
    struct Node* position = L;
    while (position->next != NULL) {
        int comparing = atoi(position->next->given_id);

        if (compare_target < comparing) {
            break;
        }
        else {
            position = position->next;
        }
    }

    if (position->next == NULL) {
        position->next = tmp;
    }
    else {
        tmp->next = position->next;
        position->next = tmp;
    }
}

void PrintNode(struct Node* L){
    struct Node* position = L->next;
    while (position != NULL) {
        printf("%s %s ", position->given_id, position->given_name);
        position = position->next;
    }
}

void Delete(char* student_id, struct Node* L){
    struct Node* position = L;

    int compare_target = atoi(student_id);
  
    while (position->next != NULL) {
        int comparing = atoi(position->next->given_id);
        if (compare_target == comparing) {
            break;
        }
        else {
            position = position->next;
        }
    }
    
    if (position->next->next == NULL) {
        free(position->next);
    }
    else {
        struct Node* tmp;
        tmp = position->next;
        position->next = tmp->next;
        free(tmp);
    }
}
