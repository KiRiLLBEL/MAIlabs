import numpy as np
import math
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from scipy.integrate import odeint

def odesys(y, t, m1, m2, c, R, l, g):
    dy = np.zeros(4)
    dy[0] = y[2]
    dy[1] = y[3]
    e = R / (3 ** 0.5)
    a = y[0] - y[1] - (math.pi / 6)
    a11 = (5/6 * m1 + 4/3 * m2) * (R ** 2)
    a12 = 2 * m2 * l * e * np.sin(a)
    a21 = 2 * e * np.sin(a)
    a22 = l

    b1 = (y[3] ** 2) * np.cos(a) * 2 * m2 * l * e + \
         (m1 * np.sin(y[0]) + 2 * m2 * np.cos(y[0] - math.pi / 6)) * e * g - c * y[0]
    b2 = -2 * e * (y[2] ** 2) * np.cos(a) - g * np.sin(y[1])

    dy[2] = (b1*a22 - b2*a12)/(a11*a22 - a12*a21)
    dy[3] = (b2*a11 - b1*a21)/(a11*a22 - a12*a21)
    return dy

m1 = 10
m2 = 0.001
c = 15
R = 1
l = 1
g = 9.81

Steps = 1001
t_fin = 20
t = np.linspace(0, t_fin, Steps)

phi0 = 0
ksi0 = 0.5
dphi0 = 0
dksi0 = 0
y0 = [phi0, ksi0, dphi0, dksi0]

Y = odeint(odesys, y0, t, (m1, m2, c, R, l, g))

phi = Y[:, 0]
ksi = Y[:, 1]
dphi = Y[:, 2]
dksi = Y[:, 3]
ddphi = [odesys(y, t, m1, m2, c, R, l, g)[2] for y, t in zip(Y, t)]
ddksi = [odesys(y, t, m1, m2, c, R, l, g)[3] for y, t in zip(Y, t)]

fig_for_graphs = plt.figure(figsize=[13, 7])
ax_for_graphs = fig_for_graphs.add_subplot(2, 3, 1)
ax_for_graphs.plot(t, phi, color='blue')
ax_for_graphs.set_title("phi(t)")
ax_for_graphs.set(xlim=[0, t_fin])
ax_for_graphs.grid(True)

ax_for_graphs = fig_for_graphs.add_subplot(2, 3, 2)
ax_for_graphs.plot(t, ksi, color='red')
ax_for_graphs.set_title('ksi(t)')
ax_for_graphs.set(xlim=[0, t_fin])
ax_for_graphs.grid(True)

ax_for_graphs = fig_for_graphs.add_subplot(2, 3, 3)
ax_for_graphs.plot(t, dphi, color='green')
ax_for_graphs.set_title("phi'(t)")
ax_for_graphs.set(xlim=[0, t_fin])
ax_for_graphs.grid(True)

ax_for_graphs = fig_for_graphs.add_subplot(2, 3, 4)
ax_for_graphs.plot(t, dksi, color='black')
ax_for_graphs.set_title('ksi\'(t)')
ax_for_graphs.set(xlim=[0, t_fin])
ax_for_graphs.grid(True)

ax_for_graphs = fig_for_graphs.add_subplot(2, 3, 5)
ax_for_graphs.plot(t, ddphi, color='green')
ax_for_graphs.set_title("phi''(t)")
ax_for_graphs.set(xlim=[0, t_fin])
ax_for_graphs.grid(True)

ax_for_graphs = fig_for_graphs.add_subplot(2, 3, 6)
ax_for_graphs.plot(t, ddksi, color='black')
ax_for_graphs.set_title('ksi\'\'(t)')
ax_for_graphs.set(xlim=[0, t_fin])
ax_for_graphs.grid(True)

psi = np.linspace(0, 2 * math.pi, 100)
C = 1
R1 = 0.2
R2 = R/(3**0.5)/2

X_Wheel = R*np.sin(psi)
Y_Wheel = R*np.cos(psi)
X_C = -(R/(3**0.5))*np.sin(phi)
Y_C = (R/(3**0.5))*np.cos(phi)
X_A = X_C - R*np.sin(phi + math.pi / 2)
Y_A = Y_C + R*np.cos(phi + math.pi / 2)
X_B = X_A + l*np.sin(ksi)
Y_B = Y_A - l*np.cos(ksi)
thetta = np.linspace(0, C*math.pi*2-phi[0], 100)
X_SpiralSpr = -(R1 + thetta*(R2-R1)/thetta[-1])*np.sin(thetta)
Y_SpiralSpr = (R1 + thetta*(R2-R1)/thetta[-1])*np.cos(thetta)

fig = plt.figure(figsize=[15, 7])

ax = fig.add_subplot(1, 1, 1)

ax.axis('equal')
ax.set(xlim=[-6, 6], ylim=[-6, 6])

Circ = ax.plot(X_C[0]+R * np.cos(psi), Y_C[0]+R * np.sin(psi), 'yellow')[0]
Point_O = ax.plot(0, 0, marker='o')[0]
Point_C = ax.plot(X_C[0], Y_C[0], marker='o')[0]
Point_A = ax.plot(X_A[0], Y_A[0], marker='o')[0]
Point_B = ax.plot(X_B[0], Y_B[0], marker='o', markersize=20)[0]
Line_CO = ax.plot([0, X_C[0]], [0, Y_C[0]], 'blue')[0]
Line_AB = ax.plot([X_A[0], X_B[0]], [Y_A[0], Y_B[0]])[0]
Drawed_SpiralSpring = ax.plot(-X_SpiralSpr, Y_SpiralSpr)[0]

def anima(i):
    Point_C.set_data(X_C[i], Y_C[i])
    Point_A.set_data(X_A[i], Y_A[i])
    Point_B.set_data(X_B[i], Y_B[i])
    Line_AB.set_data([X_A[i], X_B[i]], [Y_A[i], Y_B[i]])
    Circ.set_data(X_C[i] + R * np.cos(psi), Y_C[i] + R * np.sin(psi))
    Line_CO.set_data([0, X_C[i]], [0, Y_C[i]])
    thetta = np.linspace(0, C * math.pi * 2 - phi[i], 100)
    X_SpiralSpr = -(R1 + thetta * (R2 - R1) / thetta[-1]) * np.sin(thetta)
    Y_SpiralSpr = (R1 + thetta * (R2 - R1) / thetta[-1]) * np.cos(thetta)
    Drawed_SpiralSpring.set_data(-X_SpiralSpr, Y_SpiralSpr)
    return [Point_C, Point_A, Point_B, Circ, Line_CO, Line_AB, Drawed_SpiralSpring]

anim = FuncAnimation(fig, anima, frames=len(t), interval=3)

plt.show()