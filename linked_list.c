#include<stdio.h> 
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node* (*push)(struct Node*, int value);
} Node;

Node* pushToNode(struct Node* self, int value) {
    Node* nextNode = NULL;
    nextNode = malloc(sizeof(Node));
    nextNode->data = value;
    nextNode->next = NULL;
    nextNode->push = pushToNode;
    self->next = nextNode;
    return nextNode;
}

typedef struct LinkedList {
    struct Node *head;
    struct Node *tail;
    void (*addToTail)(struct LinkedList*, int value);
} LinkedList;


void addToTail(struct LinkedList* self, int value){
    if (self->head == NULL) {
        Node* head = NULL;
        head = (Node*)malloc(sizeof(Node));
        head->data = value;
        head->push = pushToNode;
        head->next = NULL;
        self->head = head;
        self->tail = head;
    } else {
        self->tail = self->tail->push(self->tail, value);
    }
};

void printList(Node *n) { 
    while (n != NULL) { 
        printf(" %d ", n->data); 
        n = n->next; 
    } 
}

LinkedList* initializeLinkedList() {
    LinkedList* ll = NULL;
    ll = (LinkedList*)malloc(sizeof(LinkedList));
    ll->head = NULL;
    ll->tail = NULL;
    ll->addToTail = addToTail;
    return ll;
};

int main(int argc, char** argv) {

    LinkedList* ll = initializeLinkedList();

    for (int i=0; i<10000; i ++) {
        ll->addToTail(ll, i);
    }

    printList(ll->head);
}

