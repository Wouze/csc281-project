#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "string.h"
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

long long cpow_mod(long long x, long long y, long long z)
{
    long long number = 1;
    while (y)
    {
        if (y & 1)  /* is_even */
            number = number * x % z;
        y >>= 1;  /* diviide 2 */
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

int gcd(int a, int b)
{
    // Find Minimum of a and b
    int result = ((a < b) ? a : b);
    while (result > 0) {
        if (a % result == 0 && b % result == 0) {
            break;
        }
        result--;
    }
 
    // Return gcd of a and b
    return result;
}

int cget_second_primitive_root(int p){

    int i, count =0;
    for(i=1; i<p; i++){
        if (cis_primitive_root(i, p)){
            // printf("%d\n", i);
            count++;
            if (count==2) return i;
        }
    }

}
int cget_th_primitive_root(int p, int n){

    int i, count =0;
    for(i=1; i<p; i++){
        if (cis_primitive_root(i, p)){
            // printf("%d\n", i);
            count++;
            if (count==n) return i;
        }
    }

}
int cget_num_primitive_root(int p, int n){

    int i, count =0;
    for(i=1; i<p; i++){
        if (cis_primitive_root(i, p)){
            // printf("%d\n", i);
            count++;
            if (i==n) return count;
        }
    }

}

unsigned long long long_pow(long long base, long long exp){
    unsigned long long number =1;

    for (int i = 0; i<exp; i++)
        number *= base;

    return number;
}
long bigMod(long  a, long  b, long c) {
    if (a == 0 || b == 0) {
        return 0;
    }
    if (a == 1) {
        return b;
    }
    if (b == 1) {
        return a;
    } 

    // Returns: (a * b/2) mod c
    long a2 = bigMod(a, b / 2, c);

    // Even factor
    if ((b & 1) == 0) {
        // [((a * b/2) mod c) + ((a * b/2) mod c)] mod c
        return (a2 + a2) % c;
    } else {
        // Odd exponent
        // [(a mod c) + ((a * b/2) mod c) + ((a * b/2) mod c)] mod c
        return ((a % c) + (a2 + a2)) % c;
    }
}

// int main(){
//     int p = 1009;  // Any large prime //
//     int g = cget_second_primitive_root(p);  // generate g //

//     printf("%d\n", g);
//     printf("%d\n", cget_num_primitive_root(p, cget_th_primitive_root(p,100)));

//     int a_SECRET = 32;  // Any large number less than p //
//     int b_SECRET = 46;  // Any large number less than p //

//     // prepare to send to other party

//     int a_exchange = cpow_mod2(g, a_SECRET, p);  
//     int b_exchange = cpow_mod2(g, b_SECRET, p);

//     // Each party send the exchange to the other

//     /// transfare

//     // get shared secret key

//     int a_SHARED_KEY = cpow_mod2(b_exchange, a_SECRET, p);
//     int b_SHARED_KEY = cpow_mod2(a_exchange, b_SECRET, p);


//     printf(a_SHARED_KEY==b_SHARED_KEY?"YES\n":"NO\n");
//     printf("the shared key is : %d\n", a_SHARED_KEY);

//     unsigned char* message = "Hello bob!"; // Message to send to b! //

//     // Map function will be ASCII //
//     int y_random = rand() % (p-1) + 1; // random y from G //
//     printf("The y_random variable is: %d\n", y_random);
//     // Computing c1, c2 //

//     printf("plain: %c\n", message[0]);


//     unsigned long long c1 = long_pow(g, y_random);
//     unsigned long long c2 = cget_th_primitive_root(p, (int)message[0]) * a_SHARED_KEY;

//     // send (c1, c2) to bob //

//     // Bob recive (c1, c2), decrpting it now //

//     unsigned long long SHARED_KEY_INVERSE = long_pow(c1, p-b_SECRET);

//     unsigned long long decrypted_message = c2*SHARED_KEY_INVERSE;

//     decrypted_message = cget_num_primitive_root(p, decrypted_message);
    
//     printf("decrypted: %d\n", decrypted_message);
//     char let = (char)decrypted_message;

//     printf("%c", let);

//     return 0;
// }


int main(){
    int p = 1009;  // Any large prime //
    int g = cget_second_primitive_root(p);  // generate g //

    printf("%d\n", cget_num_primitive_root(p, cget_th_primitive_root(p,100)));

    int x_random_SECRET = 5;

    printf("gcd: %d, %d\n", g, x_random_SECRET);

    unsigned long long e = cpow_mod(g, x_random_SECRET, p);

//################################################################

    // do{
    //     y_random_SECRET = rand() % (p-9) + 9; // random y from G //
    //     y_random_SECRET = cget_th_primitive_root(p, y_random_SECRET);
    // }while(y_random_SECRET!=p && gcd(p, y_random_SECRET) == 1);
    // printf("gcd: %d, %d\n", g, y_random_SECRET);

    unsigned char* message = "Hello bob!"; // Message to send to b! //

    int y_random_SECRET = 3;

    // Map function will be ASCII //
    // int y_random_SECRET = rand() % (p-1) + 1; // random y from G //
    
    // unsigned long long s_SHARED = long_pow(g, y_random_SECRET);

    // Computing c1, c2 //

    int msg=16;

    unsigned long long c1 = cpow_mod(g, y_random_SECRET, p);
    // unsigned long long c2 = cget_th_primitive_root(p, (int)message[0]) * s_SHARED;
    // unsigned long long c2 = bigMod((int)msg, long_pow(e, y_random_SECRET), p);
    //   msg * e^y  mod p
    //  msg mod p * e
    unsigned long long c2 = ((msg%p) * cpow_mod(e, y_random_SECRET, p)) % p;
    
    printf("plain: %c\n", msg);

    // send (c1, c2) back to me //

    unsigned long long x = cpow_mod(c1, x_random_SECRET, p);
    // unsigned long long new_m = bigMod(c2, long_pow(x, p-2), p);
    unsigned long long new_m = ((c2%p) * cpow_mod(x, p-2, p)) % p;
    // printf("The y_random variable is: %d\n", y_random);

    printf("plain: %c\n", new_m);
    printf("\n\n\n\n\n");   
    // s_SHARED = long_pow(g, x_random_SECRET); 

    unsigned long long SHARED_KEY_INVERSE = long_pow(c1, p-x_random_SECRET);

    unsigned long long decrypted_message = c2*SHARED_KEY_INVERSE;

    decrypted_message = cget_num_primitive_root(p, decrypted_message);

    
    printf("decrypted: %d\n", decrypted_message);
    char let = (char)decrypted_message;

    printf("%c", let);

    // int a_exchange = cpow_mod2(g, a_SECRET, p);  
    // int b_exchange = cpow_mod2(g, b_SECRET, p);



    // Each party send the exchange to the other

    /// transfare

    // get shared secret key

    // int a_SHARED_KEY = cpow_mod2(b_exchange, a_SECRET, p);
    // int b_SHARED_KEY = cpow_mod2(a_exchange, b_SECRET, p);


    // printf(a_SHARED_KEY==b_SHARED_KEY?"YES\n":"NO\n");
    // printf("the shared key is : %d\n", a_SHARED_KEY);




    // Bob recive (c1, c2), decrpting it now //




    return 0;



}



