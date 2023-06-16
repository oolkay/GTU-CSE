#include "utils.h"

// freeing the book struct
void freeBook(Book **book)
{
    Book *temp;
    while (*book != NULL)
    {
        temp = *book;
        *book = (*book)->next;
        free(temp->isbn);
        free(temp->title);
        free(temp->author);
        free(temp);
    }
}

// checking whether the given book is on database or not
int checkBook(Book *book, char *isbn)
{
    while (book != NULL)
    {
        // if the book is found
        if (strcmp(book->isbn, isbn) == 0)
            return 1;
        book = book->next;
    }
    return 0;
}

// pringing the booklist reversely
void reverseBookList(Book **book)
{
    Book *reverselist = NULL;
    Book *tmp = NULL;

    tmp = *book;
    while (tmp != NULL)
    {
        addBook(&reverselist, tmp->isbn, tmp->title, tmp->author, tmp->publicYear, tmp->status, 0);
        tmp = tmp->next;
    }
    freeBook(book);
    *book = reverselist;
    printBooks(*book);
}

// swapping the nodes in order to sort them
void swap_node(Book *node1, Book *node2)
{
    //initializing a temporary node
    Book *tmp = (Book *)malloc(sizeof(Book));
    tmp->isbn = (char *)malloc(sizeof(char) * strlen(node1->isbn));
    tmp->title = (char *)malloc(sizeof(char) * strlen(node1->title));
    tmp->author = (char *)malloc(sizeof(char) * strlen(node1->author));

    //coppies the node1 to the temporary node
    strcpy(tmp->isbn, node1->isbn);
    strcpy(tmp->title, node1->title);
    strcpy(tmp->author, node1->author);
    tmp->publicYear = node1->publicYear;
    tmp->status = node1->status;

    //coppies the node2 to the node1
    strcpy(node1->isbn, node2->isbn);
    strcpy(node1->title, node2->title);
    strcpy(node1->author, node2->author);
    node1->publicYear = node2->publicYear;
    node1->status = node2->status;

    //coppies the temporary node to the node2
    strcpy(node2->isbn, tmp->isbn);
    strcpy(node2->title, tmp->title);
    strcpy(node2->author, tmp->author);
    node2->publicYear = tmp->publicYear;
    node2->status = tmp->status;

    free(tmp->author);
    free(tmp->title);
    free(tmp->isbn);
    free(tmp);
}

// printing the books
void printBooks(Book *book)
{
    printf(CYN);// CYN is defined in utils.h, it is a macro for cyan color
    printf("┌─────────────────────────────────────────────────────BOOKS─────────────────────────────────────────────────────┐\n");
    if (!book)
    {
        printf(RED);// RED is defined in utils.h, it is a macro for red color
        printf("##No books found\n");
    }
    while (book != NULL)
    {
        printf(WHT);// WHT is defined in utils.h, it is a macro for white color
        printf("## ISBN: %s, TITLE: %s, AUTHOR: %s, PUBLICATION YEAR: %d, STATUS: %c\n", book->isbn, book->title, book->author, book->publicYear, book->status);
        book = book->next;
    }
    printf(CYN);
    printf("└───────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n\n");

}

void searchBooks(Book *book, int searchChoice, char *searchvalue)
{
    int flag = 1;
    while (book != NULL)
    {
        if (searchChoice == 0)//search by isbn
        {
            // if the book is found
            if (strcmp(book->isbn, searchvalue) == 0)
            {
                printf(GRN);
                printf("\n\nisbn: %s title: %s author: %s publication year: %d\n", book->isbn, book->title, book->author, book->publicYear);
                flag = 0;
            }
        }
        else if (searchChoice == 1)//search by author
        {
            // if the book is found
            if (strcmp(book->author, searchvalue) == 0)
            {
                printf(GRN);
                printf("\n\nisbn: %s title: %s author: %s publication year: %d\n", book->isbn, book->title, book->author, book->publicYear);
                flag = 0;
            }
        }
        else if (searchChoice == 2)//search by title
        {
            // if the book is found
            if (strcmp(book->title, searchvalue) == 0)
            {
                printf(GRN);
                printf("\n\nisbn: %s title: %s author: %s publication year: %d\n", book->isbn, book->title, book->author, book->publicYear);
                flag = 0;
            }
        }
        book = book->next;
    }
    if (flag == 1)
    {
        printf(RED);
        printf("\n\n##No books found with given criteria\n");
    }
}

void filterAndSortBooks(Book *book, int filterChoice, char* filter, int sortChoice)
{
    Book *tmp = NULL;
    Book *tmp2 = NULL;
    if (filterChoice == 0)//filter by author
    {
        printf(MAG);// MAG is defined in utils.h, it is a macro for magenta color
        printf("\n\nBOOKS WROTE BY %s", filter);
        while (book != NULL)
        {
            // if the book is found
            if (strcmp(book->author, filter) == 0)
                addBook(&tmp, book->isbn, book->title, book->author, book->publicYear, book->status, 1);
            book = book->next;
        }
    }
    else if (filterChoice == 1)//filter by publication year
    {
        printf(MAG);// MAG is defined in utils.h, it is a macro for magenta color
        printf("BOOKS PUBLISHED IN %s", filter);
        while (book != NULL)
        {
            // if the book is found
            if (book->publicYear == atoi(filter))
                addBook(&tmp, book->isbn, book->title, book->author, book->publicYear, book->status, 1);
            book = book->next;
        }
    }
    if (!tmp)
    {
        printf(RED);// RED is defined in utils.h, it is a macro for red color
        printf("\nNO BOOKS FOUND\n\n");
        return;
    }
    tmp2 = tmp;
    //printBooks(tmp);
    if (sortChoice == 0)//sort by title
    {
        printf(MAG);// MAG is defined in utils.h, it is a macro for magenta color
        printf(" AND SORTED BY TITLE\n");
        while (tmp->next != NULL)
        {
            if (strcmp(tmp->title, tmp->next->title) > 0)
            {
                swap_node(tmp, tmp->next);
                tmp = tmp2;
            }
            else
                tmp = tmp->next;
        }
    }
    else if (sortChoice == 1)//sort by author
    {
        printf(MAG);// MAG is defined in utils.h, it is a macro for magenta color
        printf(" AND SORTED BY AUTHOR\n");
        while (tmp->next != NULL)
        {
            if (strcmp(tmp->author, tmp->next->author) > 0)
            {
                swap_node(tmp, tmp->next);
                tmp = tmp2;
            }
            else
                tmp = tmp->next;
        }
    }
    else if (sortChoice == 2)//sort by publication year
    {
        printf(MAG);// MAG is defined in utils.h, it is a macro for magenta color
        printf(" AND SORTED BY PUBLICATION YEAR\n");
        while (tmp->next != NULL)
        {
            if (tmp->publicYear > tmp->next->publicYear)
            {
                swap_node(tmp, tmp->next);
                tmp = tmp2;
            }
            else
                tmp = tmp->next;
        }
    }
    printBooks(tmp2);
}

void updateBook(Book **book, char* isbn, char* feature, char* value)
{
    Book *tmp = *book;
    while (tmp != NULL && strcmp(tmp->isbn, isbn) != 0)
        tmp = tmp->next;
    // if the book is not found
    if (tmp == NULL)
    {
        printf(RED);// RED is defined in utils.h, it is a macro for red color
        printf("\n---->Book not found\n");
        return;
    }
    // if the book is found and the feature that will be updated is title
    if (strcmp(feature, "title") == 0)
    {
        // copying the new title to the book
        printf(GRN);// GRN is defined in utils.h, it is a macro for green color
        printf("\n---->The book's title updated successfully\n");
        strcpy(tmp->title, value);
        return ;
    }
    // if the book is found and the feature that will be updated is author
    else if (strcmp(feature, "author") == 0)
    {
        // copying the new author to the book
        printf(GRN);// GRN is defined in utils.h, it is a macro for green color
        printf("\n---->The book's author updated successfully\n");
        strcpy(tmp->author, value);
        return ;
    }
    // if the book is found and the feature that will be updated is publication year
    else if (strcmp(feature, "publicationYear") == 0)
    {
        // copying the new publication year to the book
        printf(GRN);// GRN is defined in utils.h, it is a macro for green color
        printf("\n---->The book's publication year updated successfully\n");
        tmp->publicYear = atoi(value);
        return ;
    }
    // invalid feature
    else
    {
        printf(RED);// RED is defined in utils.h, it is a macro for red color
        printf("\n---->Feature not found, Invalid feature\n");
    }
}

void deleteBook(Book **book, char *isbn)
{
    Book *tmp = *book;
    Book *prev = NULL;
    // there is no books on list
    if (!*book)
    {
        printf(RED);// RED is defined in utils.h, it is a macro for red color
        printf("There is no books on list\n");
        return ;
    }
    // if the book is the first node
    if (tmp != NULL && strcmp(tmp->isbn, isbn) == 0)
    {
        *book = tmp->next;
        free(tmp->author);
        free(tmp->title);
        free(tmp->isbn);
        free(tmp);
        return;
    }
    while (tmp != NULL && strcmp(tmp->isbn, isbn) != 0)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    // if the book is not found
    if (tmp == NULL)
    {
        printf(RED);// RED is defined in utils.h, it is a macro for red color
        printf("There is no book with this isbn\n");
        return ;
    }
    prev->next = tmp->next;
    free(tmp->author);
    free(tmp->title);
    free(tmp->isbn);
    free(tmp);
}

void addBook(Book **book, char* isbn, char* title, char* author,
            int publicationYear, char status, int method)
{
    if (checkBook(*book, isbn) == 1)
    {
        printf(RED);// RED is defined in utils.h, it is a macro for red color
        printf("A book with this isbn is already on the list\n");
        return ;
    }
    // controlling the parameters
    if (!isbn || !title || !author)
        return ;
    // creating a new node
    Book *new_node = (Book *)malloc(sizeof(Book));
    new_node->isbn = (char *)malloc(sizeof(char) * strlen(isbn) + 1);
    new_node->title = (char *)malloc(sizeof(char) * strlen(title) + 1);
    new_node->author = (char *)malloc(sizeof(char) * strlen(author) + 1);
    new_node->next = NULL;

    //MALLOC CONTROLS
    if (!new_node || !new_node->isbn || !new_node->title || !new_node->author)
        return ;

    // copying the parameters to the new node
    strcpy(new_node->isbn, isbn);
    strcpy(new_node->title, title);
    strcpy(new_node->author, author);
    new_node->status = status;
    new_node->publicYear = publicationYear;
    if (method == 1) //add_end
    {
        // if the list is empty
        if (!*book)
            *book = new_node;
        // if the list is not empty
        else
        {
            Book *tmp = *book;
            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = new_node;
        }
    }
    else if (method == 0)//add front if method = 0
    {
        new_node->next = *book;
        *book = new_node;
    }
}