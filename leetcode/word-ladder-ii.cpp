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
    void getNextWords(string search, unordered_set<string> &dict, vector<string> &next) {
        next.clear();
        
        for (int i = 0; i < search.size(); ++i) {
            char letter = 'a';
            while (letter <= 'z') {
                string temp = search;
                temp[i] = letter;
                if (dict.count(temp) != 0 && search.compare(temp) != 0) {
                    next.push_back(temp);
                }
                letter++;
            }
        }
    }

    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        vector<vector<string>> found;
        int shortest = INT_MAX;
        dict.insert(end);
        queue<string> q;
        vector<string> next;
        unordered_map<string, unordered_set<string>> paths;
        string word;

        q.push(start);
        while (!q.empty()) {
            word = q.front();
            q.pop();

            if (word.compare(end) == 0) {
                break;
            }

            getNextWords(word, dict, next);
            for (string nextWord : next) {
                paths[nextWord].insert(word);
                q.push(nextWord);
            }
            dict.erase(word);
        }

        if (paths.empty()) {
            return found;
        }

        bool multiple;
        do {
            multiple = false;
            word = end;
            list<string> path;
            while (word.compare(start) != 0) {
                path.push_front(word);
                string nextWord = *paths[word].begin();
                if (paths[word].size() > 1) {
                    multiple = true;
                    paths[word].erase(nextWord);
                }
                word = nextWord;

                if (path.size() > shortest) {
                    break;
                }
            }
            path.push_front(start);

            if (path.size() <= shortest) {
                if (path.size() < shortest) {
                    found.clear();
                    shortest = path.size();
                }
                found.push_back(vector<string>(path.begin(), path.end()));
            }
        } while (multiple);

        return found;
    }
};