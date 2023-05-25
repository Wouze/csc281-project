#include "Python.h"

int cis_prime(int n)
{
  int last = (int) sqrt(n) + 1; 

  for (int j = 2; j <= last; ++j)
    if (n % j == 0)
      return 0;

  return 1;
}

long long cpow_mod2(long long g, long long exp, long long n)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return g % n;
    if (exp == 2)
        return (g * g) % n;

    return cpow_mod2( cpow_mod2(g, exp%2, n) * cpow_mod2( cpow_mod2(g, exp>>1, n)*cpow_mod2(g, exp>>1, n), 1, n ), 1, n  );
}

int cis_primitive_root(int g, int n)
{
    int i;

    for (i = 1; i < n - 1; i++)
    {
        if (cpow_mod2(g, i, n) == 1)
            return 0;
    }

    return 1;
}

int cget_second_primitive_root(int p){

    int i, count =0;
    for(i=1; i<p; i++){
        if (cis_primitive_root(i, n)){
            count++;
            if (count==2) return i;
        }
    }

}

int main(){

    int p = 1009;
    int g;

}