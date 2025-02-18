#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node*next;
};

typedef struct Node node;

void print(node*head)
{
    while (head != NULL)
    {
        printf("%d ", head -> data);
        head = head -> next;
    }
}

int main()
{
    node* head;
    node* first = NULL;
    node* second = NULL;
    node* third = NULL;

    first = malloc(sizeof(node));
    second = malloc(sizeof(node));
    third = malloc(sizeof(node));

    first -> data = 2;
    second -> data = 3;
    third -> data = 4;

    first -> next = second;
    second -> next = third;
    third -> next = NULL;
    head = first;

    node*newnode;
    newnode = malloc(sizeof(node));
    newnode -> data = 1;
    newnode -> next = head;
    head = newnode;

    node*newnode2;
    newnode2 = malloc(sizeof(node));
    newnode2 -> data = 6;
    newnode2->next = NULL;

    node*temp = head;
    while (temp -> next != NULL)
    {
        temp = temp -> next;
    }

    temp -> next = newnode2;

    node* newnode3;
    newnode3 = malloc(sizeof(node));
    newnode3 -> data = 5;

    temp = head;
    while (temp != NULL && temp->data != 4)
    {
        temp = temp -> next;
    }

    if (temp != NULL)
    {
        newnode3 -> next = temp -> next;
        temp -> next = newnode3;
    }


    print(head);

    printf("\n");

    if (head != NULL)
    {
        temp = head;
        head = head -> next;
        free(temp);
    }

    print(head);
    printf("\n");


    temp = head;
    while (temp != NULL && temp->next != NULL && temp -> next -> data != 4)
    {
        temp = temp -> next;
    }

    if (temp != NULL && temp->next != NULL && temp->next->data == 4)
    {
        node*k = temp -> next;
        temp -> next = k -> next;
        free(k);
    }

    print(head);

    return 0;
}
