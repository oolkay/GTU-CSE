#include "utils.h"

//finds the closest word to the given word(str), and returns its line
int find_closest(char *str, char dict[][MAX_WORD_SIZE])
{

	double	min = -1, i = 0;
	char	answer[MAX_WORD_SIZE];
	int		closest_line = 0;
	int		line;

	line = find_line(str, dict);
	if (line == -1)
        return (line);
	min = dissimilarity(dict[line], answer, dict, THRESHOLD);
	closest_line = find_line(answer, dict);
	return (closest_line);
}

//finds the occurence of given word in input.txt
int find_occurence(char words[][MAX_WORD_SIZE], char *str, int read_nbr)
{
    int count = 0;
    for (int i = 0; i < read_nbr; i++)
        if (strcmp(str, words[i]) == 0) //compare the given word with input.txt
            count++;//counts occurence
    if (count == 0)
        return (-1);//my erno
    return (count);
}


//assing the given string to the given array
int assing_str_to_arr(char arr[][MAX_WORD_SIZE], char str[], int indx)
{
    int i = -1;
    if (!str)
        return (-1);
    while (str[++i] != '\0')
        arr[indx][i] = str[i];
    arr[indx][i] = '\0';
    return (1);
}

//assing the given string to the given array
int assing_str_to_his(char his[][MAX_WORD_SIZE+20+5], char str[], int indx)
{
    int i = -1;
    if (!str)
        return (-1);
    while (str[++i] != '\0')
        his[indx][i] = str[i];
    his[indx][i] = '\0';
    return (1);
}

//check the given words is ignored or not, in order to store the word or not
int check_is_ignored(char word[])
{
    FILE *file = fopen(IGNORE, "r");
    char str[MAX_WORD_SIZE];

    while (fscanf(file, "%s", str) != -1)
    {
        if (strcmp(word, str) == 0)//if it is ignored, returns 0 that means dont store it
        {
            fclose(file);
            return (0);
        }
    }
    fclose(file);
    return (1);
}

//if the letter ignored, returns 0, not ignored return 1
int check_ignore_letters(char ch)
{
    if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))
        return (1);
    return (0);
}


//a copy of strlen
int my_strlen(const char *str)
{
    int len = -1;
    while (str[++len] != '\0');
    return (len);
}
//a copy of strcat
void my_strcat(char *dest, char *src)
{
	int i = 0;
    int j = 0;
    while (dest[j] != '\0')
        j++;
	while (src[i] != '\0')
    {
		dest[j] = src[i];
		i++;
		j++;
	}
    dest[j] = '\0';
}

//similar function to strcpy
void my_strcpy(char arr[MAX_WORD_SIZE], char str[])
{
	int i = -1;
	if (!str)
        return ;
	while (str[++i] != '\0')
		arr[i] = str[i];
	arr[i] = '\0';
}

//similar to atoi
int my_atoi(char *str)
{
    int i = 0;
    int res = 0;

    while (str[i] != '=')//num_word=1000, skipping until 1000
        i++;
    i++;
    while (str[i] && str[i] != ',')//num_word=1000, reading until ,
    {
        res *= 10;
        res += str[i] - 48;
        i++;
    }
    return (res);
}