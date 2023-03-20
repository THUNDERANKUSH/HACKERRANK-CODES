#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int main() 
{ 
    int n;   
    scanf("%d",&n);   
    int a[n],p[n];    
    int i;   
    for(i=0;i<n;i++)   
    {        
        scanf("%d %d",&a[i],&p[i]);   
    }    
    i=0;    
    while(i<n-1)   
    {        
        if(p[i]<p[i+1])       
        {            
            p[i+1]=p[i];        
        }       
        i++;    
    }    
    int min=0;   
    for(i=0;i<n;i++)   
    {    
        min=min+a[i]*p[i];      
    }   
    printf("%d",min);               
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */       
    return 0;
}
