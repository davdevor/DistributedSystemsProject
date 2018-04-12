import numpy as np
import matplotlib.pyplot as plt

def serial():
    serial_times = ( 31, 37, 45, 52, 59)
    ind = np.arange(len(serial_times))
    x = (10000,12500,15000,17500,20000)
    fig, ax = plt.subplots()
    width = .3
    rects1 = ax.bar(ind, serial_times, width, color = 'SkyBlue', label ='Serial 12 Cities')
    ax.set_ylabel('time (seconds)')
    ax.set_title('Execution Time of Serial Code')
    ax.set_xticks(ind)
    ax.set_xlabel('Population Size')
    ax.set_xticklabels(x)
    ax.legend()
    plt.savefig('serialchart.svg',format='svg', dpi = 1000)
def parallel_scale():
    parallel_times12 = (19.6673, 15.4103, 13.5842, 12.8859, 11.3896)
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
    ax.set_title('Parallel Population Size 10,000')
    plt.savefig('parallel_scale.svg',format='svg', dpi=1000)
def parallel_size():
    parallel_times12 = (19.5333, 20.0353, 22.4724, 22.2633, 21.5233)
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
    ax.set_title('Parallel Weak Scaling')
    plt.savefig('parallel_size.svg',format='svg', dpi=1000)
serial()
parallel_scale()
parallel_size()
