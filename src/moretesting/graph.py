import matplotlib.pyplot as plt
import numpy
import scipy.optimize as s
def func(x, a, b, c):
     return a * np.exp(-b * x) + c
file = open('serial.txt','r')
data = file.readlines()
file.close()
count = 1.0
X = []
y =[]
for x in data:
    if(count % 100 == 0):
        y.append(float(x.strip()))
        X.append(count)
    count += 1.0

#print(X)
#print(y)
X = numpy.array(X)
y = numpy.array(y)
popt,_ = s.curve_fit(lambda t,a,b: a*numpy.exp(b*t),  X,  y)
print(y)
plt.plot(X,func(y*popt))
#plt.plot(np.unique(X), np.poly1d(np.polyfit(X, y, 1))(np.unique(X)))
plt.show()


