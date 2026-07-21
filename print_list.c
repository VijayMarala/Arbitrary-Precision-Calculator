#include "header.h"

int print_list(Dlist *head, Dlist *tail, int res_len)
{
    if (head == NULL)
    {
        return LIST_EMPTY;
    }

    /*Counting  total number of nodes (digits) in the result list*/
    int total_digits = 0;
    Dlist *temp = head;
    while (temp != NULL)
    {
        total_digits++;
        temp = temp->next;
    }

    int dot_at_position = total_digits - res_len;

    /*Print the list and inject the dot*/
    temp = head;
    int count = 0;
    
    while (temp != NULL)
    {
        if (count == 0 && dot_at_position <= 0)
        {
            printf("0.");
        }
        else if (count == dot_at_position && res_len > 0)
        {
            printf(".");
        }

        printf("%d", temp->data);
        temp = temp->next;
        count++;
    }
    
    printf("\n");
    return SUCCESS;
}