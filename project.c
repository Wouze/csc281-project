#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef unsigned long long ull;

int is_prime(long n)
{
    int i;

    for (i = 0; i <= sqrt(n); i += 2)
        if (n % i)
            return 0;

    return 0;
}

int is_primitive_root(unsigned long long g, unsigned long long n)
{
    unsigned long long i;
    unsigned long long number = 1;

    for (i = 1; i < n - 1; i++)
    {
        number *= g;

        if (number% n == 1)
            return 0;
    }

    return 1;
}

long long pow_mod2(long long g, long long exp, long long n)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return g % n;
    if (exp == 2)
        return (g * g) % n;

    return pow_mod2( pow_mod2(g, exp%2, n) * pow_mod2( pow_mod2(g, exp>>1, n)*pow_mod2(g, exp>>1, n), 1, n ), 1, n  );
}

unsigned long long pow_mod(long long x, long long y, const long long z)
{
    unsigned long long number = 1;
    while (y)
    {
        if (y & 1)  /* is_even */
            number = number * x % z;
        y >>= 1;  /* diviide 2 */
        x = (unsigned long long)x * x % z;  
    }
    return number;
}

int is_primitive_root_powmod(unsigned short g, unsigned short n)
{
    unsigned int i;

    for (i = 1; i < n - 1; i++)
    {
        if (pow_mod(g, i, n) == 1)
            return 0;
    }

    return 1;
}

int main()
{
    clock_t t;
    t = clock();
    
    int p = 40009;
    
    int count =0;
    for (int i =1; i < p; i++)
    {
        if (is_primitive_root_powmod(i, p)){
            count++;
            // printf("%d Is primitive root to %d\n", i, p);   
        }
    }

    printf("roots: %d\n", count);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
    printf("took %f seconds to execute \n", time_taken);
    
    return 0;
}


// // PRIME website
// int main() {
//     clock_t t;
//     t = clock();
//     long long o = 1;
//     long long k;
//     // int roots[1000];
//     int z = 0;
//     long long theNum = 40009; // Replace with the actual value of theNum

//     for (long long r = 2; r < theNum; r++) {
//         k = pow_mod(r, o, theNum);
//         // k = pow(r, o);
//         // k %= theNum;

//         while (k > 1) {
//             o++;
//             k *= r;
//             k %= theNum;
//         }
//         if (o == (theNum - 1)) {
//             // roots[z] = r;
//             z++;
//         }
//         o = 1;
//     }
//     printf("%d has %d primitive roots, and they are \n", theNum, z);
//     z--;

//     t = clock() - t;
//     double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
//     printf("took %f seconds to execute \n", time_taken);
    
//     // for (int y = 0; y < z; y++) {
//     //     printf("%d ", roots[y]);
//     // }

//     return 0;

// }

// PRIME website
// int main() {
//     clock_t t;
//     t = clock();
//     int o = 1;
//     int k;
//     // int roots[1000];
//     int z = 0;
//     int theNum = 10006; // Replace with the actual value of theNum

//     for (int r = 2; r < theNum; r++) {
//         k = pow(r, o);
//         k %= theNum;
//         while (k > 1) {
//             o++;
//             k *= r;
//             k %= theNum;
//         }
//         if (o == (theNum - 1)) {
//             // roots[z] = r;
//             z++;
//         }
//         o = 1;
//     }
//     printf("%d has %d primitive roots, and they are \n", theNum, z);
//     z--;

//     t = clock() - t;
//     double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
//     printf("took %f seconds to execute \n", time_taken);
    
//     // for (int y = 0; y < z; y++) {
//     //     printf("%d ", roots[y]);
//     // }

//     return 0;

// }










// JUNKK

// unsigned long pow_mod(unsigned short x, unsigned long y, unsigned short z)
// {
//     unsigned long number = 1;
//     while (y)
//     {
//         if (y & 1)
//             number = number * x % z;
//         y >>= 1;
//         x = (unsigned long long)x * x % z;
//     }
//     return number;
// }

// int is_primitive_root_powmod(unsigned long long g, unsigned long long n)
// {
//     unsigned long long i;

//     for (i = 1; i < n - 1; i++)
//     {
//         if (pow_mod(g, i, n) == 1)
//             return 0;
//     }

//     return 1;
// }
