import MyPrime
import pygamal



import time


x = 100_000_007
while not pygamal.is_prime(x):
    x+=1
    print(x, pygamal.is_prime(x))


## Define global vars ##
s = time.time()

p_glob = x # Global
if not pygamal.is_prime(p_glob):
    print("SD")
    quit(1)

x = 99_932_243 # My private key
g_glob, e_glob = pygamal.gen_keys_FAST(p_glob, x)

s = time.time() - s
print(f"Took {s} seconds to generate global vars")

s = time.time()
## Define me ##
Alice = pygamal.ElGamalEncryptor(p_glob, x, g_glob, e_glob)

## Define Bob ##
y = 98_152_663 # Bob private key
Bob = pygamal.ElGamalEncryptor(p_glob, y, g_glob, e_glob)



s = time.time() - s
print(f"Took {s} seconds to define Alice and Bob")
####### Bob want to send message to me #######
s = time.time()   

msg = 'Hi Alice!'
c1, c2 = Bob.encrypt(msg)
print(c1, c2)

s = time.time() - s
print(f"Took {s} seconds to encrypt")
####### Bob sent me (c1, c2) #######
s = time.time() 


x = Alice.decrypt(c1, c2)
s = time.time() - s
print(f"Took {s} seconds to decrypt")

print(x)

quit()
# print(dir(MyPrime))

# print((MyPrime.get_all_primitive_roots(11)))

x= 5000
y=1000050
z=10055
# print(pow(x, y, z) == MyPrime.pow_mod(x, y, z))
# print(MyPrime.pow_mod2(x, y, z))
# print(pow(x, y, z))

# s = time.time()

# for i in range(5000000):
#     # MyPrime.pow_mod2(i, i, z)
#     MyPrime.pow_mod(i, i, z)
#     # pow(x, i, z)

# s=time.time() - s
# print(f"took {s} seconds")

p = 31
p = 15
count = 0

s = time.time()
l  = []
# for i in range(1, p):
#     if MyPrime.is_primitive_root(i, p):
#         # print(f"{i}, ")
#         l.append(i)
#         pass

l = MyPrime.get_all_primitive_roots_loop(p)

print(time.time()-s)
print(len(l))
