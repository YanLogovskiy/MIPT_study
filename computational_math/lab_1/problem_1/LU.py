import numpy as np


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

if __name__ == "__main__":

    A = []
    with open('A9.txt', 'r') as matrix_file:
        line_num = 0
        for line in matrix_file:
            A.append(float(line))
        A = np.reshape(A, (3, 3))
        A = np.transpose(A)
    #it is done because in file we have consecutive columns, not rows 
        
    f = []
    with open('f9.txt', 'r') as f_file:
        line_num = 0
        for line in f_file:
            f.append(float(line))
        
        
    L, U = lu_decomposition(A)
    n = L.shape[0]

    #Ly = f
    y = np.zeros_like(f)
    for i in range(0, n):
        y[i] = f[i] - np.dot(L[i, :i], y[:i])
        
    #Ux = y    
    x = np.zeros_like(y)
    for i in reversed(range(0, n)):
        x[i] = (y[i] - np.dot(U[i, i+1:], x[i+1:])) / U[i][i]

    print(' A: \n', A, '\n\n L: \n', L, '\n\n U: \n', U, '\n\n x = ', x, '\n\n f = ', f)   

    #compute error
    e = np.linalg.norm(np.dot(A, x) - f) / np.linalg.norm(f)
    print('\n e = ', e)

    #for dumping as consecutive columns, we must transpose L
    L = np.transpose(L)
    L_one_dim = L.reshape(9)
    with open('L.txt', 'w') as l_file:
        for num in L_one_dim:
            l_file.write('{:.6e}'.format(num) + '\n')
            
    U = np.transpose(U)        
    U_one_dim = U.reshape(9)
    with open('U.txt', 'w') as u_file:
        for num in U_one_dim:
            u_file.write('{:.6e}'.format(num) + '\n')
            
    with open('x.txt', 'w') as x_file:
        for num in x:
            x_file.write('{:.6e}'.format(num) + '\n')

