/**
    Jacob Massengill, January 19, 2019
    This program defines a singly linked list structure, builds said structure
    to a length n using random values, then reverses it.

    This is a common coding problem for testing proficiency at a few fundamental
    CS concepts, such as linked list structures and recursion. 
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

void printList(Node *head) {
    Node *this = head;
    while(this) {
        printf("%d ", this->value);
        this = this->next;
    }
    printf("\n");
}

Node *buildRandomList(Node *head, int size) {
    if(size <= 0) {
        return head;
    }

    head = malloc(sizeof(Node));
    head->value = rand() % 20;
    head->next = buildRandomList(head->next, size - 1);
    return head;
}

void destroyList(Node *head) {
    if(head == NULL) {
        return;
    }

    Node *next = head->next;
    free(head);
    destroyList(next);
}

Node *_reverseList(Node *head, Node *next) {
    if(next == NULL) {
        return head;
    }

    Node *after = next->next;
    next->next = head;
    _reverseList(next, after);
}

Node *reverseList(Node *head) {
   Node *new = _reverseList(head, head->next);
   head->next = NULL;
   return new;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("must have list size argument\n");
        return 1;
    }

    int n = atoi(argv[1]);

    srand(time(0));
    Node *list = buildRandomList(list, n);
    printList(list);
    list = reverseList(list);
    printList(list);
    destroyList(list);
}
