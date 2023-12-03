//
// Created by kiril on 14.11.2023.
//

#ifndef RENDER_H
#define RENDER_H
#include <QtOpenGLWidgets>

#include "Ellipsoid.h"
#include "Object.h"

struct Camera {
    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;
    float translationX = 0;
    float translationY = 0;
    float translationZ = 0;
};

class Render : public QOpenGLWidget, protected QOpenGLFunctions {
private:
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 modelMatrix;
    QOpenGLShaderProgram staticProgram;
    QOpenGLShaderProgram animationProgram;
    QOpenGLBuffer vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer ebo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);;
    QOpenGLVertexArrayObject vao;
    QVector4D light = {1, 1, -2, 1};
    void animate();
    bool animationStart = false;
    float time = 0;
public:
    explicit Render(QWidget *parent);
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void rotateObjectX(double angle);
    void rotateObjectY(double angle);
    void rotateObjectZ(double angle);
    void translateObjectX(double cord);
    void translateObjectY(double cord);
    void translateObjectZ(double cord);
    void scaleObject(double scale);
    void rotateCameraX(double angle);
    void rotateCameraY(double angle);
    void rotateCameraZ(double angle);
    void translateCameraX(double cord);
    void translateCameraY(double cord);
    void translateCameraZ(double cord);
    void moveLightX(double cord);
    void moveLightY(double cord);
    void moveLightZ(double cord);
    void transfromMatrix(QMatrix4x4& matrix, const Transformation& transform);
    void rotateNormal(QMatrix4x4& matrix, const Transformation& transform);
    void startAnimation();
    void stopAnimation();
    QVector4D rotateLight();
    void recreateObject();
    Ellipsoid ellipsoid;
    Object object;
    Camera camera;
};



#endif //RENDER_H
