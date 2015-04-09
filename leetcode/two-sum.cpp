#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        unordered_map<int, int> hash;

        for (int i = 0; i < numbers.size(); ++i) {
            int number = target - numbers[i];

            if (hash.find(number) != hash.end())
            {
                return{ hash[number] + 1, i + 1 };
            }

            hash[numbers[i]] = i;
        }

        return {};
    }
};