#include <vector>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

//class Solution {
//public:
//    vector<string> anagrams(vector<string> &strs) {
//        unordered_map<string, map<char, int>> hash;
//        unordered_map<string, list<string>> found;
//        vector<string> result;
//        string key;
//
//        for (string w : strs) {
//            for (char c : w) {
//                hash[w][c]++;
//            }
//            getKey(hash[w], key);
//            found[key].push_front(w);
//            key.clear();
//        }
//
//        for (auto pair : found) {
//            if (pair.second.size() > 1) {
//                result.insert(result.end(), pair.second.begin(), pair.second.end());
//            }
//        }
//
//        return result;
//    }
//
//    void getKey(map<char, int> &hash, string &key) {
//        for (auto pair : hash) {
//            key += pair.first;
//            key += pair.second;
//        }
//    }
//};

class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        unordered_map<string, list<string>> found;
        vector<string> result;

        for (string w : strs) {
            string temp = w;
            sort(temp.begin(), temp.end());
            found[temp].push_front(w);
        }

        for (auto pair : found) {
            if (pair.second.size() > 1) {
                result.insert(result.end(), pair.second.begin(), pair.second.end());
            }
        }

        return result;
    }
};