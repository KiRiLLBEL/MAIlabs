#include "canvas.h"
#include <QVector>
#include <QPainter>
Canvas::Canvas(QWidget *parent)
    : QWidget{parent}, heightStart(0), widthStart(0)
{

}

QVector<double> interpolate(double i0, double d0, double i1, double d1) {
    if(i0 == i1) {
        return {d0};
    }
    QVector<double> values;
    double a = (d1 - d0) / (i1 - i0);
    double d = d0;
    for(int i = int(i0); i <= int(i1); ++i) {
        values.push_back(d);
        d += a;
    }
    return values;
}

void drawLine(QPainter& painter, Vertex p0, Vertex p1, QColor color) {
    painter.setPen(color);
    if(abs(p1.x - p0.x) > abs(p1.y - p0.y)) {
        if(p0.x > p1.x) {
            std::swap(p1, p0);
        }
        QVector<double> ys = interpolate(p0.x, p0.y, p1.x, p1.y);
        for (int x = int(p0.x); x <= p1.x; ++x) {
            painter.drawPoint(x, int(ys[x - p0.x]));
        }
    } else {
        if(p0.y > p1.y) {
            std::swap(p1, p0);
        }
        QVector<double> xs = interpolate(p0.y, p0.x, p1.y, p1.x);
        for (int y = int(p0.y); y <= p1.y; ++y) {
            painter.drawPoint(int(xs[int(y - p0.y)]), y);
        }
    }
}

void drawWireframePolygon(QPainter& painter, const Vertex& p0, const Vertex& p1, const Vertex& p2, QColor color) {
    painter.setPen(color);
    drawLine(painter, p0, p1, color);
    drawLine(painter, p1, p2, color);
    drawLine(painter, p2, p0, color);
}

void Canvas::drawPolygon(QPainter& painter, Vertex p0, Vertex p1, Vertex p2, QColor color) {
    painter.setPen(color);
    if (p1.y < p0.y) {
        std::swap(p1, p0);
    }
    if (p2.y < p0.y) {
        std::swap(p2, p0);
    }
    if (p2.y < p1.y) {
        std::swap(p2, p1);
    }

    QVector<double> x01 = interpolate(p0.y, p0.x, p1.y, p1.x);
    QVector<double> z01 = interpolate(p0.y, p0.z, p1.y, p1.z);
    QVector<double> x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
    QVector<double> z12 = interpolate(p1.y, p1.z, p2.y, p2.z);
    QVector<double> x02 = interpolate(p0.y, p0.x, p2.y, p2.x);
    QVector<double> z02 = interpolate(p0.y, p0.z, p2.y, p2.z);

    x01.pop_back();
    QVector<double> x012 = x01 + x12;
    z01.pop_back();
    QVector<double> z012 = z01 + z12;

    int m = floor(double(x012.size()) / 2);
    QVector<double> x_left, x_right;
    QVector<double> z_left, z_right;
    if (x02[m] < x012[m]) {
        x_left = x02;
        x_right = x012;
        z_left = z02;
        z_right = z012;
    } else {
        x_left = x012;
        x_right = x02;
        z_left = z012;
        z_right = z02;
    }
    bool intersect = false;

    for(int y = int(p0.y); y <= int(p2.y); ++y) {
        if(y >= 0 && y < this->height()) {
            double x_l = x_left[int(y - p0.y)];
            double x_r = x_right[int(y - p0.y)];
            QVector<double> z_segment = interpolate(x_l, z_left[int(y - p0.y)], x_r, z_right[int(y - p0.y)]);
            for(int x = int(x_l); x <= int(x_r); ++x) {
                if(x >= 0 && x < this->width()) {
                    double z = z_segment[int(x - x_l)];
                    if(z > depth_buffer[x][y]) {
                        painter.drawPoint(x, y);
                        depth_buffer[x][y] = z;
                    }
                }
            }
        }
    }
}

Vertex Canvas::scalePoint(double x, double y, double z) {
    return {
        x * widthStart / this->width() + this->width() / 2.0,
        y * heightStart / this->height() + this->height() / 2.0,
        z
    };
}

Vertex Canvas::viewportToCanvas(double x, double y, double z) {
    return scalePoint((x * this->width()), y * this->height(), z);
}

Vertex Canvas::projectVertex(Vertex v) {
    return viewportToCanvas(v.x/-v.z, v.y/-v.z, 1/v.z);
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    depth_buffer = QVector<QVector<double>>(this->width() + 1, QVector<double>(this->height() + 1, 0));
    renderObjects(painter);
}

void Canvas::addObject(const Object &obj) {
    objects.push_back(obj);
}

bool Canvas::back_facing(const Object& object, const Polygon& polygon) const {
    Vertex p1 = object.vertices[polygon.v1];
    Vertex p2 = object.vertices[polygon.v2];
    Vertex p3 = object.vertices[polygon.v3];
    Vertex vec1 = p2 - p1;
    Vertex vec2 = p3 - p1;
    Vertex N = vec1^vec2;
    if(N*(-1^p1) <= 0)
        return true;
    return false;
}

Vertex Canvas::applyTransform(const Vertex& v, const Object& obj) const {
    Vertex res = v;
    res.scaleModel(obj.transform.scale);
    res.rotateX(obj.transform.angle_x);
    res.rotateY(obj.transform.angle_y);
    res.rotateZ(obj.transform.angle_z);
    res.shiftX(obj.transform.x);
    res.shiftY(obj.transform.y);
    res.shiftZ(obj.transform.z);
    res.rotateX(camera.angle_x);
    res.rotateY(camera.angle_y);
    res.rotateZ(camera.angle_z);
    res.shiftX(camera.x);
    res.shiftY(camera.y);
    res.shiftZ(camera.z);
    return res;
}

Vertex intersect(Vertex v1, Vertex v2, Vertex planePoint, Vertex planeNormal) {
    Vertex edge = v2 - v1;
    double t = planeNormal * (planePoint - v1) / (planeNormal * edge);
    return v1 + (t ^ edge);
}

QVector<Polygon> Canvas::splitPolygonIntoTriangles(Polygon polygon, Vertex planePoint, Vertex planeNormal, Object& object) {
    QVector<int> frontVertices;
    QVector<int> backVertices;

    int indices[] = {
        polygon.v1,
        polygon.v2,
        polygon.v3,
        polygon.v1
    };

    for(int i = 0; i < 3; ++i) {
        int index1 = indices[i];
        int index2 = indices[i + 1];

        Vertex v1 = object.vertices[index1];
        Vertex v2 = object.vertices[index2];

        double d1 = planeNormal*(v1 - planePoint);
        double d2 = planeNormal*(v2 - planePoint);

        if(d1 < 0)
            frontVertices.push_back(index1);
        if(d1 * d2 < 0) {
            Vertex v = intersect(v1, v2, planePoint, planeNormal);
            object.vertices.push_back(v);
            int newIndex = object.vertices.size() - 1;
            frontVertices.push_back(newIndex);
        }
    }
    QVector<Polygon> result;
    for (size_t i = 2; i < frontVertices.size(); ++i) {
        result.emplace_back(frontVertices[0], frontVertices[i - 1], frontVertices[i], polygon.color);
    }

    return result;
}

void Canvas::clipObject(Object& object, Vertex planePoint, Vertex planeNormal) {
    QVector<Polygon> clippedPolygons;
    for (const Polygon& polygon : object.polygons) {
        QVector<Polygon> splitPolygons = splitPolygonIntoTriangles(polygon, planePoint, planeNormal, object);
        clippedPolygons += splitPolygons;
    }

    object.polygons = clippedPolygons;
}

void Canvas::renderObjects(QPainter& painter) {
    for(const Object& object: objects) {
        Object newObject = object;
        newObject.vertices.clear();
        for(const Vertex& vertex: object.vertices) {
            newObject.vertices.push_back(applyTransform(vertex, object));
        }
        Vertex nearPlanePoint = {0, 0, 1}; // ближняя плоскость находится в точке z=1
        Vertex nearPlaneNormal = {0, 0, -1}; // нормаль ближней плоскости направлена вдоль оси z в отрицательном направлении
        clipObject(newObject, nearPlanePoint, nearPlaneNormal);
        if(invisibleFaces) {
            for(const Polygon& polygon: newObject.polygons) {
                if(!back_facing(newObject, polygon)) {
                    drawPolygon(
                        painter,
                        projectVertex(newObject.vertices[polygon.v1]),
                        projectVertex(newObject.vertices[polygon.v2]),
                        projectVertex(newObject.vertices[polygon.v3]),
                        polygon.color
                        );
                }
            }
        } else {
            for(const Polygon& polygon: newObject.polygons) {
                drawWireframePolygon(
                    painter,
                    projectVertex(newObject.vertices[polygon.v1]),
                    projectVertex(newObject.vertices[polygon.v2]),
                    projectVertex(newObject.vertices[polygon.v3]),
                    Qt::white
                    );
            }
        }
    }
}

void Canvas::updateObjects(Transformation transform) {
    for(Object& object: objects) {
        object.transform = transform;
    }
}

void Canvas::rotateXObjects(double angle) {
    for(Object& object: objects) {
        object.transform.angle_x = angle;
    }
}

void Canvas::rotateYObjects(double angle) {
    for(Object& object: objects) {
        object.transform.angle_y = angle;
    }
}

void Canvas::rotateZObjects(double angle) {
    for(Object& object: objects) {
        object.transform.angle_z = angle;
    }
}

void Canvas::shiftXObjects(double shift) {
    for(Object& object: objects) {
        object.transform.x = shift;
    }
}

void Canvas::shiftYObjects(double shift) {
    for(Object& object: objects) {
        object.transform.y = shift;
    }
}

void Canvas::shiftZObjects(double shift) {
    for(Object& object: objects) {
        object.transform.z = shift;
    }
}

void Canvas::scaleObjects(double scale) {
    for(Object& object: objects) {
        object.transform.scale = scale;
    }
}

