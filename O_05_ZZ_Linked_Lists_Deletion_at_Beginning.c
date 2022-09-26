 #include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

struct node* createNode(struct node* head, struct node* tail, int data){
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    
    if(head==NULL){
        head = temp;
        tail = temp;
        return tail;
    }
    
    tail->next = temp;
    tail = temp;
    return tail;
}
struct node* deleteNodes(struct node* head, int k){
    if(head==NULL){
        return NULL;
    }
    
    struct node* temp = NULL;
    for(int i=0; i<k; i++){
        temp = head;
        head = head->next;
        free(temp);
    }
    return head;
}

void printLL(struct node* head){
    if(head == NULL){
        return;
    }
    while(head != NULL){
        if(head->next == NULL){
            printf("%d", head->data);
            return;
        }
        // printf("\nSukhamaano\n");////////////////////////////////////////////////
        printf("%d->", head->data);
        head = head->next;
    }
}
int main() {
    int n,data,k;
    scanf("%d", &n);
    
    struct node* head = NULL;
    struct node* tail = NULL;
    for(int i=0; i<n; i++){
        scanf("%d", &data);
        tail = createNode(head, tail, data);
        if(i==0){
            head = tail;
        }
        // printf("\nhead->data: %d\n",head->data);////////////////////////////////////////////////
    }
    
    scanf("%d", &k);
    head = deleteNodes(head,k);
    printLL(head);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}