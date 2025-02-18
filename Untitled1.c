#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node {
   int data;
   struct node *next;
};
struct node *head = NULL;

// display the list
void printList(){
   struct node *p = head;
   printf("\n[");

   //start from the beginning
   while(p != NULL) {
      printf(" %d ",p->data);
      p = p->next;
   }
   printf("]");
}

//insertion at the beginning
void insertatbegin(int data){

   //create a link
   struct node *lk = (struct node*) malloc(sizeof(struct node));
   lk->data = data;

   // point it to old first node
   lk->next = head;

   //point first to new first node
   head = lk;
}

void insertatlast(int data) {
     struct node *lk = (struct node*) malloc(sizeof(struct node));
     lk->data = data;

     lk -> next = NULL;

    struct node*temp=head;
    while (temp -> next != NULL) {
        temp = temp -> next;
    }

    temp -> next = lk;
}
void main(){
   //int k=0;
   insertatbegin(4);
   insertatlast(2);
   insertatlast(6);
   insertatlast(8);
   insertatlast(10);
   insertatlast(12);

   printf("Linked List: ");

   // print list
   printList();
}
