#include <stdio.h>
#include <stdlib.h>

struct Node { 
    int element;
    struct Node *next;
};

struct Node *CreateNode(int element) {
    struct Node *pos = malloc(sizeof(struct Node));
    pos->element = element;
    pos->next = NULL;

    return pos; 
}

int IsEmpty(struct Node *list) { 
   return list->next == NULL;
}

int IsLast(struct Node *pos) {
    return pos->next == NULL;
}

struct Node *Find(int element, struct Node *list) {
    struct Node *pos = list;
    while (pos != NULL) {
        if (element == pos->element) {
            break;
        }
        pos = pos->next;
    }    
    return pos;
}

struct Node *FindPrevious(int element, struct Node *list) {
    struct Node *pos = list;
    while (pos->next != NULL && pos->next->element != element) {
        pos = pos->next;
    }
    if (IsLast(pos)) {
        return NULL;
    }
    return pos;
}

void Insert(int element, int prev, struct Node *list) {
    struct Node *pos = Find(prev, list);
    if (pos == NULL) {
        printf("Insertion(%d) failed: element %d is not in the list\n", element, prev);
        return;
    } 
    struct Node *new = CreateNode(element);
    new->next = pos->next;
    pos->next = new;
}

void Delete(int element, struct Node *list) {
    struct Node *del = Find(element, list);
    if (del == NULL) {
        printf("Deletion failed: element %d is not in the list\n", element);
        return;
    }
    struct Node *prev = FindPrevious(element, list);
    prev->next = del->next;
    free(del);
}

void PrintListNodes(struct Node *list) {
    struct Node *pos = list->next;
    while (pos != NULL) {
        printf("key: %d \t",pos->element);
        pos = pos->next;
    }
    printf("\n");
}

void FreeListNodes(struct Node *list) {
    struct Node *pos = list;
    struct Node *freeNode;
    while (pos != NULL) {
        freeNode = pos;
        pos = pos->next;
        free(freeNode);
    }
}

void ParseCommandToFunction(FILE* fp, struct Node *list) {
   char buf[8];
   char command;
   if (fp == NULL) {
        fprintf(stderr, "cannot open the file\n");
        exit(EXIT_FAILURE);
   }
   while (!feof(fp)) {
        fgets(buf, 8, fp);
        command = buf[0];
        int element;
        int prev;
        switch (command) {
            case 'i': 
                sscanf(buf, "%*c %d %d", &element, &prev);
                Insert(element, prev, list); 
                break;
            case 'd': 
                sscanf(buf, "%*c %d", &element);
                Delete(element, list); 
                break;
            case 'f': 
                sscanf(buf, "%*c %d", &element);
                FindPrevious(element, list); 
                break;
            case 'p': 
                PrintListNodes(list); 
                break;
        }
    }
    fclose(fp);
}

int main(int argc, const char *argv[]) {
    struct Node *list;
    list = CreateNode(-1);

    FILE* fp;
    fp = fopen(argv[1], "rt");
    if (argc == 2) {
        ParseCommandToFunction(fp, list);       
    } else {
        printf("wrong execution: put an argument file");
    }
    FreeListNodes(list);
    return 0;
}
