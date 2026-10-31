#include <stdio.h>
#include <time.h>

int count = 0;

long long Delannoy(int m, int n) {
    if (m == 0 || n == 0) return 1;
    count += 3; 
    return Delannoy(m - 1, n) + Delannoy(m - 1, n - 1) + Delannoy(m, n - 1);
}

double cpu_time() {
    return (double)clock() / CLOCKS_PER_SEC;
}

int main(void) {
    double prev_time = 0.0;
    int prev_count = 0;

    printf("n   DEL         RECCalls     Time (sec)  Time Ratio   Call Ratio\n");
    for (int n = 0; n < 13; n++) {
        count = 0;
        double start = cpu_time();
        long long del = Delannoy(n, n);
        double elapsed = cpu_time() - start;

        double time_ratio = (prev_time != 0) ? elapsed / prev_time : 0.0;
        double call_ratio = (prev_count != 0) ? (double)count / prev_count : 0.0;

        printf("%2d  %10lld  %11d  %10.5f  %10.2f  %10.2f\n",
               n, del, count, elapsed, time_ratio, call_ratio);

        prev_time = elapsed;
        prev_count = count;
    }
    return 0;
}
