#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

struct node
{
    node * nxt;
    int v;
};

void partition_linked_list(node * c, node * a)
{
    assert(c);
    int i = 0;
    int j = 0;
    node * p = c;
    while (p != a && ++i) p = p->nxt;
    assert(p && (p->v == a->v));
    
    while (c != nullptr)
    {
        if (j < i)
        {
            // before a
            // TODO: complete solution
        }
    }
}

void run_tests()
{
    srand(time(nullptr));
    int count = 6;

    node * h = new node();
    h->v = rand();
    node * c = h;
    node * a = nullptr;
    int k = rand() % count;

    for (int i = 0; i < count; ++i)
    {
        c->nxt = new node();
        c->nxt->v = rand();
        c = c->nxt;

        if (i == k)
        {
            a = c;
        }
    }

    partition_linked_list(h, a);
    printf("%d\n", a->v);

    while (h)
    {
        printf("%d->", h->v);
        h = h->nxt;
    }

    printf("null\n");
}

int main()
{
    run_tests();
    return 0;
}