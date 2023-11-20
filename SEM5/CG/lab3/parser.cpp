#include <fstream>
#include <iostream>
#include <sstream>
#include "parser.h"
#include <QDebug>
#include <QColor>

int split_string(const std::string& str, const char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    std::getline(ss, token, delimiter);
    return std::stoi(token);
}

QColor randomColor() {
    QColor Colors[] = {
            Qt::white, Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow, Qt::gray
    };
    int index = rand() % 7;
    return Colors[index];
}

Object CreateObjectFromFile(const QString& path) {
    std::ifstream file(path.toStdString());
    if(!file) {
        qDebug() << "File not found " << path << "\n";
        exit(1);
    }
    std::string line;
    Object obj;
    double minZ = 1e9;
    double minX = 1e9;
    double minY = 1e9;
    while(std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;
        if(type == "v") {
            double x, y, z;
            ss >> x >> y >> z;
            obj.addVertex(x, y, z);
            if(z < minZ) {
                minZ = z;
            }
        } else if(type == "f") {
            std::string v1, v2, v3, v4;
            ss >> v1 >> v2 >> v3 >> v4;
            QColor color = randomColor();
            if(!v4.empty()) {
                obj.addPolygon(
                        split_string(v3, '/'),
                        split_string(v4, '/'),
                        split_string(v1, '/'),
                        color
                );
                obj.addPolygon(
                        split_string(v1, '/'),
                        split_string(v2, '/'),
                        split_string(v3, '/'),
                        color
                        );
            } else {
                obj.addPolygon(
                        split_string(v1, '/'),
                        split_string(v2, '/'),
                        split_string(v3, '/'),
                        color
                );
            }
        }
    }
    // obj.transform.z = (minZ <= 1) ? -1 * minZ + 5 : 0;
    return obj;
}
