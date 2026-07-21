#include "header.h"

/*comparing lists and returning which one is highest*/
int compare_lists(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;

    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    while(temp1)
    {
        len1++;
        temp1 = temp1->next;
    }

    while(temp2)
    {
        len2++;
        temp2 = temp2->next;
    }

    if(len1 > len2)
        return 1;

    if(len1 < len2)
        return -1;

    while(head1 && head2)
    {
        if(head1->data > head2->data)
            return 1;

        if(head1->data < head2->data)
            return -1;

        head1 = head1->next;
        head2 = head2->next;
    }

    return 0;
}

/*comparing signs and retun sign as a character*/
char compare_sign(char *argv[], char *sign, Dlist *head1, Dlist *head2)
{
    // 1. Determine actual signs of the numbers
    int is_neg1 = (argv[1][0] == '-');
    int is_neg2 = (argv[3][0] == '-');
    char op = argv[2][0];
    
    int cmp = compare_lists(head1, head2);

    // Default signs
    *sign = '+';

    if (op == 'x' || op == '/') 
    {
        // For multiplication/division: signs match -> +, signs differ -> -
        if (is_neg1 ^ is_neg2) 
            *sign = '-';
        return op;
    }
    
    if (op == '+') 
    {
        if (!is_neg1 && !is_neg2) 
        {
            *sign = '+'; 
            return '+';
        }
        if (is_neg1 && is_neg2) 
        {
            *sign = '-'; 
            return '+'; 
        }
        if (is_neg1 && !is_neg2) 
        { 
            if (cmp >= 0) 
            { 
                *sign = '-'; 
                return '-'; 
            }
            else 
            { 
                *sign = '+'; 
                return '-'; 
            }
        }
        if (!is_neg1 && is_neg2) 
        {
            if (cmp >= 0) 
            { 
                *sign = '+'; 
                return '-'; 
            }
            else 
            { 
                *sign = '-'; 
                return '-'; 
            }
        }
    }
    
    if (op == '-') 
    {
        if (!is_neg1 && !is_neg2) 
        {
            if (cmp >= 0) 
            { 
                *sign = '+'; 
                return '-'; 
            }
            else 
            { 
                *sign = '-'; 
                return '-'; 
            }
        }
        if (is_neg1 && is_neg2) 
        { 
            if (cmp >= 0) 
            {
                *sign = '-'; 
                return '-'; 
            }
            else 
            {
                *sign = '+'; 
                return '-'; 
            }
        }
        if (is_neg1 && !is_neg2) 
            *sign = '-'; return '+';
    
        if (!is_neg1 && is_neg2)  
            *sign = '+'; return '+';
    }

    return op; 
}