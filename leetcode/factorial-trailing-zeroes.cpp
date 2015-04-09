int trailingZeroes(int n) {
    int count = 0;
    long long i;
    for (i = 5; n / i > 0; i *= 5)
        count += n / i;

    return count;
}