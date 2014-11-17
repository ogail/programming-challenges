#include <stdio.h>
#include <vector>
#include <assert.h>

using namespace std;

void replace_space(char* str, int length)
{
    if (str == nullptr || length == 0) return;
    
    // Do not do anything if the string does not have spaces
    if (strlen(str) == length) return;

    int end = strlen(str) - 1;

    for (int i = length - 1; i >= 0; --i)
    {
        if (str[i] == ' ')
        {
            str[end--] = '0';
            str[end--] = '2';
            str[end--] = '%';
        }
        else
        {
            str[end--] = str[i];
        }
    }
}

void run_tests()
{
    vector<pair<pair<char*, int>, char*>> tests =
    {
        { { nullptr, 0 }, nullptr },
        { { "", 0 }, "" },
        { { " --", 1 }, "%20" },
        { { "  ----", 2 }, "%20%20" },
        { { "ab", 2 }, "ab" },
        { { "a --", 2 }, "a%20" },
        { { "a b c----", 5 }, "a%20b%20c" },
        { { "Mr John Smith----", 13 }, "Mr%20John%20Smith" }
    };

    for (auto item : tests)
    {
        if (item.first.first == nullptr)
        {
            replace_space(item.first.first, item.first.second);
            assert(item.first.first == item.second);
        }
        else
        {
            char* str = strdup(item.first.first);
            replace_space(str, item.first.second);
            assert(strcmp(str, item.second) == 0);
        }
        
        printf("%s PASSED!\n", item.first.first);
    }
}

int main()
{
    run_tests();
    return 0;
}