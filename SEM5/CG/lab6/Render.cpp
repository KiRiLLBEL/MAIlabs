//
// Created by kiril on 14.11.2023.
//

#include "Render.h"
#include <QtOpenGL>
#include <iostream>
Render::Render(QWidget *parent) : QOpenGLWidget(parent) {
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Render::animate);
    timer->start(10); // Запускаем таймер каждые 10 миллисекунд
}

void Render::animate() {
    time += 0.01f;
    time = fmod(time, 100.0f);
    if (animationStart) {
        update();
    }
}

void Render::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);

    bool vertexShader = staticProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "#version 330 core\n"
        "layout (location = 0) in vec4 position;\n"
        "layout (location = 1) in vec4 color;\n"
        "layout (location = 2) in vec4 normal;\n"
        "out vec3 vertexColor;\n"
        "out vec3 vertexNormal;\n"
        "out vec3 vertexPos;\n"
        "uniform mat4 projectionMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 rotateMatrix;\n"
        "void main() {\n"
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;\n"
        "   vertexPos = vec3(modelMatrix * position);\n"
        "   vertexColor = vec3(color);\n"
        "   vertexNormal = vec3(rotateMatrix * normal);\n"
        "}");
    if(!vertexShader) {
        std::cout << staticProgram.log().toStdString() << "\n";
    }
    bool fragmentShader = staticProgram.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "#version 330 core\n"
        "in vec3 vertexColor;\n"
        "in vec3 vertexNormal;\n"
        "in vec3 vertexPos;\n"
        "uniform vec4 vertexLight;\n"
        "uniform float ambientParam;\n"
        "uniform float specularParam;\n"
        "uniform float diffuseParam;\n"
        "uniform float shininessParam;\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   vec3 norm  = normalize(vertexNormal);\n"
        "   vec3 lightDir = normalize(vec3(vertexLight) - vertexPos);\n"
        "   float diff = diffuseParam * max(dot(norm, lightDir), 0.0);\n"
        "   vec3 viewDir = normalize(-vertexPos);\n"
        "   vec3 reflectDir = reflect(-lightDir, norm);\n"
        "   float spec = specularParam * pow(max(dot(viewDir, reflectDir), 0.0), shininessParam);\n"
        "   FragColor = vec4((ambientParam + diff + spec) * vertexColor, 1.0);\n"
        "}");
    if(!fragmentShader) {
        std::cout << staticProgram.log().toStdString() << "\n";
    }

    staticProgram.link();

    animationProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "#version 330 core\n"
        "layout (location = 0) in vec4 position;\n"
        "layout (location = 1) in vec4 color;\n"
        "layout (location = 2) in vec4 normal;\n"
        "out vec3 vertexColor;\n"
        "out vec3 vertexNormal;\n"
        "out vec3 vertexPos;\n"
        "uniform mat4 projectionMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 rotateMatrix;\n"
        "uniform float time;\n"
        "void main() {\n"
        "   mat4 model = modelMatrix;\n"
        "   model[3][0] += cos(time);\n"
        "   model[3][1] += sin(time);\n"
        "   gl_Position = projectionMatrix * viewMatrix * model * position;\n"
        "   vertexPos = vec3(model * position);\n"
        "   vertexColor = vec3(color);\n"
        "   vertexNormal = vec3(rotateMatrix * normal);\n"
        "}");

    animationProgram.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "#version 330 core\n"
        "in vec3 vertexColor;\n"
        "in vec3 vertexNormal;\n"
        "in vec3 vertexPos;\n"
        "uniform vec4 vertexLight;\n"
        "uniform float ambientParam;\n"
        "uniform float specularParam;\n"
        "uniform float diffuseParam;\n"
        "uniform float shininessParam;\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   vec3 norm  = normalize(vertexNormal);\n"
        "   vec3 lightDir = normalize(vec3(vertexLight) - vertexPos);\n"
        "   float diff = diffuseParam * max(dot(norm, lightDir), 0.0);\n"
        "   vec3 viewDir = normalize(-vertexPos);\n"
        "   vec3 reflectDir = reflect(-lightDir, norm);\n"
        "   float spec = specularParam * pow(max(dot(viewDir, reflectDir), 0.0), shininessParam);\n"
        "   FragColor = vec4((ambientParam + diff + spec) * vertexColor, 1.0);\n"
        "}");

    animationProgram.link();

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();

    ebo.create();
    ebo.bind();

    vao.release();
    vbo.release();
    ebo.release();

    QVector3D cameraPos(0.0f, 0.0f, 0.0f);
    QVector3D cameraTarget(0.0f, 0.0f, 1.0f);
    QVector3D up(0.0f, 1.0f, 1.0f);
    viewMatrix.lookAt(cameraPos, cameraTarget, up);
    modelMatrix.setToIdentity();
}

void Render::transfromMatrix(QMatrix4x4& matrix, const Transformation& transform) {
    matrix.setToIdentity();
    matrix.translate(camera.translationX, camera.translationY, camera.translationZ);
    matrix.rotate(camera.angleX, {1, 0, 0});
    matrix.rotate(camera.angleY, {0, 1, 0});
    matrix.rotate(camera.angleZ, {0, 0, 1});
    matrix.translate(transform.translateX, transform.translateY, transform.translateZ);
    matrix.rotate(transform.angleX, {1, 0, 0});
    matrix.rotate(transform.angleY, {0, 1, 0});
    matrix.rotate(transform.angleZ, {0, 0, 1});
    matrix.scale(transform.scaleX, transform.scaleY, transform.scaleZ);
}

void Render::rotateNormal(QMatrix4x4& matrix, const Transformation& transform) {
    matrix.setToIdentity();
    matrix.rotate(camera.angleX, {1, 0, 0});
    matrix.rotate(camera.angleY, {0, 1, 0});
    matrix.rotate(camera.angleZ, {0, 0, 1});
    matrix.rotate(transform.angleX, {1, 0, 0});
    matrix.rotate(transform.angleY, {0, 1, 0});
    matrix.rotate(transform.angleZ, {0, 0, 1});
}

void Render::startAnimation() {
    animationStart = true;
}

void Render::stopAnimation() {
    animationStart = false;
    time = 0;
}

QVector4D Render::rotateLight() {
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.rotate(camera.angleX, {1, 0, 0});
    matrix.rotate(camera.angleY, {0, 1, 0});
    matrix.rotate(camera.angleZ, {0, 0, 1});
    matrix.translate(camera.translationX, camera.translationY, camera.translationZ);
    return matrix * light;
}




void Render::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    transfromMatrix(modelMatrix, object.transform);
    QMatrix4x4 rotateMatrix;
    rotateNormal(rotateMatrix, object.transform);
    QOpenGLShaderProgram* program = animationStart ? &animationProgram : &staticProgram;
    program->bind();
    program->setUniformValue("projectionMatrix", projectionMatrix);
    if(animationStart) {
        program->setUniformValue("time", time);
    }
    program->setUniformValue("viewMatrix", viewMatrix);
    program->setUniformValue("modelMatrix", modelMatrix);
    program->setUniformValue("rotateMatrix", rotateMatrix);
    program->setUniformValue("vertexLight", rotateLight());
    program->setUniformValue("ambientParam", object.property.ambient);
    program->setUniformValue("specularParam", object.property.specular);
    program->setUniformValue("diffuseParam", object.property.diffuse);
    program->setUniformValue("shininessParam", object.property.shininess);

    vao.bind();
    vbo.bind();
    vbo.allocate(object.vertices.constData(), sizeof(Vertex) * object.vertices.size());

    ebo.bind();  // Мы связываем EBO
    ebo.allocate(object.polygons.data(), sizeof(unsigned int) * object.polygons.size());  // Мы выделяем память для EBO

    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, offsetof(Vertex, position), 4, sizeof(Vertex));

    program->enableAttributeArray(1);
    program->setAttributeBuffer(1, GL_FLOAT, offsetof(Vertex, color), 4, sizeof(Vertex));

    program->enableAttributeArray(2);
    program->setAttributeBuffer(2, GL_FLOAT, offsetof(Vertex, normal), 4, sizeof(Vertex));

    glDrawElements(GL_TRIANGLES, object.polygons.size(), GL_UNSIGNED_INT, 0);
    program->disableAttributeArray(0);
    program->disableAttributeArray(1);
    program->disableAttributeArray(2);

    vao.release();
    program->release();
}

void Render::resizeGL(int w, int h) {
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45, w / float(h), 1, 100);
}

void Render::rotateObjectX(double angle) {
    object.transform.angleX = angle;
}

void Render::rotateObjectY(double angle) {
    object.transform.angleY = angle;
}

void Render::rotateObjectZ(double angle) {
    object.transform.angleZ = angle;
}

void Render::translateObjectX(double cord) {
    object.transform.translateX = cord;
}

void Render::translateObjectY(double cord) {
    object.transform.translateY = cord;
}

void Render::translateObjectZ(double cord) {
    object.transform.translateZ = cord;
}

void Render::scaleObject(double scale) {
    object.transform.scaleX = scale;
    object.transform.scaleY = scale;
    object.transform.scaleZ = scale;
}

void Render::rotateCameraX(double angle) {
    camera.angleX = -angle;
}

void Render::rotateCameraY(double angle) {
    camera.angleY = -angle;
}

void Render::rotateCameraZ(double angle) {
    camera.angleZ = -angle;
}

void Render::translateCameraX(double cord) {
    camera.translationX = -cord;
}

void Render::translateCameraY(double cord) {
    camera.translationY = -cord;
}

void Render::translateCameraZ(double cord) {
    camera.translationZ = -cord;
}

void Render::moveLightX(double cord) {
    light.setX(cord);
}

void Render::moveLightY(double cord) {
    light.setY(cord);
}

void Render::moveLightZ(double cord) {
    light.setZ(cord);
}

void Render::recreateObject() {
    Transformation tmp = object.transform;
    Properties prop = object.property;
    object = ellipsoid.generate_mesh();
    object.transform = tmp;
    object.property = prop;
}
