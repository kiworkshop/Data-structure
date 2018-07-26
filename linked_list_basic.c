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

struct Node *FindNode(struct Node *linked_list, int key_element)
{
    struct Node *checked_node = linked_list;

    while ((checked_node != NULL) && (checked_node->element != key_element)){
        checked_node = checked_node->next;
    }

    return checked_node;
}

struct Node *FindPrevNode(struct Node *linked_list, int key_element)
{
    if(FindNode(linked_list, key_element) == NULL){
        return NULL;
    }
    else{        
        struct Node *checked_node = linked_list;

        while((checked_node->next != NULL)&&(checked_node->next->element != key_element)){
            checked_node = checked_node->next;
        }
        return checked_node;
    }
}

void Insert(struct Node *linked_list, int prev_node_element, int element)
{
    struct Node *prev_node = FindNode(linked_list, prev_node_element);

    if(prev_node){
        struct Node *new_node = MakeNode(element);
        new_node->next = prev_node->next;
        prev_node->next = new_node;
    }
    else{
        printf("Insertion (%d) Failed : element %d is not in the list \n", element, prev_node_element);
    }
}

int main(int argc, const char *argv[])
{

    return 0;
}
