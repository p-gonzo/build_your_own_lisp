#include<stdio.h> 
#include<stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node* (*push)(struct Node*, int value);
} Node;

Node* addToTail(struct Node* self, int value) {
    Node* nextNode = NULL;
    nextNode = malloc(sizeof(Node));
    nextNode->data = value;
    nextNode->next = NULL;
    nextNode->push = addToTail;
    self->next = nextNode;
    return nextNode;
}

void printList(Node *n) 
{ 
    while (n != NULL) 
    { 
        printf(" %d ", n->data); 
        n = n->next; 
    } 
}

int main(int argc, char** argv)
{

    Node* head = NULL;     
    
    head = (Node*)malloc(sizeof(Node));
    head->data = 1;
    head->push = addToTail;
    head->next = NULL;

    Node *node1 = head->push(head, 2);
    Node *node2 = node1->push(node1, 3);

    printList(head);
}

