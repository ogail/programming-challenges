#include <stdio.h>
#include <vector>
#include <assert.h>

using namespace std;

void reverse(char* str)
{
    if (str == nullptr) return;

    for (int i = 0, j = strlen(str) - 1; i < j; ++i, --j)
    {
        char t = str[i];
        str[i] = str[j];
        str[j] = t;
    }
}

void run_tests()
{
    vector<pair<char*, char*>> testCases =
    {
        { nullptr, nullptr },
        { "", "" },
        { "a", "a" },
        { "ab", "ba" },
        { "abc", "cba" },
        { "abcd", "dcba" },
        { "aaaaaaaaaaaaa", "aaaaaaaaaaaaa" }
    };

    for (auto item : testCases)
    {
        if (item.first == nullptr)
        {
            reverse(item.first);
            assert(item.second == nullptr);
        }
        else
        {
            char* str = strdup(item.first);
            reverse(str);
            assert(strcmp(str, item.second) == 0);
        }

        printf("%s PASSED\n", item.first);
    }
}

int main()
{
    run_tests();
    return 0;
}