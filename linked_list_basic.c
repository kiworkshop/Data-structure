#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int element;
    struct Node *next;
};

struct Node *MakeNode(int element)
{
    struct Node *new_node_pointer = (struct Node *)malloc(sizeof(struct Node));
    new_node_pointer->element = element;
    new_node_pointer->next = NULL;
    return new_node_pointer;
}

void MakeNewList(struct Node **initial_node)
{
    //Make element of header node -1
    *initial_node = MakeNode(-1);
}

struct Node *FindNode(struct Node *list, int key_element)
{
    struct Node *checked_node = list;

    while ((checked_node != NULL) && (checked_node->element != key_element)){
        checked_node = checked_node->next;
    }

    return checked_node;
}

struct Node *FindPrevNode(struct Node *list, int key_element)
{
    if(FindNode(list, key_element) == NULL){
        return NULL;
    }
    else{        
        struct Node *checked_node = list;

        while((checked_node->next != NULL)&&(checked_node->next->element != key_element)){
            checked_node = checked_node->next;
        }
        return checked_node;
    }
}

void Insert(struct Node *list, int prev_node_element, int element)
{
    struct Node *prev_node = FindNode(list, prev_node_element);

    if(prev_node){
        struct Node *new_node = MakeNode(element);
        new_node->next = prev_node->next;
        prev_node->next = new_node;
    }
    else{
        printf("Insertion (%d) Failed : element %d is not in the list \n", element, prev_node_element);
    }
}

void Delete(struct Node *list, int key_element)
{
    struct Node *deleted_node = FindNode(list, key_element);
    struct Node *prev_node = FindPrevNode(list, key_element);
    struct Node *temp;

    if(!deleted_node){
        printf("Deletion failed : element %d is not in the list.\n", key_element);
    }
    else if(deleted_node == list){
        printf("Deletion failed : Could not delete header.\n");
    }
    else{
        temp = deleted_node;
        prev_node->next = deleted_node->next;
        free(temp);
    }
}

int IsEmpty(struct Node *list)
{
    return (list->next == NULL);
}

void PrintList(struct Node *list)
{
    struct Node *printed_node = list->next;
    int index = 1;
    
    while(printed_node != NULL)
    {
        printf("[%d] key : %d    ", index++, printed_node->element);
        printed_node = printed_node->next;
    }
    printf("\n");

    if(IsEmpty(list))
    {
        printf("List is empty\n");
    }
}

void ExecuteBufferLine(struct Node *list, char *buffer)
{
    char command;
    int new_element;
    int key_element;

    command = buffer[0];

        if(command =='i'){
            sscanf(buffer, "%c %d %d", &command, &new_element, &key_element);
            Insert(list, key_element, new_element);
        }
        else if(command =='d'){
            sscanf(buffer, "%c %d", &command, &key_element);
            Delete(list, key_element);
        }
        else if(command =='f'){
            sscanf(buffer, "%c %d", &command, &key_element);
            struct Node *p = FindPrevNode(list, key_element);
            if(p==list)
                printf("Key of the previous node of %d is header\n", key_element);
            else if(p==NULL)
                printf("Could not find %d in the list\n", key_element);
            else
                printf("Key of the previous node of %d is %d\n", key_element, p->element);
        }
        else if(command =='p'){
            PrintList(list);
        }
        else printf("Wrong instruction.\n");
}

int main(int argc, const char *argv[])
{
    struct Node *list;
    char buffer[10];

    MakeNewList(&list);

    for(int i=0; i<argc; i++){
         printf("%s\n", argv[i]);
    }
    
    FILE *fp = fopen(argv[1],"r");

    while(1){
        if(fgets(buffer, sizeof(buffer), fp)==NULL) break;
        
        ExecuteBufferLine(list, buffer);
    }

    fclose(fp);

    return 0;
}
