#ifndef UTILS_H
# define UTILS_H

# define MAX_WORD_SIZE 12 + 1 // + 1 for '\0'
# define IGNORE "./ignore.txt" // ignore.txt path
# define DICT "./dictionary.txt" // dictionary.txt path
# define THRESHOLD 20 // threshold value
# define INPUT_MAX_WORD 300000 // max word number in input.txt
# define WORDS "./input.txt" // input.txt path

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>


//MY UTIL FUNCTIONS
int my_strlen(const char *str); //similar function of strlen
int my_atoi(char *str); //similar to atoi
int assing_str_to_arr(char arr[][MAX_WORD_SIZE], char str[], int indx); //assing str to given index of arr
int check_ignore_letters(char ch); //check the letter is ignored forex: (‘.’, ‘:’, ‘;’, ‘,’, ‘\’’, ‘”’, etc.)
int check_is_ignored(char word[]); //check the word is ignored
int find_occurence(char words[][MAX_WORD_SIZE], char *str, int read_nbr);//finds occurences of given word in input.txt
double distance_cal(double vector1[], double vector2[]);//calculates the distance between given vectors
int find_line(char *str, char dict[][MAX_WORD_SIZE]);//finds the line of the word in dictionary.txt
int find_closest(char *str, char dict[][MAX_WORD_SIZE]);//find closest word
void fill_vectors(double vectors[][200]); //fill vecctor array
void find_vector_amount();//finds how many vectors each word has
void find_word_amount();//finds how many word in dictionary.txt
double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold);//calculates the dissimilarity
int assing_str_to_his(char his[][MAX_WORD_SIZE+20+5], char str[], int indx);//assing the argument to the hist array
void my_strcat(char *dest, char *src);
void my_strcpy(char arr[MAX_WORD_SIZE], char str[]);
//MY UTIL FUNCTIONS


//MANDATORY FUNCTIONS
double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold);
int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE]);
int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE]);
int histogram(const char words[][MAX_WORD_SIZE],const int occurrences[], const char hist[][MAX_WORD_SIZE + 5 + 20]);
//MANDATORY FUNCTIONS


#endif