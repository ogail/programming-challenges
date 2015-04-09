int singleNumber(int A[], int n) {
    int i, r;
    r = A[0];
    for (i = 1; i < n; ++i) {
        r ^= A[i];
    }
    
    return r;
}