//list-studentID

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENROLLMENT 30
#define MAX_BUF 128
#define MAX_ARGUMENT 8

enum Command{
    UNKNOWN,
    INSERT,
    DELETE,
    FIND,
    PRINT,
};

struct Commandline{
    char tmp_string[MAX_BUF];
    enum Command command;
    char student_id[MAX_ARGUMENT];     
    char student_name[MAX_ENROLLMENT];
};

struct Node{
    char given_id[MAX_ARGUMENT];
    char given_name[MAX_ENROLLMENT];
    struct Node* next;
};

void ParseCommandLine(struct Commandline *commandline) {
    char command = commandline->tmp_string[0];
    switch (command) {
        case 'i':
            commandline->command = INSERT;
            sscanf(commandline->tmp_string, "%*c %s %[^\n]s", commandline->student_id, commandline->student_name);
            break;
        case 'd':
            commandline->command = DELETE;
            sscanf(commandline->tmp_string, "%*c %s", commandline->student_id);
            break;
        case 'f':
            commandline->command = FIND;
            sscanf(commandline->tmp_string, "%*c %s", commandline->student_id);
          break;
        case 'p':
            commandline->command = PRINT;
            break;
        default:
            commandline->command = UNKNOWN;
    }
}

struct Node* CreateNode();
struct Node* Find(char* student_id, struct Node* list);
void InsertF(char* student_id, char* student_name, struct Node* list);
void PrintNode(struct Node* list);
void Delete(char* student_id, struct Node* list);

int main(int argc, const char* argv[]) {
    if (argc == 2) {
        FILE *fp = fopen(argv[1],"r");
        if (fp) {
            struct Commandline commandline;
            struct Node* list = CreateNode();
            struct Node* duplicate, *check, *find;
            //여기 까지 수정
            while(fgets(commandline.tmp_string, sizeof(commandline.tmp_string), fp)) {
                ParseCommandLine(&commandline);
                switch (commandline.command) {
                    case INSERT:
                        //duplicate check with Find function
                        duplicate = Find(commandline.student_id, list);
                        if (duplicate != NULL) {
                            printf("There already is an element with key %s . Insertion failed\n", commandline.student_id);
                            break;
                        }
                       
                        //Insertion function
                        InsertF(commandline.student_id, commandline.student_name, list);
                        
                        //Print all node
                        printf("Insertion Success : %s \n", commandline.student_id);
                        printf("Current List>");
                        PrintNode(list);
                        break;            
                    case DELETE:
                        check = Find(commandline.student_id, list);
                        if (check == NULL) {
                            printf("Deletion failed : element %s is not in the list \n", commandline.student_id);
                            break;
                        }
                        else {
                            //Delete function
                            Delete(commandline.student_id, list);

                            //Print all node
                            printf("Deletion Success : %s\n", commandline.student_id);
                            printf("Current List>");
                            PrintNode(list);
                            printf("\n");
                            break;
                        }
                    case FIND:
                        //FIND
                        find = (commandline.student_id, list);
                        if (find == NULL) {
                            printf("Find failed : element %s is not in the list", commandline.student_id);
                            break;
                        } 
                        else {
                            //Print the node
                            printf("Find Success : %s\n", find->given_id);
                            break;
                        }
                    case PRINT:
                        //Print all node
                        PrintNode(list);
                        printf("\n");
                        break;
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

struct Node* CreateNode() {
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    new->next = NULL;
    return new;
}

struct Node* Find(char* student_id, struct Node* list) {
    struct Node* search = list->next;
    int tmp_given_id;
    int tmp_stu_id = atoi(student_id);

    while (search != NULL) {
        tmp_given_id = atoi(search->given_id);
        if (tmp_stu_id == tmp_given_id) {
            break;
        }
        else {
            search = search->next;
        }   
    }   
    return search;
}

void InsertF(char* student_id, char* student_name, struct Node* list) {
    //create new node
    struct Node* tmp = CreateNode();
    strcpy(tmp->given_id, student_id);
    strcpy(tmp->given_name, student_name);

    int compare_target = atoi(student_id);
    //Insert with sorted position
    struct Node* position = list;
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

void PrintNode(struct Node* list) {
    struct Node* position = list->next;
    while (position != NULL) {
        printf("%s %s ", position->given_id, position->given_name);
        position = position->next;
    }
    printf("\n");
}

void Delete(char* student_id, struct Node* list) {
    struct Node* position = list;
    int compare_target = atoi(student_id);
    while (position->next) {
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
