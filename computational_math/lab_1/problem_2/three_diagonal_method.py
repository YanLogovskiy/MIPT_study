import numpy as np
from matplotlib import pyplot as plt
import math

def three_diagonal_method(a, b, c, d):
    y = np.zeros_like(b)
    x = np.zeros_like(b)
    alpha = np.zeros_like(b)
    betta = np.zeros_like(b)
    n = len(b)

    y[0] = b[0]
    alpha[0] = - c[0] / y[0]
    betta[0] = d[0] / y[0]

    for i in range(1, n-1):
        y[i] = b[i] + a[i-1] * alpha[i-1]
        alpha[i] = - c[i] / y[i]
        betta[i] = (d[i] - a[i-1] * betta[i-1]) / y[i]

    y[n-1] = b[n-1] + a[n-2] * alpha[n-2]
    betta[n-1] = (d[n-1] - a[n-2] * betta[n-2]) / y[n-1]

    x[n-1] = betta[n-1]
    for i in reversed(range(0, n-1)):
        x[i] = alpha[i] * x[i+1] + betta[i]

    with open('alpha.txt', 'w') as file:
        for num in alpha:
            file.write('{:.6e}'.format(num) + '\n')

    with open('betta.txt', 'w') as file:
        for num in betta:
            file.write('{:.6e}'.format(num) + '\n')

    return x


if __name__ == "__main__":

    a = []
    b = []
    c = []
    d = []
    with open('a_diag9.txt') as a_file:
        for line in a_file:
            a.append(float(line))

    with open('c_diag9.txt') as b_file:
        for line in b_file:
            b.append(float(line))

    # I used formula where b is central

    with open('b_diag9.txt') as c_file:
        for line in c_file:
            c.append(float(line))

    with open('r9.txt') as d_file:
        for line in d_file:
            d.append(float(line))

    x = three_diagonal_method(a, b, c, d)

    #initialize matrix A
    n = len(b)
    A = np.zeros((n, n))
    A[0][0] = b[0]
    A[0][1] = c[0]

    for i in range(1, n-1):
        A[i][i-1] = a[i-1]
        A[i][i]   = b[i]
        A[i][i+1] = c[i]
        
    A[n-1][n-2] = a[n-2]
    A[n-1][n-1] = b[n-1]

    f = d
    e = np.linalg.norm(np.dot(A, x) - f) / np.linalg.norm(f)

    print('e = ', e)

    with open('x.txt', 'w') as file:
        for num in x:
            file.write('{:.6e}'.format(num) + '\n')
                

    # Compare with Gauss method

    def lu_decomposition(A):
        L = np.zeros_like(A)
        U = np.zeros_like(A)

        n = A.shape[0]
        U[0, :] = A[0, :]
        L[:, 0] = A[:, 0] / A[0][0]

        for i in range(1, n):
            U[i, i:] = A[i, i:] - np.dot(L[i, :i], U[:i, i:])
            L[i:, i] = (A[i:, i] - np.dot(L[i:, :i], U[:i, i])) / U[i][i]

        return L, U


    L, U = lu_decomposition(A)
    n = L.shape[0]

    #Ly = f
    y = np.zeros_like(f)
    for i in range(0, n):
        y[i] = f[i] - np.dot(L[i, :i], y[:i])

    #Ux = y
    x_g = np.zeros_like(y)
    for i in reversed(range(0, n)):
        x_g[i] = (y[i] - np.dot(U[i, i+1:], x[i+1:])) / U[i][i]

    #compute error
    e_g = np.linalg.norm(np.dot(A, x_g) - f) / np.linalg.norm(f)
    print('\n e_g = ', e_g)
