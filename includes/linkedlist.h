#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

struct Node {
    struct Node *next;
    void *data;
};

struct LinkedList {
    struct Node *head;
};

struct LinkedListOp {
    struct LinkedList* (*Instance) ();
    void (*Append) (struct LinkedList *linkedList, void *element);
    void (*Delete) (struct LinkedList *linkedList, int index);
    void* (*Find) (struct LinkedList *linkedList, int index);
    void (*Print) (struct LinkedList *linkedList);
    void (*Free) (struct LinkedList *linkedList);
};

extern const struct LinkedListOp linkedListOp;

#endif  // __LINKEDLIST_H__