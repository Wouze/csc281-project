#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "string.h"

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


int main(){

    int p_GLOBAL = 1009;  // Any large prime //
    int g_GLOBAL = cget_second_primitive_root(p_GLOBAL);  // generate g //


    int x_random_SECRET = 5;  // My Secret key //

    unsigned long long e_GLOBAL = cpow_mod(g_GLOBAL, x_random_SECRET, p_GLOBAL); // Global e //

// ########################################################### 
// ########### Transfare(e, g, p) to bob #####################
// ########################################################### 

    unsigned char* message = "Hello bob!"; // Bob's message to me! //

    int y_random_SECRET = 3;               // His random secret key //

    // Computing cypher message c1, c2[] //
    int* message_encrtpted = malloc(strlen(message) * sizeof(char));
    
    for (int i = 0; i<strlen(message); i++){
        message_encrtpted[i] = (int) message[i];
    }

    int c1 = cpow_mod(g_GLOBAL, y_random_SECRET, p_GLOBAL);

    //   msg * e^y  mod p
    //  msg mod p * e

    int* c2 = malloc(strlen(message) * sizeof(int));

    for(int i=0; i<strlen(message); i++){
        c2[i] = ((message_encrtpted[i]%p_GLOBAL) * cpow_mod(e_GLOBAL, y_random_SECRET, p_GLOBAL)) % p_GLOBAL;
    }
    
    
// ########################################################### 
// ######### Bob Transfare(c1, c2, strlen(message)) to me ####
// ########################################################### 

    int x = cpow_mod(c1, x_random_SECRET, p_GLOBAL);

    char* decrypted_message = malloc(strlen(message) * sizeof(char));

    for (int i = 0; i<strlen(message); i++){
        decrypted_message[i] = (char) ((c2[i]%p_GLOBAL) * cpow_mod(x, p_GLOBAL-2, p_GLOBAL)) % p_GLOBAL;
    }


    printf("plain: %s\n", decrypted_message);
    return 0;

}



