#include <stack>
#include <assert.h>

using namespace std;

class queue
{
public:
    void enqueue(int item)
    {
        s1.push(item);
    }

    int dequeue()
    {
        int frontItem = front();

        if (frontItem != INT_MIN)
        {
            s2.pop();
            return frontItem;
        }
        else
            throw new exception("no items in list to dequeue");
    }

    int front()
    {
        if (s2.empty())
        {
            while (!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }

        // INT_MN indicates that no elements found
        int front = INT_MIN;

        if (!s2.empty())
        {
            front = s2.top();
        }

        return front;
    }

private:
    stack<int> s1;
    stack<int> s2;
};

int main()
{
    queue myQ;

    for (int i = 0; i < 5; ++i)
    {
        myQ.enqueue(i);
    }

    assert(myQ.front() == 0);

    for (int i = 0; i < 3; ++i)
    {
        assert(myQ.dequeue() == i);
    }

    assert(myQ.front() == 3);

    myQ.enqueue(5);

    for (int i = 3; i < 6; ++i)
    {
        assert(myQ.dequeue() == i);
    }

    return 0;
}