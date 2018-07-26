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

int main(int argc, const char *argv[])
{

    return 0;
}
