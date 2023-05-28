from time import time

def bench_func(func, args):
    s = time()

    func(102551,args)

    s = time() - s
    return s

def bench_average(func, n):
    timings = []
    for i in range(10000, n, 10000):
        timings.append((i, bench_func(func, i)))

    return timings
    

import matplotlib.pyplot as plot
from pygamal import *
res = bench_average(gen_keys, 1_000_000)
Time = [x[0] for x in res]
Speed = [x[1] for x in res]
plot.plot(Time, Speed)
plot.title('Speed Time Graph')
plot.xlabel('Time')
plot.ylabel('Speed')
plot.show()