  #include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node* next;
};
struct node *head=0, *new_node,*temp,*temp1;
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

void delete()
{
    int k;
    scanf("%d", &k);
    temp = head;       
    int i;                    
    if(k==0)
    {
        head=head->next;        
        temp->next=NULL;
        free(temp);             
    }
    else
   {
        for(i=0;i<k-1;i++)
        {
            temp=temp->next;
        }
        
        struct node *del =temp->next; 
        temp->next=temp->next->next;     
        del->next=NULL;
        free(del); 
    
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

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++)
    {
        insert_last();
    }
    delete();
    display();
 return 0;
}