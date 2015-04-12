#include <stdio.h>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    void getNextWords(string search, unordered_set<string> &dict, unordered_set<string> &next) {
        next.clear();
        
        for (int i = 0; i < search.size(); ++i) {
            char letter = 'a';
            while (letter <= 'z') {
                string temp = search;
                temp[i] = letter;
                if (dict.count(temp) != 0) {
                    next.insert(temp);
                }
                letter++;
            }
        }
    }

    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        vector<vector<string>> found;
        dict.insert(end);
        queue<string> q;
        unordered_set<string> next;
        unordered_map<string, unordered_set<string>> paths;
        string word;

        q.push(start);
        while (!q.empty()) {
            word = q.front();
            q.pop();

            if (word.compare(end) == 0) {
                break;
            }

            dict.erase(word);
            getNextWords(word, dict, next);
            
            if (next.count(end) == 0) {
                for (string nextWord : next) {
                    if (paths.count(nextWord) == 0) {
                        q.push(nextWord);
                    }
                    paths[nextWord].insert(word);
                }
            }
            else {
                q.push(end);
                paths[end].insert(word);
            }
        }

        if (paths.empty()) {
            return found;
        }

        vector<string> path;
        populatePaths(end, start, paths, path, found);

        return found;
    }

    void populatePaths(
        string curr,
        string end,
        unordered_map<string, unordered_set<string>> &paths,
        vector<string> &path,
        vector<vector<string>> &found) {
        path.push_back(curr);
        if (curr.compare(end) == 0) {
            found.push_back(vector<string>(path.rbegin(), path.rend()));
            path.pop_back();
            return;
        }

        const unordered_set<string> &neighbirs = paths[curr];
        for (string neighbir : neighbirs) {
            populatePaths(neighbir, end, paths, path, found);
        }
        path.pop_back();
    }
};