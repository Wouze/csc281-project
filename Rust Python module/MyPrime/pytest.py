import my_prime
import time
import MyPrime


def is_primitive_root(g, n):
    global global_mod
    for i in range(1, n-1):

        if MyPrime.pow_mod(g, i, n) == 1:
            return False
        if my_prime.pow_mod(g, i, n) == 1:
            return False

    return True




x=1111513223
y=111142324
z=11121232

p = 5003
p=4007
count = 0

s = time.time()
l  = []
for i in range(1, p):
    if is_primitive_root(i, p):
        # print(f"{i}, ")
        l.append(i)
        pass

print(time.time()-s)


print(len(l))

print(my_prime.pow_mod(x, y, z) == pow(x, y, z))