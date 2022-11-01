#include <stdio.h>
#define n 1000000
char s[n];
int top = -1;
void push(char);
void pop();
int size();
int main()
{
    int t, i;
    printf("For How Many Brackets You to Check?\n");
    scanf("%d", &t);
    while (t--)
    {
        char str[1000000];
       printf("Enter Brackets: ");
        scanf("%s", str);
        for (i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == '{' || str[i] == '[' || str[i] == '(')
            {
                push(str[i]);
            }
            else
            {
                if ((str[i] == '}' && s[top] == '{') || (str[i] == ']' && s[top] == '[') || (str[i] == ')' && s[top] == '('))
                {
                    pop();
                }
            }
        }
        if (size() == 0)
        {
            top = -1;
            printf("Your Brackets is Balanced.\n");
        }
        else
        {
            printf("Your Brackets is NOT Balanced.\n");
        }
        top = -1;
    }

    return 0;
}
void push(char ch)
{
    if (top < n - 1)
    {
        top++;
        s[top] = ch;
    }
}
void pop()
{
    if (top != -1)
    {
        top--;
    }
}
int size()
{
    return top + 1;
}