#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 128
#define MAX_ARGUMENT 2
#define MAX_ENROLLMENT 30

enum Command {
    UNKNOWN,
    INSERT,
    DELETE,
    PRINT,
};

struct CommandLine {
    char buf[MAX_BUF];
    enum Command command;
    int arguments[MAX_ARGUMENT];
};

struct Student { 
    char studentId[12];
    char studentName[20];
};

struct Node {
    struct Student student;
    struct Node *next;
};

struct Node *CreateNode(struct Student *student) {
    struct Node *pos = (struct Node*) malloc(sizeof(struct Node));
    memcpy(&(pos->student), student, sizeof(struct Student));
    pos->next = NULL;

    return pos;
}

void *CreateList(struct Node **list_ptr) {
   struct Student header = {
       .studentId = "-1",
       .studentName = "header",
   };
   *list_ptr = CreateNode(&header);
}
int IsLast(struct Node *pos) {
    return pos->next == NULL;
}

struct Node *Find(struct Student *student, struct Node *list) {
    struct Node *pos = list;
    while (pos != NULL) {
        if (strcmp(student->studentId, (pos->student).studentId) == 0) {
            break;
        }
        pos = pos->next;
    }
    return pos;
}

struct Node *FindPrevious(struct Student *student, struct Node *list) {
    struct Node *pos = list;
    while (pos->next != NULL) {
        if (strcmp(student->studentId, (pos->next->student).studentId) == 0) {
            break;
        }
        pos = pos->next;
    }
    if (IsLast(pos)) {
        return NULL;
    }
    return pos;
}

void PrintList(struct Node *list) {
    struct Node *pos = list;
    pos = pos->next;
    while (pos != NULL) {
        printf("current list>> %s %s  ", (pos->student).studentId, (pos->student).studentName);
        pos = pos->next;
    }
    printf("\n");
}

void Insert(struct Student *student, struct Node *list, int *enroll_num) {
    if (Find(student, list) == NULL & *enroll_num < MAX_ENROLLMENT) {
        struct Node *pos = list;
        struct Node *prev = list;
        struct Node *new = CreateNode(student);
        while (pos->next != NULL & atoi((pos->student).studentId) < atoi(student->studentId)) {
            prev = pos;
            pos = pos->next;
        }
        new->next = prev->next;
        prev->next = new;

        PrintList(list);
        *enroll_num += 1;
    } else {
        printf("There already is an element with key %s. Insertion failed.\n", student->studentId);    
    }  
}

void Delete(struct Student *student, struct Node *list, int *enroll_num) {
    struct Node *prev = FindPrevious(student, list);
    struct Node *del = NULL;
    if (prev != NULL) {
        del = prev->next;
    }
    if (prev == NULL || del == NULL) {
        printf("Deletion failed: %s is not in the list\n", student->studentId);
        return;
    }
    prev->next = del->next;
    free(del);
    *enroll_num -= 1;
}

void FreeAll(struct Node *list) {
    struct Node *pos = list;
    struct Node *free_node;
    while (pos != NULL) {
        free_node = pos;
        pos = pos->next;
        free(free_node);
    }
}

void *ParseCommandLine(struct CommandLine *commandline, struct Student **st_ptr) {
    char command = commandline->buf[0];
    *st_ptr = malloc(sizeof(struct Student));

    switch (command) {
        case 'i':
            commandline->command = INSERT;
            sscanf(commandline->buf, "%*c %s %[^\n]s", ((*st_ptr)->studentId), ((*st_ptr)->studentName));
            break;
        case 'd':
            commandline->command = DELETE;
            sscanf(commandline->buf, "%*c %s", ((*st_ptr)->studentId));
            break;
        case 'p':
            commandline->command = PRINT;
            break;
    }
}

int main(int argc, const char *argv[]) {
    if (argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        if (fp) {
            struct CommandLine commandline;
            struct Student *student;
            struct Node *list;
            CreateList(&list);
            int enroll_num = 0;
            while (fgets(commandline.buf, sizeof(commandline.buf), fp)) {
                ParseCommandLine(&commandline, &student);
                switch (commandline.command) {
                    case INSERT:
                        Insert(student, list, &enroll_num); break;
                    case DELETE:
                        Delete(student, list, &enroll_num); break;
                    case PRINT:
                        PrintList(list); break;
                    case UNKNOWN:
                        printf("wrong command!");break;
                }
            }
            fclose(fp);
        } else {
            printf("file open error \n");
        }
    } else {
        printf("usage: {executable} {input text file_ex.lab3_input.txt}\n");
    }
    return 0;
}
