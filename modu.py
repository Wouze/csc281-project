from pygamal import *
import time
s=time.time()

## Define global vars ##
x = 999995713  # My private key

p_glob = 1_000_000_007 # Global Prime
g_glob, e_glob = gen_keys_FAST(p_glob, x)

print(f"GEN_KEYS took: {time.time()-s}")
s=time.time()
## Define me ##
Alice = ElGamalEncryptor(p_glob, x, g_glob, e_glob)

## Define Bob ##
y = 999997279 # Bob private key
Bob = ElGamalEncryptor(p_glob, y, g_glob, e_glob)

####### Bob want to send message to me #######
msg = 'Hi Alice!'
c1, c2 = Bob.encrypt(msg)
print("Plain message:", msg)
print("Encrypted message:",c1, c2)

####### Bob sent me (c1, c2) #######
msg_decrypted = Alice.decrypt(c1, c2)
print("Decrypted message:", msg_decrypted)


print(f"ENC/DEC took: {time.time()-s}")