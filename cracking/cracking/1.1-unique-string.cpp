#include <stdio.h>
#include <vector>
#include <assert.h>

using namespace std;

bool is_unique(char* str)
{
    if (str == nullptr) return true;

    for (int i = 0; i < strlen(str); ++i)
    {
        for (int j = 0; j < strlen(str); ++j)
        {
            if (i == j) continue;

            if (str[i] == str[j])
            {
                return false;
            }
        }
    }

    return true;
}

void run_tests()
{
    vector<char*> testCases = { nullptr, "", "a", "abc", "abcdeff", "aaf", "aaaaaaaaaaaaaaaaaaaaaaaaa", "qwertyuiop" };
    vector<bool> expected = { true, true, true, true, false, false, false, true };

    assert(testCases.size() == expected.size());

    for (int i = 0; i < testCases.size(); ++i)
    {
        assert(is_unique(testCases[i]) == expected[i]);
        printf("%s PASSED!\n", testCases[i]);
    }
}

int main()
{
    run_tests();
    return 0;
}