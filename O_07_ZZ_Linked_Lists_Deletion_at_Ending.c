 #include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node* next;
};
struct node *head=0, *new_node, *temp,*temp1;

void insert_first()

{
    new_node = (struct node *)malloc(sizeof(struct node));
    scanf("%d",&new_node->data);
    new_node->next=head;
    head=new_node;
}

void insert_last()
{
    if(!head)
    {
        insert_first();
    }
    else
    {
        new_node = (struct node *)malloc(sizeof(struct node));
        scanf("%d",&new_node->data);
        new_node->next = 0;
        temp = head;
        while (temp->next != 0)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void delete_first()
{
    {  
        struct node *ptr,*ptr1;  
        if(head == NULL)  
        {  
            printf("\nlist is empty");  
        }  
        else if(head -> next == NULL)  
        {  
            head = NULL;  
            free(head);  
        }  
              
        else  
        {  
            ptr = head;   
            while(ptr->next != NULL)  
                {  
                    ptr1 = ptr;  
                    ptr = ptr ->next;  
                }  
                ptr1->next = NULL;  
                free(ptr);    
            }     
        }  
}

void display()
{
        temp = head;
        while (temp->next!= 0)
        {
            printf("%d->", temp->data);
            temp = temp->next;
        }
        printf("%d",temp->data);
}

int main() {
    int n,k;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        insert_last();
    }
    scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
        delete_first();
    }
    display();
    return 0;
}