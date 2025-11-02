#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_STACK_SIZE 10
#define MAX_CHARS_IN_STRING 10

typedef struct {
    char data[MAX_STACK_SIZE][MAX_CHARS_IN_STRING];
    int top;
} Stack;

void init_stack(Stack* s)
{
    s-> top = -1;
}

void push(Stack* s, char value[])
{
    if(s->top == MAX_STACK_SIZE - 1)
    {
        printf("Stack Overflow!!!");
        return;
    }
    s->top++;
    strcpy(s->data[s->top], value);

}

void pop(Stack *s, char* deleting_value)
{

    if(s->top == -1)
    {
        printf("Stack Underflow!!!");
        return;
    }

    strcpy(deleting_value, s->data[s->top]);

    s->top--;

    return;
}

bool is_operator(char *str)
{

    // switch statements in c only support integral types like int, char, enum etc...
    if(!strcmp(str, "+") || !strcmp(str, "-") || !strcmp(str, "*") || !strcmp(str, "/"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_higher_or_same_preced(char *op1, char *op2)
{
    if(!strcmp(op1, "("))
    return false;
    int op1_prec = !strcmp(op1, "+") || !strcmp(op1, "-") ? 1 : 2;
    int op2_prec = (!strcmp(op2, "+") || !strcmp(op2, "-")) ? 1 : 2;

    return op1_prec >= op2_prec;
}

bool is_value(char * str)
{
    for(int i=0; i < strlen(str); i++)
    {
        if(!(str[i] >= 48 && str[i] <= 57))
        {
            // accounting for negative values
            if(i == 0 && str[i] == '-')
            continue;

            return false;
        }
    }
    return true;
}

int convert_to_int(char *str)
{
    int result = 0;

    int sign = 1;
    int i = 0;
    if(str[0] == '-')
    {
        sign = -1;
        i = 1; // if the value is negative, return value
    }
    for(; i < strlen(str); i++)
    {
        result = result * 10; 
        result = result + (str[i] - '0');
    }
    return result * sign;
}


char* convert_to_str(int val)
{
    static char str_buffer[MAX_CHARS_IN_STRING]; 
    
    // convert int to string with sprintf method
    sprintf(str_buffer, "%d", val);
    
    // Return the pointer to the persistent static buffer.
    return str_buffer;
}

char* perform_operation(Stack *s, char *op)
{
    int result = 0;
    char operand1[MAX_CHARS_IN_STRING];
    pop(s, operand1);
    char operand2[MAX_CHARS_IN_STRING];
    pop(s, operand2);

    int val1 = convert_to_int(operand1);
    int val2 = convert_to_int(operand2);

    if(!strcmp(op, "+"))
    {
        result = val2 + val1;
    }
    else if(!strcmp(op, "-"))
    {
        result = val2 - val1; // since, when popping, the values are reversed, this becomes issue for non commutative operations
    }
    else if(!strcmp(op, "*"))
    {
        result = val2 * val1;
    }

    return convert_to_str(result);
}

int main()
{
    printf("Day 5 - Daily Coding!\n");
    char input[100];

    Stack operand_stack;
    Stack operator_stack;

    do
    {
        init_stack(&operand_stack);
        init_stack(&operator_stack);

        char* result;
        printf("input: ");
        
        // scanf reads the characters till the whitespace and also, the characters after the whitespace will stay in the input buffer
        // Use fgets to read the entire line, including spaces
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle read error or EOF
            return 1; 
        }
        // Remove the newline character that fgets leaves at the end (if present)
        input[strcspn(input, "\n")] = '\0'; // to calculate the length of the initial segment of one string (str1) that consists entirely of characters NOT found in a second string (str2)

        char *delimiter = " ";
        char *token = strtok(input, delimiter);
        while(token != NULL)
        {
            int result = 0;
            if(token[strlen(input)-1] == '\n')
            {
                token[strlen(input)-1] = '\0';
            }

            if(is_operator(token))
            {
                if(operator_stack.top != -1 && has_higher_or_same_preced(operator_stack.data[operator_stack.top], token))
                {
                    char* value;
                    char operation[MAX_CHARS_IN_STRING];
                    pop(&operator_stack, operation);

                    value = perform_operation(&operand_stack, operation); // perform operation with the top two elements of the stack

                    push(&operand_stack, value);
                } 

                push(&operator_stack, token);
            }
            else if(is_value(token))
            {
                push(&operand_stack, token);
            }
            else if(!strcmp(token, "("))
            {
                push(&operator_stack, token);
            }
            else if(!strcmp(token, ")"))
            {
                while(strcmp(operator_stack.data[operator_stack.top], "("))
                {
                    char* value;
                    char operation[MAX_CHARS_IN_STRING];
                    pop(&operator_stack, operation);

                    value = perform_operation(&operand_stack, operation);

                    push(&operand_stack, value);
                }

                char popped_operand[MAX_CHARS_IN_STRING]; // not needed
                pop(&operator_stack, popped_operand); // remove the "(" from the stack top.
            }


            // 5 + 3 * 2 - 9 * 4 - 1 + 3
            // 5 + 3 
            
            token = strtok(NULL, delimiter);
        }

        char *operation_result;
        // at the end, perform all the operations from the top
        while(operator_stack.top != -1)
        {
            char* value;
            char operation[MAX_CHARS_IN_STRING];
            pop(&operator_stack, operation);

            value = perform_operation(&operand_stack, operation);

            push(&operand_stack, value);
            
        }

        if (operand_stack.top != -1) 
        {
            char final_result_str[MAX_CHARS_IN_STRING];
            pop(&operand_stack, final_result_str);
        
            // Convert the string result back to an integer
            int final_int_result = convert_to_int(final_result_str); 

            printf("The final result is %d\n", final_int_result);
        }
        else 
        {
            printf("Error: No valid calculation performed.\n");
        }
    }
    while(strcmp(input, "q")); // returns 0, if the strings are same. 
    // if it is not "q", the loop will run.

}