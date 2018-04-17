import numpy as np
import matplotlib.pyplot as plt

def serial():
    serial_times = ( 20, 24, 29, 34, 40)
    ind = np.arange(len(serial_times))
    x = (10000,12500,15000,17500,20000)
    fig, ax = plt.subplots()
    width = .3
    rects1 = ax.bar(ind, serial_times, width, color = 'SkyBlue', label ='Serial 12 Cities')
    ax.set_ylabel('time (seconds)')
    ax.set_title('Execution Time of Serial Code for 1000 generations')
    ax.set_xticks(ind)
    ax.set_xlabel('Population Size')
    ax.set_xticklabels(x)
    ax.legend()
    plt.savefig('serialchart.svg',format='svg', dpi = 1000)
def parallel_scale():
    parallel_times12 = (12.5806, 9.9867, 8.29759, 8.36338, 7.5802)
    ind = np.arange(len(parallel_times12))
    x = (2, 3, 4, 6, 8)
    fix, ax = plt.subplots()
    width = .3
    rects1 = ax.bar(ind, parallel_times12, width, color = 'SkyBlue',label='Parallel 12 Cities')
    ax.set_ylabel('time (seconds)')
    ax.set_xlabel('# of threads')
    ax.set_xticks(ind)
    ax.set_xticklabels(x)
    ax.legend()
    ax.set_title('Parallel Population Size 10,000 for 1000 generations')
    plt.savefig('parallel_scale.svg',format='svg', dpi=1000)
def parallel_size():
    parallel_times12 = (13.0146, 12.6634, 12.6762, 14.4815, 14.6598)
    ind = np.arange(len(parallel_times12))
    x = ('10000 : 2', '12500 : 3', '15000 : 4', '175000 : 6', '20000 : 8')
    fix, ax = plt.subplots()
    width = .3
    rects1 = ax.bar(ind, parallel_times12, width, color = 'SkyBlue' , label='Parallel 12 Cities')
    ax.set_ylabel('time (seconds)')
    ax.set_xlabel('Population Size :# of threads')
    ax.set_xticks(ind)
    ax.set_xticklabels(x)
    ax.legend()
    ax.set_title('Parallel Weak Scaling for 1000 generations')
    plt.savefig('parallel_size.svg',format='svg', dpi=1000)
serial()
parallel_scale()
parallel_size()
