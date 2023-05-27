import ElGamal_c
import time


class ElGamalEncryptor:
    p_GLOBAL = 0
    g_GLOBAL = 0
    e_GLOBAL = 0
    secret = 0

    def __init__(self, p, x, g, e):
        """
        Create new instance of the encryption
        takes p and secret key
        """
        self.p_GLOBAL = p
        self.secret = x

        self.g_GLOBAL, self.e_GLOBAL = g, e

    def encrypt(self, msg):
        """
        encrypt msg using private key
        return c1, c2
        """
        c1 = ElGamal_c.gen_c1(self.g_GLOBAL, self.secret, self.p_GLOBAL)

        c2 = ElGamal_c.encrypt(msg, self.secret, self.e_GLOBAL, self.p_GLOBAL)
        return c1, c2
    
    def decrypt(self, c1, c2):
        """
        decrypt msg using c1, c2
        return msg
        """
        x_key = ElGamal_c.gen_x_key(c1, self.secret, self.p_GLOBAL)

        msg = ElGamal_c.decrypt(len(c2), *c2, x_key, self.p_GLOBAL)
        return msg

s = time.time()
## Define global vars ##
x = 54 # My private key

p_glob = 43051 # Global
g_glob, e_glob = ElGamal_c.gen_keys(p_glob, x)

s = time.time() - s
print(f"Took {s} seconds to generate global vars")

s = time.time()
## Define me ##
Alice = ElGamalEncryptor(p_glob, x, g_glob, e_glob)

## Define Bob ##
y = 43 # Bob private key
Bob = ElGamalEncryptor(p_glob, y, g_glob, e_glob)



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
