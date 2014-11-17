#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;

bool is_permutation(char* str1, char* str2)
{
    if (str1 == nullptr && str2 == nullptr)
    {
        return true;
    }
    else if (str1 == nullptr || str2 == nullptr)
    {
        return false;
    }
    else
    {
        string first = string(str1);
        string second = string(str2);
        sort(first.begin(), first.end());
        sort(second.begin(), second.end());

        return first.compare(second) == 0;
    }
}

void run_tests()
{
    vector<pair<char*, char*>> tests = 
    {
        { nullptr, nullptr },
        { "", "" },
        { "a", "a" },
        { "ab", "ab" },
        { "ba", "ab" },
        { "abc", "bca" },
        { "a", "b" },
        { "qwe", "qwh" },
        { nullptr, "a" },
        { "", "q" }
    };
    vector<bool> expected = { true, true, true, true, true, true, false, false, false, false };

    assert(tests.size() == expected.size());

    for (int i = 0; i < tests.size(); ++i)
    {
        assert(is_permutation(tests[i].first, tests[i].second) == expected[i]);
        printf("%s & %s PASSED!\n", tests[i].first, tests[i].second);
    }
}

int main()
{
    run_tests();
    return 0;
}