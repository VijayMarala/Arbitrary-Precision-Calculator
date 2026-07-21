#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SUCCESS 1
#define FAILURE -1
#define LIST_EMPTY -2

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
}Dlist;

/*validating arguments*/
int validate_arg(char **);

/*converts char to integer and inserting in linked list*/
int convert_insert_first(char ** , Dlist **, Dlist **, Dlist **, Dlist **);

/*digits inserting at first*/
int insert(Dlist **, Dlist **, int);

/*printing output list*/
int print_list(Dlist *, Dlist *, int);

/*performing addition calculation*/
int addition(Dlist **, Dlist **, Dlist **, Dlist **, Dlist **, Dlist **);

/*performing subtraction*/
int subtraction(Dlist **, Dlist **, Dlist **, Dlist **, Dlist **, Dlist **);

/*comparing lists which one is highest*/
int compare_lists(Dlist *, Dlist *);

/*performing multiplication
->multi repeatedly calling with each digit
->multiplication performs each digit of 1 ll to all digits of 2nd ll
->once done then free one temp ll and copy reults list to that temp list*/
int multi(Dlist **, Dlist **, Dlist **, Dlist **, Dlist **, Dlist **);
int multiplication(Dlist **, Dlist **, Dlist **, int , int);
int free_and_add(Dlist **, Dlist **, Dlist **, Dlist **, Dlist **, Dlist **);

/*performing division*/
int division(Dlist **, Dlist **, Dlist **, Dlist **, Dlist **, Dlist **);

/*performing sign*/
char compare_sign(char **, char *, Dlist *, Dlist *);


#endif