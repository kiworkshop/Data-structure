#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

struct Node {
    struct Node *next;
    void *data;
};

struct LinkedList {
    struct Node *head;
    struct Node *tail;
};

struct LinkedListOp {
    struct LinkedList *(*Instance)();
    void (*Append)(struct LinkedList *linked_list, void *element);
    void (*Prepend)(struct LinkedList *linked_list, void *element);
    void *(*Delete)(struct LinkedList *linked_list, void *element,
                   int (*Equals)(void *compared, void *item));
    void *(*Find)(struct LinkedList *linked_list, void *element,
                  int (*Equals)(void *compared, void *item));
    void (*ForEach)(struct LinkedList *linked_list,
                    void (*Function)(void *data));
    void (*Free)(struct LinkedList *linked_list);
    void (*FreeWithItems)(struct LinkedList *linked_list);
};

extern const struct LinkedListOp linked_list_op;

#endif  // __LINKEDLIST_H__