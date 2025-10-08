/**
 * @file point3d.cpp
 * @brief Реализация методов структуры Point3D
 * @author Ваше Имя
 * @version 1.0
 * @date 2023-12-01
 */

#include "point3d.h"
#include <iostream>
using namespace std;

Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

void Point3D::print() {
    cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}
