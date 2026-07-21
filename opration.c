    #include "header.h"

    /*validating arguments like its  only contaning digits, sign and .*/
    int validate_arg(char **argv)
    {
        int flag1=1, flag2=1;
        if(argv[1]==NULL || argv[2]==NULL || argv[3]==NULL)
        {
            printf("arg failed\n");
            return FAILURE;
        }
        for(int i=0; argv[1][i]!='\0'; i++)
        {
            if(argv[1][0]=='-' || argv[1][0]=='+')
            continue;

            else if(argv[1][i]=='.')
            {
                flag1=0;
                continue;
            }

            else if((argv[1][i]<'0' || argv[1][i]>'9') )
            {
                printf("invalid argv[1]\n");
                return FAILURE;
            }
            //printf("%c\n", argv[1][i]);
        }
    
        for(int i=0; argv[3][i]!='\0'; i++)
        {
            if(argv[3][0]=='-' || argv[3][0]=='+')
            continue;

            else if(argv[3][i]=='.')
            {
                flag2=0;
                continue;
            }
            if((argv[3][i]<'0' || argv[3][i]>'9'))
            {
                printf("invalid argv[3]\n");
                return FAILURE;
            }
        }
        return SUCCESS;
   }


   /*convering char digits to integer digits and calling insert first function*/
    int convert_insert_first(char **argv, Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2)
    {
        extern int dot_count1, dot_count2;
        if(argv[2][0]!='x')
        {
        if(dot_count1>dot_count2)
        {
            int res=dot_count1-dot_count2;
            for(int i=0; i<res; i++)
            insert(head2, tail2, 0);
        }
        if(dot_count1<dot_count2)
        {
            int res=dot_count2-dot_count1;
            for(int i=0; i<res; i++)
            insert(head1, tail1, 0);
        }
    }

        for(int i=strlen(argv[1])-1; i>=0; i--)
        {
            //printf("%d", i);
            if(argv[1][i]=='.')
            continue;
            if(argv[1][i]=='-')
            continue;
            if(argv[1][i]=='+')
            continue;

            int num=argv[1][i]-'0';
            //printf("num %d\n", num);
            if(insert(head1, tail1, num)==FAILURE)
            {
                printf("insert failed\n");
                return FAILURE;
            } 
           
        }
        
        for(int i=strlen(argv[3])-1; i>=0; i--)
        {
            if(argv[3][i]=='.')
            continue;
            if(argv[3][i]=='-')
            continue;
            if(argv[3][i]=='+')
            continue;

            int num=argv[3][i]-'0';
            //printf("num %d\n", num);
            if(insert(head2, tail2, num)==FAILURE)
            {
                printf("insert failed\n");
                return FAILURE;
            } 
        }
        return SUCCESS;
    }

    /*inserting digits by insert first*/
    int insert(Dlist **head, Dlist **tail, int data)
    {
        Dlist *new=malloc(sizeof(Dlist));
        if(new==NULL)
        {
            printf("memory not allocated\n");
            return FAILURE;
        }
        new->prev=NULL;
        new->data=data;
        new->next=NULL;
        if(*tail==NULL)
        {
            *tail=new;
            *head=new;
            return SUCCESS;
        }
        (*head)->prev=new;
        new->next=(*head);
        *head=new;
        return SUCCESS;
    }

    /*performing addition*/
    int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **resh, Dlist **rest)
    {
        int carry=0;
        while(*tail1!=NULL || *tail2!=NULL)
        {
            int data1=0, data2=0, sum=0;
            if((*tail1)!=NULL)
            {
                data1=(*tail1)->data;
                *tail1=(*tail1)->prev;
            }
            if((*tail2)!=NULL)
            {
                data2=(*tail2)->data;
                *tail2=(*tail2)->prev;
            }
            sum=data1+data2+carry;
            carry=sum/10;
            sum=sum%10;
            insert(resh,rest,sum);
            
        }
        if(carry==1)
        {
            insert(resh,rest,carry);
        }
    }

    /*performing subtraction*/
    int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **resh, Dlist **rest)
    {
        int borrow=0;
        Dlist *t1= *tail1, *t2= *tail2;
        while(t1!=NULL || t2!=NULL)
        {
            int data1=0, data2=0, diff=0;
            if((t1)!=NULL)
            {
                data1=(t1)->data;
                t1=(t1)->prev;
            }
            if((t2)!=NULL)
            {
                data2=(t2)->data;
                t2=(t2)->prev;
            }
            data1 -=borrow;
            if(data1<data2)
            {
                data1 += 10;
                borrow=1;
            }
            else
            {
                borrow=0;
            }
            diff=data1-data2;
            insert(resh, rest, diff);
        }
        while(*resh && (*resh)->data == 0 && (*resh)->next)
        {
            Dlist *temp = *resh;
            *resh = (*resh)->next;
            (*resh)->prev = NULL;
            free(temp);
        }
        return SUCCESS;
    }

    /*performing multi repeatedly calling multiplication function*/
   int multi(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **resh, Dlist **rest)
   {
        int count=0, num;
        Dlist *temp1h=NULL, *temp1t=NULL, *temp2h=NULL, *temp2t=NULL;
        Dlist *t1=*tail1;
        num=(t1)->data;
        (t1)=(t1)->prev;
        multiplication(&temp1h, &temp1t, tail2, num, count);
        count++;
        while((t1)!=NULL)
        {
            num=(t1)->data;
            (t1)=(t1)->prev;
            multiplication(&temp2h, &temp2t, tail2, num, count);
            count++;
            //printf("\n\ntemp1h=%p\n\ntemp2h=%p\n\n", temp1h, temp2h);
            addition(&temp1h, &temp1t, &temp2h, &temp2t, resh, rest);
            free_and_add(&temp1h, &temp1t, &temp2h, &temp2t, resh, rest);
        }
        *resh = temp1h;
        *rest = temp1t;     
        return SUCCESS;
    }

    /*performing multiplication 1digit from 1 list to all digits from 2nd list*/
    int multiplication(Dlist **head, Dlist **tail, Dlist **tail2, int num, int count)
    {
        if(*tail2 == NULL)
        {
            return FAILURE;
        }
        Dlist *temp=*tail2;
        for(int i=0; i<count; i++)
        {
           Dlist *new = malloc(sizeof(Dlist));

        new->data = 0;
        new->next = NULL;
        new->prev = *tail;

        if(*tail == NULL)
        {
            *head = *tail = new;
        }
        else
        {
            (*tail)->next = new;
            *tail = new;
        }
        }
        int carry=0, res=0;
        while(temp!=NULL)
        {
            res=num * (temp->data) + carry;
            carry=res / 10;
            insert(head, tail, res%10);
            temp=temp->prev;
        }
        if(carry>0)
        {
            insert(head, tail, carry);
        }
        return SUCCESS;
    }

    /*freeing after one digit multiplication and adding result to frred list*/
    int free_and_add(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **resh, Dlist **rest)
    {
        Dlist *temp;
        while(*head1 != NULL)
        {
        temp = *head1;
        *head1 = (*head1)->next;
        free(temp);
        }
        *tail1=NULL;
        *head1=*resh;
        *tail1=*rest;
        *resh=NULL;
        *rest=NULL;

        while(*head2 != NULL)
        {
        temp = *head2;
        *head2 = (*head2)->next;
        free(temp);
        }
        head2 = NULL;
        *tail2 = NULL;
        return SUCCESS;
    }


    /*performing division*/
    int division(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **resh, Dlist **rest)
    {
        if (*head2 == NULL) return FAILURE;
        if ((*head2)->next == NULL && (*head2)->data == 0)
        {
            printf("Division by zero error.\n");
            return FAILURE;
        }

        Dlist *rem_h = NULL, *rem_t = NULL;
        Dlist *t1 = *head1;
        Dlist *q_reversed_h = NULL, *q_reversed_t = NULL;

        int precision = 6; 
        int calculated_decimals = 0;
        int is_fractional_part = 0;
        int total_decimal_digits = 0;

        while (t1 != NULL || (rem_h != NULL && calculated_decimals < precision))
        {
            int current_digit = 0;

            if (t1 != NULL) {
                current_digit = t1->data;
                t1 = t1->next;
            } 
            else 
            {
                if (!is_fractional_part) {
                is_fractional_part = 1;
                }
                current_digit = 0; 
                calculated_decimals++;
            }

        // 1. Bring down the digit to the tail of the remainder
            Dlist *new_node = malloc(sizeof(Dlist));
            if (!new_node) return FAILURE;
            new_node->data = current_digit;
            new_node->next = NULL;
            new_node->prev = rem_t;
            if (rem_t == NULL) rem_h = rem_t = new_node;
            else { rem_t->next = new_node; rem_t = new_node; }

            // 2. Normalize remainder
            while (rem_h && rem_h->data == 0 && rem_h->next) {
                Dlist *tmp = rem_h;
                rem_h = rem_h->next;
                rem_h->prev = NULL;
                free(tmp);
            }

            // 3. Subtract loop
            int digit = 0;
            while (compare_lists(rem_h, *head2) >= 0) {
                Dlist *tmp_h = NULL, *tmp_t = NULL;
                subtraction(&rem_h, &rem_t, head2, tail2, &tmp_h, &tmp_t);

                while (rem_h != NULL) 
                {
                    Dlist *del = rem_h;
                    rem_h = rem_h->next;
                    free(del);
                }
            rem_t = NULL;
            rem_h = tmp_h; rem_t = tmp_t;

            while (rem_h && rem_h->data == 0 && rem_h->next) 
            {
                Dlist *tmp_node = rem_h;
                rem_h = rem_h->next;
                rem_h->prev = NULL;
                free(tmp_node);
            }
            digit++;
        }

        // 4. Save the quotient digit
        insert(&q_reversed_h, &q_reversed_t, digit);
        if (is_fractional_part) {
            total_decimal_digits++;
        }

        // Stop early if remainder is perfectly 0 in fractional space
        if (is_fractional_part && rem_h && rem_h->data == 0 && rem_h->next == NULL) {
            break;
        }
    }

    // 5. Flip back to standard order
    Dlist *curr = q_reversed_h;
    while (curr != NULL) {
        insert(resh, rest, curr->data);
        Dlist *tmp = curr;
        curr = curr->next;
        free(tmp);
    }

    // 6. Trim leading zeros
    while (*resh && (*resh)->data == 0 && (*resh)->next) {
        Dlist *temp = *resh;
        *resh = (*resh)->next;
        (*resh)->prev = NULL;
        free(temp);
    }

    // Clean up remaining remainder memory
    while (rem_h != NULL) {
        Dlist *tmp = rem_h;
        rem_h = rem_h->next;
        free(tmp);
    }

    // 7. Print the results 
    printf("quotient is:\n");
    
    // Count total digits in the final quotient list
    int total_digits = 0;
    Dlist *count_ptr = *resh;
    while (count_ptr != NULL) {
        total_digits++;
        count_ptr = count_ptr->next;
    }

    int integer_digits = total_digits - total_decimal_digits;
    curr = *resh;

    // Print integer part
    for (int i = 0; i < integer_digits; i++) {
        if (curr != NULL) {
            printf("%d", curr->data);
            curr = curr->next;
        }
    }

    // Print decimal point explicitly if a fractional component exists
    if (total_decimal_digits > 0) {
        printf(".");
        // Print fractional part
        while (curr != NULL) {
            printf("%d", curr->data);
            curr = curr->next;
        }
    }
    printf("\n");

    return SUCCESS;
}   