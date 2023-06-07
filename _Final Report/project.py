
def is_prime(p):
    p_sqrt = int(pow(p, 0.5)) + 1

    if p <= 1:  # Exclude negative and 1
        return False

    if p == 2:  # Include 2
        return True

    for i in range(2, p_sqrt):
        if p % i == 0:
            return False

    return True


def powmod(base, exp, mod):

    if exp == 0: return 1
    if exp == 1: return base
    if exp == 2: return (base*base) % mod

    half_pow = powmod(powmod(base, exp//2, mod), 2, mod)

    return (powmod(base, exp % 2, mod) * half_pow) % mod


def is_primitive_root(p, g):

    for i in range(1, p-1):
        if powmod(g, i, p) == 1:
            return False

    return True


def get_all_primitive_roots(p):
    result = []

    for g in range(1, p):
        if is_primitive_root(p, g):
            result.append(g)

    return result

# s = time.time()
# sawd =get_all_primitive_roots(5003)
# print("took:", time.time()-s)
