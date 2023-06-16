#include <stdio.h>

void trim_str(char str[50])
{
    int i=0;
    int j=0;
    int result = 2147483646;
    for (int k=0 ; 26>k ; k++)
    {
        int temp = 0;
        int i=0;
        int j=0;
        while (str[j] != '\0' && str[i] != '\0')
        {
            while (str[j] == str[i] && str[j] != '\0')
            {
                j++;
            }
            if (str[i] != k+'a')
            {
                temp++;
            }
            i = j;
        }
        
        if (temp+1 < result)
            result = temp+1;
    }
    printf("Min operation: %d\n",result);
}

int main()
{
    printf("Please enter the string: ");
    char str[50];
    scanf("%s",str);
    trim_str(str);

}