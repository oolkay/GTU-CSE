#ifndef UTILS_H
# define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

typedef struct s_book
{
    char *isbn;
    char *title;
    char *author;
    int publicYear;
    char status;
    struct s_book *next;
}Book;

typedef struct s_student
{
    char *name;
    int id;
    char *borrowedbooks;
    struct s_student *next;
}Student;


//BOOK FUNCTIONS
void addBook(Book **book, char* isbn, char* title, char* author,int publicationYear, char status, int method);
void deleteBook(Book **book, char *isbn);
void updateBook(Book **book, char* isbn, char* feature, char* value);
void filterAndSortBooks(Book *book, int filterChoice, char* filter, int sortChoice);
void printBooks(Book *book);
void searchBooks(Book *book, int searchChoice, char* searchValue);
void reverseBookList(Book **book);
void searchBooks(Book *book, int searchChoice, char* searchValue);

//UTIL BOOK FUNCTIONS
void swap_node(Book *node1, Book *node2);//for sorting
int checkBook(Book *book, char *isbn);//for debug

//STUDENT FUNCTIONS
void addSudent(Student **student, char *name, int id, char *borrowedbook);
void deleteStudent(Student **student, char *isbn);
void studentBorrowedBooks(Student *student, int id);
void printStudents(Student *student);//for debugging

//FILE FUNCTIONS
void update_database(Book **book, Student **student);//to keep the structs up to date with the files
void write_database_to_file(Book *book, Student *student);//to keep file up to date with the structs

//FREE FUNCTIONS
void freeStudent(Student **student);//free student struct
void freeBook(Book **book);//free book struct

#endif
