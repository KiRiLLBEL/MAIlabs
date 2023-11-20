import sys
from PyQt6.QtWidgets import QApplication, QWidget, QSlider, QVBoxLayout, QHBoxLayout, QLabel, QLayout
from PyQt6.QtOpenGLWidgets import QOpenGLWidget
from PyQt6.QtCore import Qt
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import numpy as np
import math


def func(x, y, a):
    return x**(2/3) + y**(2/3) - a**(2/3)

class GLWidget(QOpenGLWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.a = 1.0
        self.scale = 1.0
        self.sizeX = 10
        self.sizeY = 10

    def initializeGL(self):
        glutInit()
        glClearColor(1.0, 1.0, 1.0, 1.0)
        glEnable(GL_LINE_SMOOTH)
        glEnable(GL_DEPTH_TEST)

    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        w = self.width()
        h = self.height()
        self.sizeX = 10
        self.sizeY = 10
        aspect = w / h if h > 0 else 1
        gluOrtho2D(-self.sizeX * aspect / self.scale, self.sizeX * aspect / self.scale, -self.sizeY / self.scale, self.sizeY / self.scale)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        glColor3f(0.0, 0.0, 0.0)
        glLineWidth(3.0)

        glBegin(GL_LINE_LOOP)

        n = 100
        step = math.pi * 2 / n

        for i in range(n):
            x = self.a * (math.cos(i * step) ** 3)
            y = self.a * (math.sin(i * step) ** 3)
            glVertex2f(x, y)
        glEnd()
        glColor3f(0.5, 0.5, 0.5)
        glLineWidth(2.0)
        glBegin(GL_LINES)
        glVertex2f(0, -self.sizeY)
        glVertex2f(0, self.sizeY)
        glEnd()
        glBegin(GL_LINES)
        glVertex2f(-self.sizeX, 0)
        glVertex2f(self.sizeX, 0)
        glEnd()
        glColor3f(1, 0, 0)
        glLineWidth(1.0)
        glBegin(GL_LINES)
        for x in range(-self.sizeX, self.sizeX + 1):
            glVertex2f(x, 0)
            glVertex2f(x, -0.2)
        glEnd()
        for x in range(-self.sizeX, self.sizeX + 1):
            glRasterPos2f(x - 0.1, -0.5)
            for c in str(x):
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ord(c))
        glBegin(GL_LINES)
        for y in range(-self.sizeX, self.sizeX + 1):
            glVertex2f(0, y)
            glVertex2f(-0.2, y)
        glEnd()
        for y in range(-self.sizeX, self.sizeX + 1):
            glRasterPos2f(-0.5, y - 0.1)
            for c in str(y):
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ord(c))
        glBegin(GL_LINES)
        glVertex2f(10, 0)
        glVertex2f(9.7, 0.3)
        glVertex2f(9.7, -0.3)
        glVertex2f(10, 0)
        glEnd()
        glBegin(GL_LINES)
        glVertex2f(0, 10)
        glVertex2f(0.3, 9.7)
        glVertex2f(-0.3, 9.7)
        glVertex2f(0, 10)
        glEnd()
        glRasterPos2f(9.5, -1)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ord('x'))
        glRasterPos2f(-1, 9.5)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ord('y'))

    def resizeGL(self, w, h):
        glViewport(0, 0, w, h)


    def update_params(self, a):
        self.a = a
        self.update()

    def update_scale(self, scale):
        self.scale = scale
        self.update()

    def wheelEvent(self, event):
        angle = event.angleDelta().y()
        if angle > 0:
            self.update_scale(self.scale * 1.1)
        elif angle < 0:
            if(self.scale > 1):
                self.update_scale(self.scale * 0.9)

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Plot')
        self.resize(800, 800)
        self.gl_widget = GLWidget(self)
        self.slider_a = QSlider(Qt.Orientation.Horizontal)
        self.slider_a.setMinimum(-100)
        self.slider_a.setMaximum(100)
        self.slider_a.setValue(1)
        self.slider_a.valueChanged.connect(self.on_slider_a_changed)
        self.layout = QVBoxLayout()
        self.layout.addWidget(self.gl_widget)
        self.layout_slider = QHBoxLayout()
        self.layout_slider.setSizeConstraint(QLayout.SizeConstraint.SetMinimumSize)
        self.label = QLabel()
        self.label.setMaximumSize(100, 50)
        self.layout_slider.addWidget(self.slider_a)
        self.layout_slider.addWidget(self.label)
        self.label.setText(f"a = {1}")
        self.layout.addLayout(self.layout_slider)
        self.setLayout(self.layout)

    def on_slider_a_changed(self, value):
        a = value / 10
        self.label.setText(f"a = {a}")
        self.gl_widget.update_params(a)

app = QApplication(sys.argv)
window = MainWindow()
window.show()
sys.exit(app.exec())
