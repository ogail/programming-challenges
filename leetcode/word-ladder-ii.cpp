#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <climits>
#include <assert.h>

using namespace std;

class Solution {
public:
    unordered_map<string, vector<string>> hash;

    vector<string> getNextWords(string search, unordered_set<string> &dict) {
        vector<string> next;
        for (string word : dict) {
            int diff = 0;
            int i = 0;
            while (diff < 2 && i < search.size()) {
                diff += search[i] != word[i];
                ++i;
            }

            if (diff == 1) {
                next.push_back(word);
            }
        }

        return next;
    }

    void findLaddersCore(
        string current,
        string end,
        unordered_set<string> &dict,
        vector<vector<string>> &found,
        vector<string> path,
        int &size) {
        if (current.compare(end) == 0) {
            if (path.size() <= size) {
                if (path.size() < size) {
                    found.clear();
                    size = path.size();
                }

                found.push_back(vector<string>(path.begin(), path.end()));
            }

            return;
        }

        if (path.size() >= size) {
            return;
        }

        vector<string> next = hash[current];
        unordered_set<string> search(path.begin(), path.end());
        for (string word : next) {
            if (search.count(word) == 0) {
                vector<string> candidate = path;
                candidate.push_back(word);
                findLaddersCore(word, end, dict, found, candidate, size);
            }
        }
    }

    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        vector<vector<string>> found;
        int size = INT_MAX;
        dict.insert(end);

        for (string word : dict) {
            hash[word] = getNextWords(word, dict);
        }
        hash[start] = getNextWords(start, dict);

        findLaddersCore(start, end, dict, found, { start }, size);
        return found;
    }
};