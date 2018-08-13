#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 128
#define MAX_ARGUMENT 2

struct Node{
    int element;
    struct Node *next;
};

struct List{
    struct Node *header;
};

enum Command{
    UNKNOWN,
    INSERT,
    DELETE,
    FINDPREVIOUS,
    PRINT,
};

struct CommandLine{
    char buf[MAX_BUF];
    enum Command command;
    int arguments[MAX_ARGUMENT];
};

struct Node *CreateNode(int element)
{
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->element = element;
    new->next = NULL;

    return new;
}

struct List *CreateList()
{
    struct List *new = (struct List *)malloc(sizeof(struct List));
    new->header = CreateNode(-1);

    return new;
}

int IsEmpty(struct List *list)
{
    return list->header->next == NULL;
}

struct Node *Find(int element, struct List *list)
{
    struct Node *pos = list->header;
    while (pos) {
        if (pos->element == element) {
            break;
        }
        pos = pos->next;
    }
    return pos;
}

struct Node *FindPrevious(int element, struct List *list)
{
    struct Node *pos = list->header;
    while (pos->next) {
        if (pos->next->element == element) {
            break;
        }
        pos = pos->next;
    }
    return pos;
}

void Insert(int element, int pre_element, struct List *list)
{
    struct Node *pre_node = Find(pre_element, list);
    if (pre_node) {
        struct Node *new_node = CreateNode(element);
        new_node->next = pre_node->next;
        pre_node->next = new_node;
    } else {
        printf("Insertion(%d) Failed : element %d is not in the list.\n", element, pre_element);
    }
}

void Delete(int element, struct List *list)
{
    struct Node *pre_node = FindPrevious(element, list);
    if (pre_node->next) {
        struct Node *target_node = pre_node->next;
        pre_node->next = target_node->next;
        free(target_node);
    } else {
        printf("Deletion Failed : element %d is not in the list.\n", element);
    }
}

void PrintList(struct List *list)
{
    struct Node *pos = list->header;
    while (pos) {
        printf("key:%d      ", pos->element);
        pos = pos->next;
    }
    printf("\n");
}

void ParseCommandLine(struct CommandLine *commandline)
{
    char command = commandline->buf[0];
    switch (command) {
        case 'i':
            commandline->command = INSERT;
            sscanf(commandline->buf, "%*c %d %d", &commandline->arguments[0], &commandline->arguments[1]);
            break;
        case 'd':
            commandline->command = DELETE;
            sscanf(commandline->buf, "%*c %d", &commandline->arguments[0]);
            break;
        case 'f':
            commandline->command = FINDPREVIOUS;
            sscanf(commandline->buf, "%*c %d", &commandline->arguments[0]);
            break;
        case 'p':
            commandline->command = PRINT;
            break;
        default:
            commandline->command = UNKNOWN;
    }
}

int main(int argc, const char *argv[])
{
    if (argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        struct List *list = CreateList();
        if (fp) {
            struct CommandLine commandline;
            while (fgets(commandline.buf, sizeof(commandline.buf), fp)){
                ParseCommandLine(&commandline);
                switch (commandline.command){
                    case INSERT:
                        Insert(commandline.arguments[0], commandline.arguments[1], list);
                        break;
                    case DELETE:
                        Delete(commandline.arguments[0], list);
                        break;
                    case FINDPREVIOUS:
                        FindPrevious(commandline.arguments[0], list);
                        break;
                    case PRINT:
                        PrintList(list);
                        break;
                    case UNKNOWN:
                        printf("Invalid command!\n");
                        break;
                }
            }
            fclose(fp);
        } else {
            printf("file open error\n");
        }
    }
    return 0;
}
