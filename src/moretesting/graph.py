import matplotlib.pyplot as plt
import numpy as np
import numpy.polynomial.polynomial as poly
from scipy.optimize import curve_fit
import sympy as sym
import matplotlib.patches as mpatches

def func(x, a, b, c, d):
    return a*x**3 + b*x**2 +c*x + d

def serial():
    file = open('openmp.txt','r')
    data = file.readlines()
    file.close()
    count = 1.0
    X = []
    y =[]
    #for x in range(10):
    for x in data:
        if(count < 10):
            y.append(float(x.strip()))
            X.append(count)
        if(count % 1000 == 0):
            y.append(float(x.strip()))
            X.append(count)
        count += 1.0
    v = [0,300000,3250,4400]
    plt.axis(v)
    plt.plot(X,y)
    minP = min(y)
    file = open('serial.txt','r')
    data = file.readlines()
    file.close()
    count = 1.0
    X = []
    y =[]
    for x in data:
        if(count < 10):
            y.append(float(x.strip()))
            X.append(count)
        elif(count % 1000 == 0):
            y.append(float(x.strip()))
            X.append(count)
        count += 1.0
    minS = min(y)
    plt.plot(X,y, label ='serial')
    orange_patch = mpatches.Patch(color='orange', label='Serial min ' + str(minS))
    blue_patch = mpatches.Patch(color='skyblue', label='Parallel min ' + str(minP))
    plt.legend(handles=[blue_patch,orange_patch])
    plt.title("Average fitness over 2 hours")
    plt.xlabel("Generation number")
    plt.ylabel("Average fitness")
    plt.savefig('serial.svg',format='svg', dpi=1000)


def serial1():
    file = open('serial.txt','r')
    data = file.readlines()
    file.close()
    count = 1.0
    X = []
    y =[]
    for x in data:
        if(count % 1000 == 0):
            y.append(float(x.strip()))
            X.append(count)
        count += 1.0
    x = np.array(X, dtype=float) #transform your data in a numpy array of floats 
    y = np.array(y, dtype=float) #so the curve_fit can work
    popt, pcov = curve_fit(func, x, y)
    xs = sym.Symbol('\lambda')    
    tex = sym.latex(func(xs,*popt)).replace('$', '')
    plt.title(r'$f(\lambda)= %s$' %(tex),fontsize=16)
    plt.plot(x, func(x, *popt), label="Fitted Curve")
    plt.savefig('serial.svg',format='svg', dpi=1000)
def parallel1():
    file = open('openmp.txt','r')
    data = file.readlines()
    file.close()
    count = 1.0
    X = []
    y =[]
    for x in data:
        if(count % 1000 == 0):
            y.append(float(x.strip()))
            X.append(count)
        count += 1.0

    x = np.array(X, dtype=float) #transform your data in a numpy array of floats 
    y = np.array(y, dtype=float) #so the curve_fit can work
    popt, pcov = curve_fit(func, x, y)
    xs = sym.Symbol('\lambda')    
    tex = sym.latex(func(xs,*popt)).replace('$', '')
    plt.title(r'$f(\lambda)= %s$' %(tex),fontsize=16)
    plt.plot(x, func(x, *popt), label="Fitted Curve")
    plt.savefig('parallel.svg',format='svg', dpi=1000)

serial()
