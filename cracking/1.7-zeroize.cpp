#include <stdio.h>
#include <vector>
#include <assert.h>

using namespace std;

void zeroize(vector<vector<int>> &m)
{
    vector<pair<int, int>> zeros;

    for (int i = 0; i < m.size(); ++i)
    {
        for (int j = 0; j < m[i].size(); ++j)
        {
            if (m[i][j] == 0)
            {
                // scan entire row
                for (int k = 0; k < m[i].size(); ++k)
                {
                    zeros.push_back({ i, k });
                }

                for (int k = 0; k < m.size(); ++k)
                {
                    zeros.push_back({ k, j });
                }
            }
        }
    }

    for (auto item : zeros)
    {
        m[item.first][item.second] = 0;
    }
}

void zeroize_optimized(vector<vector<int>> &m)
{
    vector<bool> row;
    vector<bool> column;

    row.resize(m.size());
    column.resize(m[0].size());

    for (int i = 0; i < m.size(); ++i)
    {
        for (int j = 0; j < m[i].size(); ++j)
        {
            if (m[i][j] == 0)
            {
                row[i] = true;
                column[j] = true;
            }
        }
    }

    for (int i = 0; i < m.size(); ++i)
    {
        for (int j = 0; j < m[i].size(); ++j)
        {
            if (row[i] || column[j])
            {
                m[i][j] = 0;
            }
        }
    }
}

void run_tests()
{
    vector<vector<int>> test =
    {
        { 1, 0, 3 },
        { 4, 5, 6 },
        { 7, 0, 9 }
    };

    vector<vector<int>> expected =
    {
        { 0, 0, 0 },
        { 4, 0, 6 },
        { 0, 0, 0 }
    };

    //zeroize(test);
    zeroize_optimized(test);

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