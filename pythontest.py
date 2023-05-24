from numba import prange
from numba import jit, njit
from functools import cache
import numpy as np
import time

# Our library
import MyPrime
# is_prime(int n)
# pow_mod(int x, int y, int z)
# pow_mod2(int x, int y, int z)
# is_primitive_root(int g, int n)

global_mod = 0


@njit()
def powmod_glob(base, n):
    if n == 1:
        return base
    elif n % 2 == 0:
        return (powmod_glob(base, n/2)**2) % global_mod
    else:
        return ((powmod_glob(base, (n-1)/2)**2)*base) % global_mod


# @cache
@njit()
def powmod(base, n, mod):
    if n == 1:
        return base
    elif n % 2 == 0:
        return (powmod(base, n/2, mod)**2) % mod
    else:
        return ((powmod(base, (n-1)/2, mod)**2)*base) % mod



def is_primitive_root(g, n):
    global global_mod
    for i in range(1, n-1):

        # Benchmark at p = 3257 with 1440 result

        # if pow(g, i, n) == 1:  # 3.829s
        #     return False

        # if powmod(g, i, n) == 1: # 2.730s
        #     return False

        # global_mod = n
        # if powmod_glob(g, i) == 1:  # 2.576s
        #     return False

        # if powmod(g, i, n) == 1:  # 1.481s w: @njit @ is_primitive_root(g, n)
        #     return False

        if MyPrime.pow_mod(g, i, n) == 1:
            return False

    return True


s = time.time()
p = 40009
count = 0
l  = []
# for i in range(1, p):
#     if MyPrime.is_primitive_root(i, p):
#         # print(f"{i}, ")
#         l.append(i)
#         pass

l = MyPrime.get_all_primitive_roots(p)

print(time.time()-s)
print(len(l))

# at p=10007
# in C, took 5.1s
# in pytohn, took 13.4s
