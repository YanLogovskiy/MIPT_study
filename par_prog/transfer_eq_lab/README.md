The key idea of the algotithm is to fill the table below.
Take table 3x3 as an example:

|--------|----------|-----------|
|psi(0)  |phi(dx)   |phi(2dx)   |
|psi(dt) |U(dt, dx) |U(dt, 2dx) |
|psi(2dt)|U(2dt, dx)|U(2dt, 2dx)|

dt, dx - are steps in computation process \
psi(t), phi(x) - are the border condition of equation: \
dU(t, x)/dt + a * dU(t, x)/dx = func(t, x) \
U(0, x) = phi(x), U(t, 0) = psi(t)
