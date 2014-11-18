#include <stdio.h>
#include <assert.h>
#include <vector>

using namespace std;

struct node
{
    char value;
    node* next;
};

void remove_duplicates(node* head)
{
    node* n = head;

    while (n)
    {
        node* curr = n->next;
        node* prev = n;

        while (curr)
        {
            assert(curr);
            assert(n);
            assert(prev);

            if (curr->value == n->value)
            {
                // change prev->next to point to curr->next
                prev->next = curr->next;

                // change curr->next so it does not point to any node
                curr->next = nullptr;

                // delete the curr node
                delete curr;

                // set curr to be prev
                curr = prev;
            }

            prev = curr;
            curr = curr->next;
        }

        n = n->next;
    }
}

void run_tests()
{
    vector<pair<string, string>> testCases =
    {
        { "follow up", "folw up" },
        { "hello world", "helo wrd" },
        { "", "" },
        { "aaaa", "a" }
    };

    for (auto item : testCases)
    {
        node* head = new node();
        node* curr = head;

        for (char letter : item.first)
        {
            curr->value = letter;
            curr->next = new node();
            curr = curr->next;
        }

        remove_duplicates(head);
        curr = head;

        for (int i = 0; i < item.second.size(); ++i)
        {
            assert(item.second[i] == curr->value);
            curr = curr->next;
        }

        // To make sure that the lengths are same
        assert(curr->next == nullptr);

        printf("%s PASSED\n", item.first.c_str());
    }
}

int main()
{
    run_tests();
    return 0;
}