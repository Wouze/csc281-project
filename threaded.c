#include <stdio.h>
#include <time.h>
#include <omp.h>

long long cpow_mod(long long x, long long y, long long z)
{
    long long number = 1;
    while (y)
    {
        if (y & 1)  /* is_even */
            number = number * x % z;
        y >>= 1;  /* divide by 2 */
        x = (unsigned long long)x * x % z;
    }
    return number;
}

int cis_primitive_root(int g, int n)
{
    int i;

    for (i = 1; i < n - 1; i++)
    {
        if (cpow_mod(g, i, n) == 1)
            return 0;
    }

    return 1;
}

int main()
{
    clock_t t;
    t = clock();
    
    int p = 100;
    int count = 0;

    int o = 1;
    unsigned long long k;

    #pragma omp parallel for private(o) reduction(+:count)
    for (int r = 2; r < p; r++) {
        k = cpow_mod(r, o, p);

        while (k > 1) {
            o++;
            k *= r;
            k %= p;
        }
        if (o == (p - 1)) {
            // PyList_Append(list, PyLong_FromLong(r));
            count++;
        }
        o = 1;
    }

    printf("Count: %d\n", count);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
    printf("took %f seconds to execute \n", time_taken);
    

    return 0;
}
