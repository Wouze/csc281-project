from time import time
import matplotlib.pyplot as plot
from scipy.signal import lfilter
from scipy.interpolate import splrep, splev
from numba import njit
import MyPrime
from MyPrime import pow_mod

['get_all_primitive_roots_inter',
 'get_all_primitive_roots_loop',
 'get_all_primitive_roots_mosaed',
 'is_prime',
 'is_primitive_root',
 'pow_mod',
 'pow_mod2']

"""
if pow(g, i, n) == 1:  # 3.829s
return False

if powmod(g, i, n) == 1:  # 1.481s w: @njit @ is_primitive_root(g, n)
return False

if powmod_n(g, i, n) == 1:  # 1.481s w: @njit @ is_primitive_root(g, n)
return False

if MyPrime.pow_mod(g, i, n) == 1:
return False

if MyPrime.pow_mod2(g, i, n) == 1:
return False
"""

global_mod = 0

def get_lop(p): 
    res = []
    o=1
    for r in range(p):
        k = powmod(r, o, p)
        # k %= p
        while k > 1:
            o+=1
            k *= r
            k %= p
        
        if o == (p - 1):
            res.append(r)
        o = 1
    return res

@njit()
def powmod(base, n, mod):
    if n == 1:
        return base
    elif n % 2 == 0:
        return (powmod(base, n/2, mod)**2) % mod
    else:
        return ((powmod(base, (n-1)/2, mod)**2)*base) % mod

def powmod_n(base, n, mod):
    if n == 1:
        return base
    elif n % 2 == 0:
        return (powmod_n(base, n/2, mod)**2) % mod
    else:
        return ((powmod_n(base, (n-1)/2, mod)**2)*base) % mod

@njit
def is_primitive_root(g, n):
    for i in range(1, n-1):

        # if powmod_n(g, i, n) == 1:  # 1.481s w: @njit @ is_primitive_root(g, n)
        #     return False

        # if pow(g, i, n) == 1:
        #     return False

        if powmod(g, i, n) == 1:  # 1.481s w: @njit @ is_primitive_root(g, n)
            return False
        
    return True

def is_primitive_root2(g, n):
    for i in range(1, n-1):

        # if pow(g, i, n) == 1: 
        #     return False

        # if powmod(g, i, n) == 1:  # 1.481s w: @njit @ is_primitive_root(g, n)
        #     return False

        if MyPrime.pow_mod2(g, i, n) == 1:
            return False
        
    return True

def is_primitive_root3(g, n):
    for i in range(1, n-1):

        # if pow(g, i, n) == 1: 
        #     return False

        # if powmod(g, i, n) == 1:  # 1.481s w: @njit @ is_primitive_root(g, n)
        #     return False

        if pow_mod(g, i, n) == 1:
            return False
        
    return True




def bench_func(func, args, loop):
    sum = 0
    t = []
    for _ in range(3):
        if loop:
            s = time()
            for i in range(1, args):
                if func(i, args):
                    t.append(i)
            sum += time() - s
        else:
            s = time()
            t = func(args)
            sum += time() - s

    print(args, len(t))
    return sum/3, t

def bench_average(func, n, loop):

    timings = []
    for i in range(50, n, 50):
        x = i
        while not MyPrime.is_prime(x):
            x += 1
        res, t1 = bench_func(func, x, loop)

        timings.append((x, res))

    return timings


def plot_func(func,func2, name1, name2, func_name, n=7_00):
    res = bench_average(func, n, True)
    print("\n===============\n")

    Prime_n = [x[0] for x in res]
    Speed = [x[1] for x in res]
    z = sum(Speed)/len(Speed)
    bspl = splrep(Prime_n, Speed, s=10)
    bspl_y = splev(Prime_n, bspl)
    plot.plot(Prime_n, bspl_y, '-', label=name1, linewidth=1)

    res = bench_average(func2, n, False)

    Prime_n = [x[0] for x in res]
    Speed = [x[1] for x in res]
    z = z/(sum(Speed)/len(Speed))
    bspl = splrep(Prime_n, Speed, s=10)
    bspl_y = splev(Prime_n, bspl)
    plot.plot(Prime_n, bspl_y, '-', label=name2, linewidth=2)



    # res = bench_average(is_primitive_root3, n)

    # Prime_n = [x[0] for x in res]
    # Speed = [x[1] for x in res]
    # # z = z/(sum(Speed)/len(Speed))
    # bspl = splrep(Prime_n, Speed, s=10)
    # bspl_y = splev(Prime_n, bspl)
    # plot.plot(Prime_n, bspl_y, 'r-', label='C (from internet)', linewidth=2)




    plot.title(f'{func_name}')
    plot.xlabel('Prime N')
    plot.ylabel('Speed')
    # plot.show()
    plot.legend()
    plot.savefig(format='pdf', fname=f'{func_name}.pdf')
    print(z)
    print(z*100)

# plot_func(is_primitive_root, is_primitive_root2, 'Native', 'Built-in', 'Native Python vs Built-in', n=700)
# plot_func(is_primitive_root, is_primitive_root2, 'Built-in', 'Optimized', 'Built-in vs Optimized', n=1000)
plot_func(is_primitive_root, MyPrime.get_all_primitive_roots_mosaed, 'Python Optimized', 'C (our\'s)', 'Python Optimized vs C', n=2000)
