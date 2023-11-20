#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QVector>
#include "object.h"

class Canvas : public QWidget
{
    Q_OBJECT
private:
    QVector<QVector<double>> depth_buffer;
protected:
    void paintEvent(QPaintEvent *event) override;
    void renderObjects(QPainter& painter);
    void drawPolygon(QPainter& painter, Vertex p0, Vertex p1, Vertex p2, QColor color, double ambient, double diffuse, double specular, double shininess, Vertex light_pos);
public:
    Object object_on_scene;
    explicit Canvas(QWidget *parent = nullptr);
    Vertex scalePoint(double x, double y, double z);
    Vertex viewportToCanvas(double x, double y, double z);
    Vertex projectVertex(Vertex v);
    Vertex applyTransform(const Vertex& v, const Object& obj) const;
    QVector<Polygon> splitPolygonIntoTriangles(Polygon polygon, Vertex planePoint, Vertex planeNormal, Object& object);
    void clipObject(Object& object, Vertex planePoint, Vertex planeNormal);
    bool back_facing(const Object& object, const Polygon& polygon) const ;
    void addObject(const Object& obj);
    void updateObjects(Transformation transform);
    void rotateXObjects(double angle);
    void rotateYObjects(double angle);
    void rotateZObjects(double angle);
    void shiftXObjects(double shift);
    void shiftYObjects(double shift);
    void shiftZObjects(double shift);
    void scaleObjects(double scale);
    bool invisibleFaces = false;
    int heightStart = 0;
    int widthStart = 0;
    Transformation camera;
    Vertex point_light;
};

#endif // CANVAS_H
