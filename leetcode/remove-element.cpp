class Solution {
public:
    int removeElement(int A[], int n, int elem) {
        if (n == 0) return 0;
        
        int count = 0;
        int i = 0;
        int j = n - 1;
        while (i <= j) {
            if (A[i] == elem) {
                A[i] = A[j--];
                ++count;
            } else {
                ++i;
            }
        }
        
        return n - count;
    }
};