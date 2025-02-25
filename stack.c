#include<stdio.h>
#include<stdlib.h>


struct stack {
    int data;
    struct stack * next ;
};

typedef struct stack st;

st * top = NULL;

void display() {
    st * temp = top;

    while (temp != NULL) {
        printf("%d  ", temp -> data);
        temp = temp -> next;
    }
}

void push(int data) {
    st * newnode = malloc(sizeof(st));
    if (newnode == NULL) {
        printf ("Memory allocation failed\n");
    }

    newnode -> data = data;
    newnode -> next = top;
    top = newnode;
}

void pop() {
    if (top == NULL) {
        exit;
    }
    else {
    st * temp = top;
    top = top -> next;
    free(temp);
    }
}

int main() {
    push(2);
    push(4);
    push(6);

    display();

    printf("\n");
    
    pop();
    pop();


    display();
}