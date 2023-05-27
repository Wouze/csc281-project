import ElGamal_c

p = 1009


m = 'Hello'

class ElGamalEncryptor:
    p_GLOBAL = 0
    g_GLOBAL = 0
    e_GLOBAL = 0
    secret = 0

    def __init__(self, p, x):
        """
        Create new instance of the encryption
        takes p and secret key
        """
        self.p_GLOBAL = p
        self.secret = x

        self.g_GLOBAL, self.e_GLOBAL = ElGamal_c.gen_keys(p, x)

    def encrypt(self, msg):
        """
        encrypt msg using private key
        return c1, c2
        """
        c1 = ElGamal_c.gen_c1(self.g_GLOBAL, self.secret, self.p_GLOBAL)

        c2 = ''
        for i in msg:
            c2 += ElGamal_c.encrypt_let(i, self.secret, self.e_GLOBAL, self.p_GLOBAL)

        return c2
    
    def decrypt(self, c1, c2):
        """
        decrypt msg using c1, c2
        return msg
        """
        x_key = ElGamal_c.gen_x_key(c1, self.secret, self.p_GLOBAL)
        msg = ''
        for i in c2:
            msg += ElGamal_c.decrypt_let(i, x_key, self.p_GLOBAL)
        
        return msg
p = 1009
x = 5

# Alice = ElGamalEncryptor(p, x)
# msg = 'hello'

# c2 = Alice.encrypt(msg)
c2 = 1
msg = ''
# print(c2, msg)

