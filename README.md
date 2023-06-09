# csc281-project
This is our project at csc281 course

project supervisor: Aqil Alazimi

# Testing pygamal module

to test pygamal module, you first type this in cmd
```bash
pip install pygamal
```
You will need Visual Studio C++ develpor tools to compile the libraries


then, create any python file, and put this starter code:

```python
from pygamal import *

## Define global vars ##
x = 23_456  # My private key

p_glob = 100_003 # Global Prime
g_glob, e_glob = gen_keys(p_glob, x)

## Define me ##
Alice = ElGamalEncryptor(p_glob, x, g_glob, e_glob)

## Define Bob ##
y = 65_432 # Bob private key
Bob = ElGamalEncryptor(p_glob, y, g_glob, e_glob)

####### Bob want to send message to me #######
msg = 'Hi Alice!'
c1, c2 = Bob.encrypt(msg)
print("Plain message:", msg)
print("Encrypted message:",c1, c2)

####### Bob sent me (c1, c2) #######
msg_decrypted = Alice.decrypt(c1, c2)
print("Decrypted message:", msg_decrypted)

```

This will print:
```
Plain message: Hi Alice!
Encrypted message: 86251 [48807, 8675, 21692, 81563, 23209, 8675, 79610, 55965, 59871, 21692]
Decrypted message: Hi Alice!
```

# Fast key generation
The bottle neck for the code is the key generation, it takes the most time, even with it being coded in C.

The code for gen_keys() uses our PowMod function to find primitive roots, and for some big numbers, it takes long time.

There exsist a website that has another algorithm of doing so, [Link for the page](http://www.bluetulip.org/2014/programs/primitive.html). we implemented it in gen_keys_FAST(), which is faster than our solution

But still, generating keys for the prime 1_000_000_007 takes around 10 seconds!
That made me search for better algorithm, and I found one!, [link for the paper](https://cp-algorithms.com/algebra/primitive-root.html#implementation).
This last one is implemented under gen_keys_FASTEST(), and the same prime takes literally 0.000 seconds!
