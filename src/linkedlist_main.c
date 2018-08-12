#include "linkedlist.h"

int main(int argc, char** argv) {
    struct LinkedListOp op = linkedListOp;
    struct LinkedList *linkedList;
    
    linkedList = op.Instance();
    op.Free(linkedList);

    return 0;
}