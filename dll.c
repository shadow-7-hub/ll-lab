#include<stdio.h>
#include<stdlib.h>


struct Node {
    int data;
    struct Node * prev;
    struct Node * next;
};

typedef struct Node node;

node * head = NULL;

void display();
void insert(int data);

int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(40);

    display();

    return 0;
}

void insert(int data) {
    node * newnode = malloc(sizeof(node));

    if (newnode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newnode -> data = data;
    newnode -> next = NULL;

    if (head == NULL) {
        newnode -> prev = NULL;
        head = newnode;
    }
    else {
        node * temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp -> next = newnode;
        newnode -> prev = temp;
    }
}

void display(){
    node * temp = head;

     printf("\n[   ");

    while (temp != NULL) {
        printf("%d  ", temp -> data);
        temp = temp -> next;
    }

     printf("]");
}