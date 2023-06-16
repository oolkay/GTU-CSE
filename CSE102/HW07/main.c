#include "utils.h"


int vector_amount;
int word_amount;
int temp_argc;

//vector_size=200, reads the 200
void find_vector_amount()
{
    FILE *fp = fopen("dictionary.txt", "r");
    char str[30];
    fscanf(fp, "%s", str);
    fscanf(fp, "%s", str);
    vector_amount = my_atoi(str);
    fclose(fp);
}

//num_word=1000, reads the 1000
void find_word_amount()
{
    FILE *fp = fopen("dictionary.txt", "r");
    char str[30];
    fscanf(fp, "%s", str);
    word_amount = my_atoi(str);
    fclose(fp);
}

//finds the given word's line(for ex:"example" is line "i" in dictionary.txt)
int find_line(char *str, char dict[][MAX_WORD_SIZE])
{
    for (int i = 0; i < word_amount; i++)
        if (strcmp(str, dict[i]) == 0)
            return i;
    return -1;
}

//fill the vectors array with a word's vector values
void	fill_vectors(double vectors[][vector_amount])
{
	FILE	*file = fopen(DICT, "r");
	int		i = 0;
	char	letter, str[MAX_WORD_SIZE];

	while (fscanf(file, "%c", &letter) != -1 && letter != '\n');//skips the first line
	while (i < word_amount)
    {
		fscanf(file, "%s", str);//skips the word
		for (int j = 0; j < vector_amount; j++)//reads vectors
			fscanf(file, "%lf", &vectors[i][j]);
		i++;
	}
    fclose(file);
}

//calculates the distance between given vectors
double	distance_cal(double vector1[], double vector2[])
{
	double sum = 0, temp = 0;
	for (int i = 0; i < vector_amount; i++)
    {
		temp = vector1[i] - vector2[i];
		sum += temp * temp;
		if (sum > THRESHOLD * THRESHOLD)
            return (INT_MAX);
	}
	sum = sqrt(sum);
	return (sum);
}

//this function, calculates the distance between w1 and all words,
//returns the line that has minimum distance with w1
//uses distance_cal(),find_line(),my_strcpy()
double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold)
{
	int	i = 0, line;
	double vectors[word_amount][vector_amount], temp;
    int min_line = 0;
	double sum = INT_MAX;
	line = find_line(w1, dict);
	fill_vectors(vectors);
	while (i < word_amount)
    {
		if (i != line)
        {
			temp = distance_cal(vectors[line], vectors[i]);
			if(temp < sum)
			{
				sum = temp;
				min_line = i;
			}
		}
		i++;
	}
	my_strcpy(w2, dict[min_line]);
	return (min_line);
}

//reads the words on dictionary and stores them in dict array
int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE])
{
    int i = 0;
    float tmp;
    char letter;
    FILE *fp = fopen(file_name, "r");
    char str[MAX_WORD_SIZE];
    while (fscanf(fp, "%c", &letter) != -1 && letter != '\n');
    while (i < word_amount) //runs 1000 times
    {
        fscanf(fp, "%s", str);
        if (assing_str_to_arr(dict, str, i) == -1)
        {
            fclose(fp);//if it couldnt assing to the arr control
            return (-1);//if it couldnt assing to the arr control
        }
        for (int j = 0; j < vector_amount; j++)//skipping vectors
            fscanf(fp, "%f", &tmp);

        i++;
    }
    dict[i][0] = '-';//sentinel value
    fclose(fp);
    return (i);
}


//reads from input txt and store the words in words array
int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE])
{
    int i = 0;
    int count = 0;
    char ch;
    float tmp;
    FILE *text = fopen(text_file, "r");
    char str[MAX_WORD_SIZE];
    while (fscanf(text, "%c", &ch) != -1)
    {
        if (ch != '\n' && ch != ' ')
        {
            if (check_ignore_letters(ch) == 1)//checks the letter is ignored
            {
                str[i] = ch;
                i++;
            }
        }
        else
        {
            str[i] = '\0';
            i = 0;
            if (check_is_ignored(str) == 1 && (str[0] != '\0'))//checks the word is ignored
            {
                assing_str_to_arr(words, str, count);
                count++;//counter for read words
            }
        }
    }
    words[count][0] = '-';
    fclose(text);
    return (count);
}

/* --CREATES A HISTOGRAM LIKE BELOW:
Enter word(s): car student triangle 
"car"          *
"student"      *
"triangle"     NO MATCHES
*/
int histogram(const char words[][MAX_WORD_SIZE],const int occurrences[], const char hist[][MAX_WORD_SIZE + 5 + 20])
{
    int scale = 1;
    int max = 1; 
    int size = temp_argc;
    int len;
    int flag = 0, j = 0;
    
    //finds the max occurences
    for (int i = 0; i < size-1 ; i++)
    {
        if (occurrences[i] > max && occurrences[i] != -5)
            max = occurrences[i];
    }
    //scale assing
    if (max % 20 == 0)
        scale = max / 20;
    else//scale assing
        scale = (max / 20) + 1;
    if(scale != 1)
        printf("Scale: %d\n", scale);
    //checks the hist[i] occurs in words array in order to decide print + or *
    for (int i = 0; i < temp_argc - 1; i++)
    {
        flag = 0;
        j = 0;
        while (words[j][0] != '-')
        {
            if (strcmp(words[j],hist[i]) == 0)
            {
                flag = 1;
                break;
            }
            j++;
        }
        len = my_strlen(hist[i]);//findling length of the string in order to print ' '
        printf("\"%s\"", hist[i]);
        for (int k = 0; k < 26 - len; k++)
            printf(" ");
        if (occurrences[i] == -5)
            printf("NO MATCHES");
        else if (occurrences[i] != -5)
        {
            if (flag==1)
                for (int k = 0; k < occurrences[i] / scale ; k++)
                    printf("*");
            else if(flag == 0)
                for (int k = 0; k < occurrences[i] / scale ; k++)
                    printf("+");
        }
        printf("\n");
    }
    return (scale);
}

int main(int argc, char *argv[])
{
    find_vector_amount(); //find how many vector dictionary.txt contains
    find_word_amount();   //find how many word dictionary.txt contains
    int read_nbr, word_nbr, i = 1, j = 0;
    
    //ARRAY DECLARATIONS
    char words[INPUT_MAX_WORD + 1][MAX_WORD_SIZE];
    char dict[1001][MAX_WORD_SIZE];
    char hist[argc + 1][MAX_WORD_SIZE+5+20];
    int occurence[argc-1];

    //CONTROL
    if (argc < 2)
        return (0);

    //READS TEXT AND DICT, FINDS HOW MANY WORD READ
    word_nbr = read_text(WORDS, IGNORE, words);
    read_nbr = read_dict(DICT, dict);
    temp_argc = argc;

    //CHECKS SINGLE INPUT OR NOT
    if (argc == 2)
    {
        occurence[0] = find_occurence(words, argv[1], word_nbr);
        //case: the given input occures in input.txt
        if (occurence[0] != -1)
        {
            printf("Enter word(s): %s\n\"%s\" appears in \"%s\" %d times.\n", argv[1], argv[1], WORDS, occurence[0]);
            return (0);
        }

        //case: the given input doesnt occur in input.txt
        else
        {
            int q = find_closest(argv[1], dict);
            if (q == -1) //case: there is no close word in dict.txt (because of thereshold)
            {
                printf("Enter word(s): %s\n\"%s\" is not matched in \"%s\"\n", argv[1], argv[1], WORDS);
                return (0);
            }
            occurence[0] = find_occurence(words,dict[q], word_nbr);
            if (occurence[0] != -1 ) //case: the given word doesnt occur in input but the closest occurs in input.txt
            {
                printf("Enter word(s): %s\n\"%s\" doesn't appear in \"%s\" but \"%s\" appears %d times.\n",argv[1], argv[1], WORDS, dict[q], occurence[0]);
                return (0);
            }
            else if (occurence[0] == -1)//case: the given and closest word doesnt occur in input.txt
            {
                printf("Enter word(s): %s\n\"%s\" is not matched in \"%s\"\n", argv[1], argv[1], WORDS);
                return (0);
            }
        }
    }

    //MULTIPLE INPUT
    else
    {
        int scale = 1;
        //printing arguments
        printf("Enter word(s): ");
        for (int i = 1; i < argc; i++)
            printf("%s ", argv[i]);
        printf("\n");


        for (int i = 0; i < argc - 1; i++)
        {
            occurence[i] = find_occurence(words, argv[i + 1], word_nbr);
            if (occurence[i] == -1)//case: the given word doesnt occur in input.txt
            {
                int q = find_closest(argv[i + 1], dict);
                if (q == -1)//case: there is no close word in dict.txt because of thereshold
                {
                    assing_str_to_his(hist,argv[i+1],i);//filling hist array
                    occurence[i] = -5;//error code
                }
                else//case: there is a close word
                {
                    occurence[i] = find_occurence(words, dict[q], word_nbr);
                    if (occurence[i] == -1)//case: the closest word doesnt occur in input.txt
                    {
                        occurence[i] = -5;//error code
                        assing_str_to_his(hist,argv[i+1],i);//fill hist array
                    }
                    else//the closest word occurs in input.txt
                    {
                        assing_str_to_his(hist, argv[i+1],i);//fill hist array
                        my_strcat(hist[i],"->");//fill hist array
                        my_strcat(hist[i],dict[q]);//fill hist array
                    }
                }
            }
            else //case: the given word occurs in input.txt
                assing_str_to_his(hist, argv[i+1],i);
        }
        //hist[i][0] = '-';//sentinel value
        scale = histogram(words, occurence, hist); // find scale and print histogram
    }
    return (0);

}