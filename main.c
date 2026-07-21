/******************************************************************
 * Name:Marala Vijaya Kumar Reddy
 * Date:23-06-2026
 * Title:Arbitary Precision Calculator
 *****************************************************************/
#include "header.h"
int dot_count1=0, dot_count2=0, res_count=0;

int main(int argc, char *argv[])
{
    char operation, sign;
    Dlist *head1=NULL, *tail1=NULL;
    Dlist *head2=NULL, *tail2=NULL;
    Dlist *resh=NULL, *rest=NULL;
    int len1=strlen(argv[1]), len2=strlen(argv[3]), cmp=0, res_len;
    char *ptr1=NULL, *ptr2=NULL;
    ptr1=strstr(argv[1], ".");
    if(ptr1!=NULL)
    dot_count1=strlen(ptr1 + 1);
    ptr2=strchr(argv[3], '.');
    if(ptr2!=NULL)
    dot_count2=strlen(ptr2 + 1);
    
  
    if(argc!=4)
    {
        printf("argc counting\n");
        printf("pass min 4 arg\n");
        return FAILURE;
    }
    if(validate_arg(argv)==FAILURE)
    {
        printf("validation not success\n");
        return 0;
    }
    printf("validation success\n");

    if(convert_insert_first(argv, &head1, &head2, &tail1, &tail2 )==FAILURE)
    {
        return 0;
    }
    printf("conversion and insertion successful\n");


    if(print_list(head1, tail1, dot_count1)==LIST_EMPTY)
    {
        printf("list1 empty\n");
        return 0;
    }
    if(print_list(head2, tail2, dot_count2)==LIST_EMPTY)
    {
        printf("list2 empty\n");
        return 0;
    }
    
    operation=compare_sign(argv, &sign, head1, head2);
    

    switch(operation)
    {
        /*addition*/
        case '+':
            res_len=(dot_count1>dot_count2) ? dot_count1 : dot_count2;
            printf("%d\n", res_count);
            if(addition(&head1, &tail1, &head2, &tail2, &resh, &rest)==FAILURE)
            {
                printf("addition failed\n");
                return 0;
            }
            printf("sum is:\n");
            if(sign=='-')
            printf("-");
            print_list(resh, rest, res_len);
            break;

        /*subtraction*/
        case '-':
             res_len=(dot_count1>dot_count2) ? dot_count1 : dot_count2;
            printf("performing -\n");
            cmp=compare_lists(head1, head2);
            if(cmp > 0)
            {
                subtraction(&head1, &tail1, &head2, &tail2, &resh, &rest);
            }
            else if(cmp < 0)
            {
                printf("-");
                subtraction(&head2, &tail2, &head1, &tail1, &resh, &rest);
            }
            else
            {
                insert(&resh, &rest, 0);
            }
            printf("sub is\n");
            if(sign=='-')
            printf("-");
            print_list(resh, rest, res_len);
            break;

        /*multiplication*/
        case 'x':

            res_len=dot_count1+dot_count2;
            if(multi(&head1, &tail1, &head2, &tail2, &resh, &rest)==FAILURE)
            {
                printf("multi failed\n");
                return FAILURE;
            }
            printf("multi successful\n");

            if(sign=='-')
            printf("-");
            print_list(resh, rest, res_len);
            break;

        /*division*/
        case '/':
            printf("performing /\n");

            if(head2 && head2->data == 0 && head2->next == NULL)
            {
                printf("Division by zero not possible\n");
                return 0;
            }
            res_count = dot_count1 - dot_count2;
            if(res_count < 0)
                res_count = 0;

            if(division(&head1, &tail1, &head2, &tail2, &resh, &rest) == FAILURE)
            {
                printf("division failed\n");
                return 0;
            }
            break;


    }

    


    return 0; 
}