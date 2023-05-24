import MyPrime
import time

print(dir(MyPrime))

print(len(MyPrime.get_all_primitive_roots(5003)))

x= 5000
y=1000050
z=10055
print(pow(x, y, z) == MyPrime.pow_mod(x, y, z))
print(MyPrime.pow_mod2(x, y, z))
print(pow(x, y, z))

s = time.time()

for i in range(5000000):
    # MyPrime.pow_mod2(i, i, z)
    MyPrime.pow_mod(i, i, z)
    # pow(x, i, z)

s=time.time() - s
print(f"took {s} seconds")

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
