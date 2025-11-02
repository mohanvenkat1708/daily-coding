#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;

Node* create_node(int val);
int add_last(int val);
Node* get_last();
void print_list();
void remove_value(int val);
void reverse_list();

struct Node{
    int data;
    struct Node* next;
};

Node* head;


int main()
{
    head = create_node(10); // if this is not there, the code will still work
    add_last(20);
    add_last(30);
    add_last(40);
    add_last(50);
    add_last(60);

    print_list();

    // remove_value(20);
    // printf("After removing 20\n");
    // remove_value(20); //again remove 20. should get message!
    reverse_list();
    print_list();
}

Node* create_node(int val)
{
    // Node n; // int a
    // n.data = 50;
    // printf("%d", n.data);

    Node* node = (Node*)malloc(sizeof(Node)); // int* a 
    if(node == NULL)
    {
        return NULL;
    }
    node->data = val; 
    node->next = NULL;
    return node;
}

Node* get_last()
{
    if(head == NULL)
    {
        printf("Cannot get last node! The list is empty.\n");
    }
    Node* node = head;
    while(node->next != NULL)
    {
        node = node->next;
    }
    return node;
}
// 1 -> 2 -> 3 -> 4 -> null
int add_last(int val)
{
    // create the yet to be last node
    Node* node = create_node(val);

    if(node == NULL)
    {
        printf("Cannot add, because: cannot create node!\n");
        return 1;
    }

    // get the current last node and assign the node to the next of the last node.
    Node* last_node = get_last();
    if(last_node == NULL)
    {
        printf("the list is null. Hence, adding the node as head!\n");
        head = node;
    }
    else
    {
        last_node->next = node;
    }
    return 0;
}

void print_list()
{
    printf("printing list\n");
    Node* node = head;
    while(node != NULL)
    {
        printf("%d\n", node->data);
        node = node->next;
    }
}

void remove_value(int val)
{
    if(head == NULL)
    {
        printf("Cannot remove. The list is empty!");
        return;
    }
    
    if(head->data == val)
    {
        Node* temp = head;
        head = head->next;
        free(temp);
        printf("value removed\n");
        return;
    }

    Node* prev_node = head;
    Node* next_node = prev_node->next;
    while(next_node->next != NULL)
    {
        if(next_node->data == val)
        {
            break;
        }
        prev_node = next_node;
        next_node = next_node->next;
    }

    if(next_node->data != val)
    {
        printf("Value not present!\n");
        return;
    }
    else{
        prev_node->next = next_node->next;
        free(next_node);
        printf("Value removed\n");
    }
}

void reverse_list()
{
    Node* prev = NULL; // from the start, there will be no previous node for head
    Node* current = head;
    Node* next = NULL; // from the start, we don't know whether head will have any next element
    
    /*
        1 -> 2 | 2 -> 1 -> null
        1
        1 -> 2-> 3 -> 4 -> 5 -> null
        5 -> 4 -> 3 -> 2 -> 1

    p   c    n
        p    c   n
             p   c   n
                 p   c    n
                     p    c    n
                          p    c   n
    */ 


    while(current != NULL)
    {
        // save the next element
        next = current->next;

        // detach 
        current->next = prev;

        // move the previous and
        prev = current;
        current = next;
    }
    head = prev;

}
// yet to implement:

// 1. Add at first
// 2. insert at index
// 3. reverse the list
// 4. count nodes
// 5. find value
// 6. clear list

/*
    Things learnt:
    1. Even though we can have structs statically (without dynamic allocation), that will have the scope only for the function 
    whose stack will be popped after the function call ends.
    2. typedef: used to create an alias for data types. Ex: typedef int abc; // Now it will be called abc
    Normally struct types are called fully like: struct <struct-name> // using typedef, we can have this as a single name.
    using typedef is same as, writing the alias name after the {} block of the stack.
    3. the dot '.' notion of accessing the values is when we have a statically defined struct.
    when we have a struct pointer, we can use '->' notation instead of using like this: *struct_pointer.data, we use: struct_pointer->data
*/