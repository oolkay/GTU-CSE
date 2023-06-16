#include "utils.h"

//read from files and updates the linkedlists when the program starts
void update_database(Book **book, Student **student)
{
    FILE *fp = fopen("books.txt", "r");
    // if the file is not found
    if (!fp)
    {
        fclose(fp);
        return ;
    }
    char isbn[20], title[20], author[20], name[20], borrowedbook[20], status;
    int year, id;
    while (fscanf(fp, "%[^,], %[^,], %[^,], %d, %c\n", isbn, title, author, &year, &status) > 0)
    {
        addBook(book, isbn, title, author, year, status, 1);
    }
    fclose(fp);

    // if the file is not found
    fp = fopen("students.txt", "r");
    if (!fp)
    {
        fclose(fp);
        return ;
    }
    while (fscanf(fp, "%[^,], %d, %s\n", name, &id, borrowedbook) > 0)
    {
        addSudent(student, name, id, borrowedbook);
    }
    fclose(fp);
}

// writes the linkedlists to the files when a change is made
void write_database_to_file(Book *book, Student *student)
{
    FILE *fp = fopen("books.txt", "w+");
    
    // if there is no book in the database
    if (book == NULL)
        return ;
    while (book != NULL)
    {
        fprintf(fp, "%s, %s, %s, %d, %c", book->isbn, book->title, book->author, book->publicYear, book->status);
        if (book->next != NULL)
            fprintf(fp, "\n");
        book = book->next;
    }
    fclose(fp);

    fp = fopen("students.txt", "w+");
    // if there is no student in the database
    if (student == NULL)
        return ;
    while (student != NULL)
    {
        fprintf(fp, "%s, %d, %s", student->name, student->id, student->borrowedbooks);
        if (student->next != NULL)
            fprintf(fp, "\n");        
        student = student->next;
    }
    fclose(fp);
}
