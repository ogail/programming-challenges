#include <unordered_set>
#include <stdio.h>

using namespace std;

struct node
{
    node *next;
    node *prev;
    int data;
};

void remove_duplicates(node* curr)
{
    unordered_set<int> elements;

    while (curr)
    {
        if (elements.count(curr->data) != 0)
        {
            node *old = curr;
            curr = old->next;
            if (old->prev) old->prev->next = old->next;
            if (old->next) old->next->prev = old->prev;
            old->prev = nullptr;
            old->next = nullptr;
        }
        else
        {
            elements.insert(curr->data);
            curr = curr->next;
        }
    }
}

void remove_duplicates_no_buffer(node* head)
{
    node* curr = head;

    while (curr)
    {
        node* temp = curr->next;

        while (temp)
        {
            if (temp->data == curr->data)
            {
                node *old = temp;
                temp = old->next;
                if (old->prev) old->prev->next = old->next;
                if (old->next) old->next->prev = old->prev;
                old->prev = nullptr;
                old->next = nullptr;
            }
            else
            {
                temp = temp->next;
            }
        }
        curr = curr->next;
    }
}

void print_list(node* curr)
{
    while (curr)
    {
        printf("%d ", curr->data);
        curr = curr->next;
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
        next->data = i % 3;
        next->prev = curr;
        curr->next = next;
        curr = next;
    }

    print_list(head);

    remove_duplicates(head);
    print_list(head);
    
    remove_duplicates_no_buffer(head);
    print_list(head);

    return 0;
}