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

void Canvas::drawPolygon(QPainter& painter, Vertex p0, Vertex p1, Vertex p2, QColor color, double ambient, double diffuse, double specular, double shininess, Vertex light_pos) {
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
    QVector<double> nx01 = interpolate(p0.y, p0.nx, p1.y, p1.nx);
    QVector<double> ny01 = interpolate(p0.y, p0.ny, p1.y, p1.ny);
    QVector<double> nz01 = interpolate(p0.y, p0.nz, p1.y, p1.nz);


    QVector<double> x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
    QVector<double> z12 = interpolate(p1.y, p1.z, p2.y, p2.z);
    QVector<double> nx12 = interpolate(p1.y, p1.nx, p2.y, p2.nx);
    QVector<double> ny12 = interpolate(p1.y, p1.ny, p2.y, p2.ny);
    QVector<double> nz12 = interpolate(p1.y, p1.nz, p2.y, p2.nz);

    QVector<double> x02 = interpolate(p0.y, p0.x, p2.y, p2.x);
    QVector<double> z02 = interpolate(p0.y, p0.z, p2.y, p2.z);
    QVector<double> nx02 = interpolate(p0.y, p0.nx, p2.y, p2.nx);
    QVector<double> ny02 = interpolate(p0.y, p0.ny, p2.y, p2.ny);
    QVector<double> nz02 = interpolate(p0.y, p0.nz, p2.y, p2.nz);



    x01.pop_back();
    QVector<double> x012 = x01 + x12;
    z01.pop_back();
    QVector<double> z012 = z01 + z12;
    nx01.pop_back();
    QVector<double> nx012 = nx01 + nx12;
    ny01.pop_back();
    QVector<double> ny012 = ny01 + ny12;
    nz01.pop_back();
    QVector<double> nz012 = nz01 + nz12;

    int m = floor(double(x012.size()) / 2);
    QVector<double> x_left, x_right;
    QVector<double> z_left, z_right;
    QVector<double> nx_left, nx_right;
    QVector<double> ny_left, ny_right;
    QVector<double> nz_left, nz_right;
    if (x02[m] < x012[m]) {
        x_left = x02;
        x_right = x012;
        z_left = z02;
        z_right = z012;
        nx_left = nx02;
        nx_right = nx012;
        ny_left = ny02;
        ny_right = ny012;
        nz_left = nz02;
        nz_right = nz012;
    } else {
        x_left = x012;
        x_right = x02;
        z_left = z012;
        z_right = z02;
        nx_left = nx012;
        nx_right = nx02;
        ny_left = ny012;
        ny_right = ny02;
        nz_left = nz012;
        nz_right = nz02;
    }
    bool intersect = false;

    for(int y = int(p0.y); y <= int(p2.y); ++y) {
        if(y >= 0 && y < this->height()) {
            double x_l = x_left[int(y - p0.y)];
            double x_r = x_right[int(y - p0.y)];
            QVector<double> z_segment = interpolate(x_l, z_left[int(y - p0.y)], x_r, z_right[int(y - p0.y)]);
            QVector<double> nx_segment = interpolate(x_l, nx_left[int(y - p0.y)], x_r, nx_right[int(y - p0.y)]);
            QVector<double> ny_segment = interpolate(x_l, ny_left[int(y - p0.y)], x_r, ny_right[int(y - p0.y)]);
            QVector<double> nz_segment = interpolate(x_l, nz_left[int(y - p0.y)], x_r, nz_right[int(y - p0.y)]);
            for(int x = int(x_l); x <= int(x_r); ++x) {
                if(x >= 0 && x < this->width()) {
                    double z = z_segment[int(x - x_l)];
                    Vertex np = {nx_segment[int(x - x_l)], ny_segment[int(x - x_l)], nz_segment[int(x - x_l)]};
                    if(z > depth_buffer[x][y]) {
                        double lx = ((x - this->width() / 2.0)  * (this->width() / double(widthStart)) / this->width() / (1/-z)) - light_pos.x ;
                        double ly = ((x - this->height() / 2.0)  * (this->height() / double(heightStart)) / this->height() / (1/-z)) - light_pos.y;
                        double lz = (1/z) - light_pos.z;

                        double length = sqrt(lx * lx + ly * ly + lz * lz);
                        Vertex light = {lx/length, ly/length, lz/length};
                        double dot = np*light;
                        Vertex r = {2 * dot * np.x - light.x, 2 * dot * np.y - light.y, 2 * dot * np.z - light.z};

                        double diffIntensity = diffuse * std::max(dot, 0.0);
                        double specularIntensity = specular * pow(std::max(r*Vertex(0,0,1), 0.0), shininess);
                        double intensity = ambient + diffIntensity + specularIntensity;
                        float rc, gc, bc;
                        color.getRgbF(&rc, &gc, &bc);
                        QColor cur_color;
                        cur_color.setRgbF(rc * intensity, gc * intensity, bc * intensity);
                        painter.setPen(cur_color);
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
    Vertex out = viewportToCanvas(v.x/-v.z, v.y/-v.z, 1/v.z);
    out.nx = v.nx;
    out.ny = v.ny;
    out.nz = v.nz;
    return out;
}

Vertex computeNormal(Vertex v1, Vertex v2, Vertex v3) {
    Vertex normal;
    normal.x = (v2.y - v1.y) * (v3.z - v1.z) - (v2.z - v1.z) * (v3.y - v1.y);
    normal.y = (v2.z - v1.z) * (v3.x - v1.x) - (v2.x - v1.x) * (v3.z - v1.z);
    normal.z = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
    return (-1.0)^normal;
}

void computeVertexNormals(Object& object) {
    for (Vertex& vertex : object.vertices) {
        vertex.nx = 0;
        vertex.ny = 0;
        vertex.nz = 0;
    }

    for (Polygon& polygon : object.polygons) {
        Vertex& v1 = object.vertices[polygon.v1];
        Vertex& v2 = object.vertices[polygon.v2];
        Vertex& v3 = object.vertices[polygon.v3];

        Vertex normal = computeNormal(v1, v2, v3);

        v1.nx += normal.x;
        v1.ny += normal.y;
        v1.nz += normal.z;

        v2.nx += normal.x;
        v2.ny += normal.y;
        v2.nz += normal.z;

        v3.nx += normal.x;
        v3.ny += normal.y;
        v3.nz += normal.z;
    }

    for (Vertex& vertex : object.vertices) {
        float length = sqrt(vertex.nx * vertex.nx + vertex.ny * vertex.ny + vertex.nz * vertex.nz);
        vertex.nx /= length;
        vertex.ny /= length;
        vertex.nz /= length;
    }
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    depth_buffer = QVector<QVector<double>>(this->width() + 1, QVector<double>(this->height() + 1, 0));
    renderObjects(painter);
}

void Canvas::addObject(const Object &obj) {
    object_on_scene = obj;
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
    Object newObject = object_on_scene;
    newObject.vertices.clear();
    for(const Vertex& vertex: object_on_scene.vertices) {
        newObject.vertices.push_back(applyTransform(vertex, object_on_scene));
    }
    Vertex nearPlanePoint = {0, 0, 1};
    Vertex nearPlaneNormal = {0, 0, -1};
    Vertex light_pos = point_light;
    light_pos.rotateX(camera.angle_x);
    light_pos.rotateY(camera.angle_y);
    light_pos.rotateZ(camera.angle_z);
    light_pos.shiftX(camera.x);
    light_pos.shiftY(camera.y);
    light_pos.shiftZ(camera.z);
    clipObject(newObject, nearPlanePoint, nearPlaneNormal);
    computeVertexNormals(newObject);
    if(invisibleFaces) {
        for(const Polygon& polygon: newObject.polygons) {
            if(!back_facing(newObject, polygon)) {
                drawPolygon(
                    painter,
                    projectVertex(newObject.vertices[polygon.v1]),
                    projectVertex(newObject.vertices[polygon.v2]),
                    projectVertex(newObject.vertices[polygon.v3]),
                    polygon.color,
                    newObject.property.ambient,
                    newObject.property.diffuse,
                    newObject.property.specular,
                    newObject.property.shininess,
                    light_pos
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

void Canvas::updateObjects(Transformation transform) {
    object_on_scene.transform = transform;
}

void Canvas::rotateXObjects(double angle) {
    object_on_scene.transform.angle_x = angle;
}

void Canvas::rotateYObjects(double angle) {
    object_on_scene.transform.angle_y = angle;
}

void Canvas::rotateZObjects(double angle) {
    object_on_scene.transform.angle_z = angle;
}

void Canvas::shiftXObjects(double shift) {
    object_on_scene.transform.x = shift;
}

void Canvas::shiftYObjects(double shift) {
    object_on_scene.transform.y = shift;
}

void Canvas::shiftZObjects(double shift) {
    object_on_scene.transform.z = shift;
}

void Canvas::scaleObjects(double scale) {
    object_on_scene.transform.scale = scale;
}

