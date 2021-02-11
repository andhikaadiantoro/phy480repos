import numpy as np
#import matplotlib.pyplot as plt
import scipy.linalg as la

n = 4
P = np.random.randint(0,10,(n,n))
print(P)

evals, evecs = la.eig(P)
#evals = evals.real

print(evals)
print(evecs)

