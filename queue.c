#include<stdio.h>
#include<stdlib.h>

struct queue {
    int data;
    struct queue * next;
};

typedef struct queue qu;

qu * front = NULL;
qu * rear = NULL;

void enqueue(int data) {
    if (front == NULL && rear == NULL ) {
        qu * newnode = malloc(sizeof(qu));
        newnode -> data = data;
        newnode -> next = NULL;
        front = newnode;
        rear = newnode;
    }
    else {
        qu * newnode = malloc(sizeof(qu));
        newnode -> data = data;
        newnode -> next = NULL;
        rear -> next = newnode;
        rear = newnode;
    }
}

void dequeue() {
    if (front == NULL && rear == NULL ) {
        exit;
    }

    else if (front == rear) {
        qu * temp = front;
        front = NULL;
        rear = NULL;
        free(temp);
    }
    else {
        qu * temp = front;
        front = front -> next;
        free(temp);
    }
}

void display() {
    qu * temp = front;

    while (temp != NULL) {
        printf("%d  ", temp -> data);
        temp = temp -> next;
    }
}


int main() {

    enqueue(2);
    enqueue(4);
    enqueue(6);

    display();

    printf("\n");

    dequeue();
    dequeue();

    display();

    return 0;

}
