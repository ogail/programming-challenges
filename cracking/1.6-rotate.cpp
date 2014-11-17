#include <stdio.h>
#include <vector>
#include <assert.h>

using namespace std;

void rotate(vector<vector<int>> &m)
{
    int n = m.size();

    for (int layer = 0; layer < n / 2; ++layer)
    {
        int first = layer;
        int last = n - 1 - layer;
        for (int i = first; i < last; ++i)
        {
            int offset = i - first;

            // save top
            int top = m[first][i];

            // left -> top
            m[first][i] = m[last - offset][first];

            // bottom -> left
            m[last - offset][first] = m[last][last - offset];

            // right -> bottom
            m[last][last - offset] = m[i][last];

            // top -> right
            m[i][last] = top;
        }
    }
}

void run_tests()
{
    vector<vector<int>> test =
    {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    vector<vector<int>> expected =
    {
        { 7, 4, 1 },
        { 8, 5, 2 },
        { 9, 6, 3 }
    };

    rotate(test);

    assert(test.size() == expected.size());

    for (int i = 0; i < test.size(); ++i)
    {
        for (int j = 0; j < test.size(); ++j)
        {
            assert(test[i][j] == expected[i][j]);
        }
    }

    printf("sample test case PASSED!\n");
}

int main()
{
    run_tests();
    return 0;
}