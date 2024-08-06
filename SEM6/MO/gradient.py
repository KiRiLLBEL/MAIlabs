import numpy as np
import matplotlib.pyplot as plt
import sympy as sp
from mpl_toolkits.mplot3d import Axes3D


def gradient_sympy(f, symbols):
    grad_f = [sp.diff(f, sym) for sym in symbols]
    return sp.lambdify(symbols, grad_f, 'numpy')


def gradient_descent_constant_step(f, x0, lr=0.2, tol=1e-5, max_iter=1000):
    x1, x2 = sp.symbols('x1 x2')
    grad_f = gradient_sympy(f, (x1, x2))

    x_val = np.array(x0, dtype=float)
    path = [x_val.copy()]
    for i in range(max_iter):
        grad_val = np.array(grad_f(*x_val))
        x_new = x_val - lr * grad_val

        while f.evalf(subs={x1: x_new[0], x2: x_new[1]}) >= f.evalf(subs={x1: x_val[0], x2: x_val[1]}):
            lr /= 2
            x_new = x_val - lr * grad_val
            if lr < tol:
                break

        path.append(x_new.copy())
        if np.linalg.norm(x_new - x_val) < tol:
            print(f"Gradient Descent (constant step): Минимум найден в точке {x_new} за {i + 1} итераций")
            break
        x_val = x_new
    return x_val, np.array(path)


# Пример функции
x1, x2 = sp.symbols('x1 x2')
# f = 10 * (x1 - 14) ** 2 + 1 * (x2 - 8) ** 2
# f = 10 * (x1 - 1) ** 2 + 1 * (x2 - 8) ** 2
# f = 10 * (x1 - 8) ** 2 + 1 * (x2 - 8) ** 2
f = 100 * (x2 - x1**2) ** 2 + (1 - x1) ** 2
x0 = [3, 3]
x_min, path = gradient_descent_constant_step(f, x0)

plt.figure()
plt.plot(path[:, 0], path[:, 1], 'ro-', label='Path')
X, Y = np.meshgrid(np.linspace(-40, 40, 800), np.linspace(-20, 20, 800))
Z = 10 * (X - 14) ** 2 + 1 * (Y - 8) ** 2
plt.contour(X, Y, Z, levels=50, cmap='viridis')
plt.legend()
plt.title('Gradient Descent (constant step) - 2D')
plt.xlabel('x1')
plt.ylabel('x2')
plt.show()

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.7)
ax.plot(path[:, 0], path[:, 1], np.sum(path ** 2, axis=1), 'ro-', label='Path')
ax.set_title('Gradient Descent (constant step) - 3D')
ax.set_xlabel('x1')
ax.set_ylabel('x2')
ax.set_zlabel('f(x1, x2)')
ax.legend()
plt.show()

print(x_min)
