#include "utils.h"

// comparing the isbn with all the elements of book struct
// if it is found, changing book status to 'a' which means available and deleting the student
void returnBook(Book *book, char *isbn, Student **student)
{
    while (book != NULL)
    {
        // if the book is found
        if (strcmp(book->isbn, isbn) == 0)
        {
            // if the book is borrowed
            if (book->status == 'b')
            {
                book->status = 'a';
                deleteStudent(student, isbn);
                printf(GRN);//GRN IS DEFINED IN utils.h, IT IS A MACRO FOR GREEN COLOR
                printf("---->Book(isbn: %s) returned successfully\n\n", isbn);
                return;
            }
            // if the book is not borrowed
            else
            {
                printf(RED);//RED IS DEFINED IN utils.h, IT IS A MACRO FOR RED COLOR
                printf("---->Book(isbn: %s) is not borrowed\n\n", isbn);
                return;
            }
        }
        book = book->next;
    }
    // if the book is not found
    if (!book)
    {
        printf(RED);//RED IS DEFINED IN utils.h, IT IS A MACRO FOR RED COLOR
        printf("---->Book(isbn: %s) is not found\n\n", isbn);
    }
}

// comparing the isbn with all the elements of book struct
// if it is found and the status of the book is 'a', changing book status to 'b' which means borrowed and adding the student
void borrowBook(Book *book, char* isbn, Student **student)
{
    // if the book is not found
    if (checkBook(book, isbn) == 0)
    {
        printf(RED); // RED IS DEFINED IN utils.h, IT IS A MACRO FOR RED COLOR
        printf("----->Book is not found\n\n");
        return ;
    }
    char name[20];
    int id;
    printf("Enter the student's name: ");
    scanf(" %[^\n]", name);
    printf("Enter the student's id: ");
    scanf("%d", &id);
    while (book != NULL)
    {
        // if the book is found
        if (strcmp(book->isbn, isbn) == 0)
        {
            // if the book is available
            if (book->status == 'a')
            {
                book->status = 'b';
                addSudent(student, name, id, isbn);
                printf(GRN); //GRN IS DEFINED IN utils.h, IT IS A MACRO FOR GREEN COLOR
                printf("----->Book borrowed successfully\n\n");
                return ;
            }
            // if the book is not available
            else
            {
                printf(RED); //RED IS DEFINED IN utils.h, IT IS A MACRO FOR RED COLOR
                printf("----->Book is not available\n\n");
                return ;
            }
        }
        book = book->next;
    }
}

void printMenu()
{
    printf(BLU); //BLU IS DEFINED IN utils.h, IT IS A MACRO FOR BLUE COLOR
    printf("\n\n┌───────────────────────────┐\n");
    printf("│1- Add a book              │\n");
    printf("│2- Delete a book           │\n");
    printf("│3- Update a book           │\n");
    printf("│4- Filter and sort books   │\n");
    printf("│5- Reverse book list       │\n");
    printf("│6- Search book             │\n");
    printf("│7- Borrow a book           │\n");
    printf("│8- Return a book           │\n");
    printf("│9- Print books             │\n");
    printf("│10- Print student's book   │\n");
    printf("│11- Exit                   │\n");
    printf("└───────────────────────────┘\n\n");
}

int main()
{
    Book *book = NULL;
    Student *student = NULL;

    update_database(&book, &student);
    int i = 1;
    while (i != 11)
    {
        char isbn[20], title[20], feature[20], value[20], author[20], filter[20], status;
        int year, id, filterchoice, sortchoice, method, choice;
        printMenu();
        printf("Please select an operation: ");
        scanf("%d", &i);
        switch(i)
        {
            case 1:
                //SCANNING INPUT FROM USER
                printf("\nEnter the book's isbn: ");
                scanf(" %[^\n]", isbn);
                printf("Enter the book's title: ");
                scanf(" %[^\n]", title);
                printf("Enter the book's author: ");
                scanf(" %[^\n]", author);
                printf("Enter the book's year: ");
                scanf("%d", &year);
                printf("Enter the book's status: ");
                scanf(" %c", &status);
                printf("Enter the adding method: ");
                scanf("%d", &method);
                
                //ADDING BOOK TO THE DATABASE AND WRITING THE STRUCT TO THE FILE
                addBook(&book, isbn, title, author, year, status, method);
                write_database_to_file(book, student);
                break;

            case 2:
                //SCANNING INPUT FROM USER
                printf("\nEnter the book's isbn: ");
                scanf(" %[^\n]", isbn);

                //DELETING BOOK FROM THE DATABASE AND WRITING THE STRUCT TO THE FILE
                deleteBook(&book, isbn);
                write_database_to_file(book, student);
                break;

            case 3:
                //SCANNING INPUT FROM USER
                printf("\nEnter the book's isbn: ");
                scanf(" %[^\n]", isbn);
                printf("Enter the feature: ");
                scanf(" %[^\n]", feature);
                printf("Enter the value: ");
                scanf(" %[^\n]", value);

                //UPDATING BOOK FROM THE DATABASE AND WRITING THE STRUCT TO THE FILE
                updateBook(&book, isbn, feature, value);
                write_database_to_file(book, student);
                break;

            case 4:
                //SCANNING INPUT FROM USER
                printf("\nEnter the filter choice (0->author, 1->p.year): ");
                scanf("%d", &filterchoice);
                printf("Enter the filter: ");
                scanf(" %[^\n]", filter);
                printf("Enter the sort choice (0->title, 1->author, 2->p.year): ");
                scanf("%d", &sortchoice);

                //FILTERING AND SORTING BOOKS
                filterAndSortBooks(book, filterchoice, filter, sortchoice);
                break;
            
            case 6:
                //SCANNING INPUT FROM USER
                printf("\nEnter the your seach choice(0->isbn, 1->author, 2->title): ");
                scanf("%d", &choice);

                if (choice == 0)
                {
                    printf("Enter the book's isbn: ");
                    scanf(" %[^\n]", isbn);
                    //SEARCHING BOOK
                    searchBooks(book, choice, isbn);
                }
                else if (choice == 1)
                {
                    printf("Enter the book's author: ");
                    scanf(" %[^\n]", author);
                    //SEARCHING BOOK
                    searchBooks(book, choice, author);
                }
                else if (choice == 2)
                {
                    printf("Enter the book's title: ");
                    scanf(" %[^\n]", title);
                    //SEARCHING BOOK
                    searchBooks(book, choice, title);
                }
                break;

            case 5:
                //REVERSING BOOK LIST
                reverseBookList(&book);
                write_database_to_file(book, student);
                break;

            case 7:
                //SCANNING INPUT FROM USER
                printf("\nEnter the book's isbn: ");
                scanf(" %[^\n]", isbn);

                //BORROWING BOOK AND WRITING THE STRUCT TO THE FILE
                borrowBook(book, isbn, &student);
                write_database_to_file(book, student);
                break;

            case 8:
                //SCANNING INPUT FROM USER  
                printf("\nEnter the book's isbn: ");
                scanf(" %[^\n]", isbn);

                //RETURNING BOOK AND WRITING THE STRUCT TO THE FILE
                returnBook(book, isbn, &student);
                write_database_to_file(book, student);
                break;

            case 9:
                //PRINTING BOOKS
                printBooks(book);
                break;

            case 10:
                //SCANNING INPUT FROM USER
                printf("\nEnter the student's id: ");
                scanf("%d", &id);

                //PRINTING STUDENT'S BORROWED BOOKS
                studentBorrowedBooks(student, id);
                break;

            case 11:
                //FREEING THE MEMORY AND EXITING THE PROGRAM
                freeStudent(&student);
                freeBook(&book);
                exit (0);
                break;
            default:
                printf("invalid operation\n");
                break;
        }
    }
}
