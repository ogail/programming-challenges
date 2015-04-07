#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool is_palindrome(string s) {
        string s2 = s;
        reverse(s2.begin(), s2.end());
        return s.compare(s2) == 0;
    }

    void partition_core(vector<vector<string>> &p, vector<string> &c, string s, int start) {
        //printf("invoked start=%d\n", start);
        if (start >= s.size()) {
            //printf("c is added to p\n");
            p.push_back(c);
            return;
        }

        for (int i = 1; i + start <= s.size(); ++i) {
            string x = s.substr(start, i);
            if (is_palindrome(x)) {
                vector<string> c2 = c;
                c2.push_back(x);
                //printf("%s is added to c\n", x.c_str());
                partition_core(p, c2, s, start + i);
            }
            else {
                //printf("%s is bad, clear c\n", x.c_str());
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> partitions;
        vector<string> c;
        partition_core(partitions, c, s, 0);

        return partitions;
    }
};