#include <stdio.h>
#include <vector>
#include <assert.h>
#include <string>

using namespace std;

bool is_rotation(string str, string rot)
{
    if (str.empty()) return true;

    rot = rot.append(rot);
    return rot.find(str) != std::string::npos;
}

void run_tests()
{
    vector<pair<string, string>> testCases =
    {
        { "", "" },
        { "a", "a" },
        { "ab", "ba" },
        { "water", "rwate" },
        { "bottle", "lebott" },
        { "aaaaaaaaaaaaa", "aaaaaaaaaaaaa" },
        { "abc", "acb" }
    };

    vector<bool> expected = { true, true, true, true, true, true, false };

    assert(testCases.size() == expected.size());

    for (int i = 0; i < testCases.size(); ++i)
    {
        bool result = is_rotation(testCases[i].first, testCases[i].second);
        assert(result == expected[i]);
        printf("%s PASSED\n", testCases[i].first);
    }
}

int main()
{
    run_tests();
    return 0;
}