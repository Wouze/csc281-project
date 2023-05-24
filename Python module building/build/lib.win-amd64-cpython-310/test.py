import MyPrime
import time


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
