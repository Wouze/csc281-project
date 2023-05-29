# csc281-project
This is our project at csc281 course

project supervisor: Aqil Alazimi

# Testing pygamal module

to test pygamal module, you first type this in cmd
```bash
pip install pygamal
```

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
