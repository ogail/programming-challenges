#include <algorithm>
#include <vector>

class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        for (vector<int> v : matrix) {
            if (std::binary_search(v.begin(), v.end(), target))
            {
                return true;
            }
        }
        
        return false;
    }
};