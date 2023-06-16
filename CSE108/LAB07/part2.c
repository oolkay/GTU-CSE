#include <stdio.h>

int check(char arr[],char rule[],int i,int j)
{
    if (rule[j] == '\0')
        return 1;
    if (arr[i] == '\0')
        return 0;
    if (arr[i] == rule[j])
        return (check(arr,rule,i+1,j) || check(arr,rule,i+1,j+1));
    else if(rule[j] == '?')
        return check(arr,rule,i+1,j+1);
    else if(rule[j] == '*')
        return (check(arr,rule,i+1,j) || check(arr,rule,i+1,j+1));
    else
        return check(arr,rule,i+1,j);
}

void filtered_text(char string[], char rule[])
{
    char filtered[100];
    int j, k;   
    int i=0;
    while (string[i] != '\0')
    {
        while (string[i] == ' ')
        {
            i++;
        }
        j=i;
        k=0;
        while (string[j] != ' ' && string[j] != '\0')
        {
            filtered[k] = string[j];
            k++;
            j++;
        }
        i = j;
        filtered[k] = '\0';
        
        if (check(filtered,rule,0,0) == 0)
        {
            printf("%s ",filtered);
        }
        
    }
    printf("\n");
}

int main()
{
    char str[100];
    char rule[100];

    printf("Please enter the string: ");
    scanf("%[^\n]s", str);
    printf("Enter the rule: ");
    scanf("%s", rule);

    filtered_text(str, rule);
}