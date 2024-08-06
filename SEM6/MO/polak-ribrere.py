import numpy as np
import matplotlib.pyplot as plt
import sympy as sp
from scipy.optimize import minimize_scalar
from mpl_toolkits.mplot3d import Axes3D

def gradient_sympy(f, symbols):
    grad_f = [sp.diff(f, sym) for sym in symbols]
    return sp.lambdify(symbols, grad_f, 'numpy')

def phi(t, f, grad_f, x_val, d):
    x1, x2 = sp.symbols('x1 x2')
    new_x = x_val + t * d
    return float(f.evalf(subs={x1: new_x[0], x2: new_x[1]}))


def polak_ribiere_sympy(f, x0, tol=1e-5, max_iter=1000):
    x1, x2 = sp.symbols('x1 x2')
    grad_f = gradient_sympy(f, (x1, x2))

    x_val = np.array(x0, dtype=float)
    grad = np.array(grad_f(*x_val))
    d = -grad
    path = [x_val.copy()]
    for i in range(max_iter):
        if np.linalg.norm(grad) < tol:
            print(f"Polak-Ribiere: Минимум найден в точке {x_val} за {i + 1} итераций")
            break

        # Определение величины шага с использованием одномерной оптимизации
        res = minimize_scalar(phi, args=(f, grad_f, x_val, d))
        alpha = res.x

        x_new = x_val + alpha * d
        path.append(x_new.copy())
        grad_new = np.array(grad_f(*x_new))
        beta = np.dot(grad_new, grad_new - grad) / np.dot(grad, grad)
        d = -grad_new + beta * d
        x_val = x_new
        grad = grad_new
    return x_val, np.array(path)


x1, x2 = sp.symbols('x1 x2')
f = 100 * (x2 - x1**2) ** 2 + (1 - x1) ** 2
x0 = [-20, -10]
x_min, path = polak_ribiere_sympy(f, x0)

plt.figure()
plt.plot(path[:, 0], path[:, 1], 'ro-', label='Path')
X, Y = np.meshgrid(np.linspace(-20, 20, 800), np.linspace(-20, 20, 800))
Z = 100 * (Y - X**2) ** 2 + (1 - X) ** 2
plt.contour(X, Y, Z, levels=50, cmap='viridis')
plt.legend()
plt.title('Polak-Ribiere Method - 2D')
plt.xlabel('x1')
plt.ylabel('x2')
plt.show()

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.7)
ax.plot(path[:, 0], path[:, 1], np.sum(path ** 2, axis=1), 'ro-', label='Path')
ax.set_title('Polak-Ribiere Method - 3D')
ax.set_xlabel('x1')
ax.set_ylabel('x2')
ax.set_zlabel('f(x1, x2)')
ax.legend()
plt.show()
