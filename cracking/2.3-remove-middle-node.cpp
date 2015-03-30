#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string>

using namespace std;

struct node
{
    node *next;
    char data;
};

void remove_node(node* n)
{
    if (n == nullptr)
    {
        return;
    }
    else if (n->next == nullptr)
    {
        delete n;
    }
    else
    {
        node* next = n->next;

        // copy data from next to n
        n->data = next->data;

        // change the n next pointer to be next next
        n->next = next->next;

        // delete next node
        delete next;
    }
}

void run_tests()
{
    vector<node*> testCases = { nullptr };
    node* head = nullptr;
    node* n = new node();
    n->data = 'a';
    n->next = new node();
    head = n;
    testCases.push_back(n);
    n = n->next;
    n->data = 'b';
    n->next = new node();
    testCases.push_back(n);
    n = n->next;
    n->data = 'c';
    n->next = new node();
    testCases.push_back(n);
    n = n->next;
    n->data = 'd';
    n->next = new node();
    testCases.push_back(n);

    for (node* testCase : testCases)
    {
        if (testCase != nullptr)
        {
            char data = testCase->data;
            remove_node(testCase);
            node* curr = head;
            while (curr)
            {
                assert(curr->data != data);
                curr = curr->next;
            }
            printf("%c PASSED!", data);
        }
        else
        {
            remove_node(testCase);
            printf("NULL PASSED!");
        }
    }
}

int main()
{
    run_tests();
    return 0;
}