import my_prime
import time
import MyPrime
# Rust Python module\MyPrime>.\.venv\Scripts\activate


def is_primitive_root(g, n):
    global global_mod
    for i in range(1, n-1):

        # if MyPrime.pow_mod(g, i, n) == 1:
        #     return False
        
        if my_prime.pow_mod(g, i, n) == 1:
            return False

    return True




x=1111513223
y=111142324
z=11121232

p = 49999
# p=4007
count = 0

# print(my_prime.get_all_primitive_roots(p) == MyPrime.get_all_primitive_roots_loop(p))

s = time.time()
l  = []

# for i in range(1, p):
    # if MyPrime.is_primitive_root(i, p):
    # if my_prime.is_primitive_root(i, p):
    #     # print(f"{i}, ")
    #     l.append(i)
    #     pass

l = MyPrime.get_all_primitive_roots_loop(p)

# l = my_prime.get_all_primitive_roots_loop(p)
# print(l == l2)

# l = MyPrime.get_all_primitive_roots(p)

# l = my_prime.get_all_primitive_roots(p)

print(time.time()-s)


print(len(l))

# print(my_prime.pow_mod(x, y, z) == pow(x, y, z))