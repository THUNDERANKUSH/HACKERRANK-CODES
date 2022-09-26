 #include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

struct node* createNode(struct node* head, int data){
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    
    if(head==NULL){
        head = temp;
        head->next = NULL;
        return head;
    }
    
    temp->next = head;
    head = temp;
    return head;
}
void printLL(struct node* head){
    if(head == NULL){
        printf("NULL");
        return;
    }
    while(head != NULL){
        if(head->next == NULL){
            printf("%d", head->data);
            return;
        }
        printf("%d->", head->data);
        head = head->next;
    }
    
}
int main() {
    int n, data;
    scanf("%d", &n);
    
    struct node* head = NULL;
    
    for(int i=0; i<n; i++){
        scanf("%d", &data);
        head = createNode(head,data);
    }
    printLL(head);
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}