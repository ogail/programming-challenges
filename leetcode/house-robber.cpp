#include <vector>
#include <algorithm> 

using namespace std;

class Solution {
public:
    int rob(vector<int> &num) {
        vector<int> table(num.size() + 2, 0);

        for (int i = 0; i < num.size(); ++i)  {
            int j = i + 2;
            table[j] = max(table[j - 1], num[i] + table[j - 2]);
        }

        return table.back();
    }
};