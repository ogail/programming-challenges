#include <vector>
#include <stdio.h>
#include <string>
#include <assert.h>
#include <unordered_set>

using namespace std;

void remove_duplicates(string str, string &output)
{
    unordered_set<char> found;

    for (char letter : str)
    {
        if (found.count(letter) == 0)
        {
            // it's better to use a string that uses linked list in the underlying implementation
            // so that appending is O(1)
            output += letter;
            found.insert(letter);

            if (output.size() == 26)
            {
                // We pretty much covered all English characters, break!
                break;
            }
        }
    }
}

void run_tests()
{
    vector<pair<string, string>> testCases =
    {
        { "hello world", "helo wrd" },
        { "aaaa", "a" },
        { "abc", "abc" },
        { "", "" },
        { "qwertyuiopasdfghjklzxcvbnm", "qwertyuiopasdfghjklzxcvbnm" }
    };

    for (auto item : testCases)
    {
        string actual;
        remove_duplicates(item.first, actual);
        assert(actual.compare(item.second) == 0);
    }
}

int main()
{
    run_tests();
    return 0;
}