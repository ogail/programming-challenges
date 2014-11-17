#include <stdio.h>
#include <vector>
#include <assert.h>
#include <string>

using namespace std;

char* compress(char* str)
{
    if (str == nullptr) return str;
    int length = strlen(str);
    int count = 0;
    int i;
    string compressed;
    char prev = NULL;

    for (i = 0; i < length && compressed.size() < length; ++i)
    {
        if (prev != str[i])
        {
            if (prev != NULL)
            {
                compressed += prev;
                compressed += to_string(count);
            }

            prev = str[i];
            count = 1;
        }
        else
        {
            ++count;
        }
    }

    compressed += prev;
    compressed += to_string(count);

    if (compressed.size() < length)
    {
        return strdup(compressed.c_str());
    }
    else
    {
        return str;
    }
}

void run_tests()
{
    vector<pair<char*, char*>> tests =
    {
        { nullptr, nullptr },
        { "", "" },
        { "b", "b" },
        { "aabcccccaaa", "a2b1c5a3" },
        { "abc", "abc" },
        { "aa", "aa" },
        { "aaa", "a3" },
    };

    for (auto item : tests)
    {
        if (item.first == nullptr)
        {
            compress(item.first);
            assert(item.first == item.second);
        }
        else
        {
            char* actual = compress(item.first);
            assert(strcmp(actual, item.second) == 0);
            if (actual != item.first)
            {
                delete actual;
            }
        }

        printf("%s PASSED!\n", item.first);
    }
}

int main()
{
    run_tests();
    return 0;
}