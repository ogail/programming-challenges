class Solution {
public:
    int lengthOfLastWord(const char *s) {
        bool space = false;
        int n = 0;
        
        while (s && *s) {
            if (*s != ' ') {
                if (space) {
                    n = 1;
                    space = false;
                } else {
                    ++n;
                }
            } else {
                space = true;
            }
            
            s++;
        }
        
        return n;
    }
};