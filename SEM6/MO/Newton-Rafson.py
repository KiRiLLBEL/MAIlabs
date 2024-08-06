import numpy as np
import matplotlib.pyplot as plt
import sympy as sp
from mpl_toolkits.mplot3d import Axes3D


def gradient_sympy(f, symbols):
    grad_f = [sp.diff(f, sym) for sym in symbols]
    return sp.lambdify(symbols, grad_f, 'numpy')

def hessian_sympy(f, symbols):
    hess_f = [[sp.diff(f, sym1, sym2) for sym1 in symbols] for sym2 in symbols]
    return sp.lambdify(symbols, hess_f, 'numpy')


def newton_raphson_sympy(f, x0, tol=1e-5, max_iter=1000):
    x1, x2 = sp.symbols('x1 x2')
    grad_f = gradient_sympy(f, (x1, x2))
    hess_f = hessian_sympy(f, (x1, x2))

    x_val = np.array(x0, dtype=float)
    path = [x_val.copy()]
    for i in range(max_iter):
        grad_val = np.array(grad_f(*x_val))
        hess_val = np.array(hess_f(*x_val))
        try:
            hess_inv = np.linalg.inv(hess_val)
        except np.linalg.LinAlgError:
            print(f"Newton-Raphson: Матрица Гессе вырождена в итерации {i + 1}")
            break

        x_new = x_val - hess_inv.dot(grad_val)
        path.append(x_new.copy())
        if np.linalg.norm(x_new - x_val) < tol:
            print(f"Newton-Raphson: Минимум найден в точке {x_new} за {i + 1} итераций")
            break
        x_val = x_new
    return x_val, np.array(path)


x1, x2 = sp.symbols('x1 x2')
f = 100 * (x2 - x1**2) ** 2 + (1 - x1) ** 2
x0 = [-20, -10]
x_min, path = newton_raphson_sympy(f, x0)

plt.figure()
plt.plot(path[:, 0], path[:, 1], 'ro-', label='Path')
X, Y = np.meshgrid(np.linspace(-400, 400, 3000), np.linspace(-400, 400, 3000))
Z = 100 * (Y - X**2) ** 2 + (1 - X) ** 2
plt.contour(X, Y, Z, levels=50, cmap='viridis')
plt.legend()
plt.title('Newton-Raphson Method - 2D')
plt.xlabel('x1')
plt.ylabel('x2')
plt.show()

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.7)
ax.plot(path[:, 0], path[:, 1], np.sum(path ** 2, axis=1), 'ro-', label='Path')
ax.set_title('Newton-Raphson Method - 3D')
ax.set_xlabel('x1')
ax.set_ylabel('x2')
ax.set_zlabel('f(x1, x2)')
ax.legend()
plt.show()
