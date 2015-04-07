#include <stdio.h>

struct node
{
    node *nxt;
    int data;
};

node* find_element(node* head, unsigned int pos)
{
    int length = 0;
    node *curr = head;
    while (curr = curr->nxt) ++length;
    int target = length - pos;
    curr = head;
    while (curr && target--) curr = curr->nxt;

    return curr;
}

void print_list(node* curr)
{
    while (curr)
    {
        printf("%d ", curr->data);
        curr = curr->nxt;
    }

    printf("\n");
}

int main()
{
    node* head = new node();
    head->data = 20;

    node *curr = head;

    for (int i = 0; i < 5; ++i)
    {
        node *next = new node();
        next->data = i;
        curr->nxt = next;
        curr = next;
    }

    print_list(head);
    node* element = find_element(head, 20);
    if (element)    printf("%d\n", element->data);
    element = find_element(head, 0);
    if (element) printf("%d\n", element->data);

    return 0;
}