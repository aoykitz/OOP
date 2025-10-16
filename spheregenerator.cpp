/**
 * @file spheregenerator.cpp
 * @brief Реализация методов класса SphereGenerator
 * @author Adam
 * @date 2025
 */

#include "spheregenerator.h"
#include <cmath>
#include <random>
#include <iostream>
using namespace std;

// Определяем константу PI, если она не определена
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Конструктор класса SphereGenerator
 * @param cx Координата X центра сфер
 * @param cy Координата Y центра сфер
 * @param cz Координата Z центра сфер
 * @param r1 Внутренний радиус R1
 * @param r2 Внешний радиус R2
 * 
 * Инициализирует генератор с заданными параметрами сфер. Если параметры
 * не указаны, используются значения по умолчанию.
 */
SphereGenerator::SphereGenerator(double cx, double cy, double cz, double r1, double r2) 
    : centerX(cx), centerY(cy), centerZ(cz), radius1(r1), radius2(r2) {}

/**
 * @brief Генерация случайной точки между концентрическими сферами
 * @return Point3D Случайная точка в сферическом слое
 * 
 * Алгоритм генерации:
 * 1. Генерация случайных параметров в сферических координатах
 * 2. Преобразование в декартовы координаты относительно центра
 * 3. Возврат точки с равномерным распределением в объеме
 */
Point3D SphereGenerator::generatePoint() {
    // Инициализация генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 1.0);
    
    // Генерация случайных параметров в сферических координатах
    double u = dist(gen); // Для радиуса
    double v = dist(gen); // Для угла theta
    double w = dist(gen); // Для угла phi
    
    // Линейная интерполяция радиуса между R1 и R2
    double r = radius1 + (radius2 - radius1) * u;
    
    // Углы в сферических координатах
    double theta = 2 * M_PI * v;        // Азимутальный угол [0, 2π]
    double phi = acos(2 * w - 1.0);     // Полярный угол [0, π]
    
    // Преобразование сферических координат в декартовы
    double sin_phi = sin(phi);
    double x = centerX + r * sin_phi * cos(theta);
    double y = centerY + r * sin_phi * sin(theta);
    double z = centerZ + r * cos(phi);
    
    return Point3D(x, y, z);
}

/**
 * @brief Установка нового центра сфер
 * @param cx Новая координата X центра
 * @param cy Новая координата Y центра
 * @param cz Новая координата Z центра
 */
void SphereGenerator::setCenter(double cx, double cy, double cz) {
    centerX = cx;
    centerY = cy;
    centerZ = cz;
}

/**
 * @brief Установка новых радиусов сфер
 * @param r1 Новый внутренний радиус R1
 * @param r2 Новый внешний радиус R2
 * 
 * @note R1 должен быть меньше или равен R2
 */
void SphereGenerator::setRadii(double r1, double r2) {
    radius1 = r1;
    radius2 = r2;
}

/**
 * @brief Получение координаты X центра сфер
 * @return Текущая координата X центра
 */
double SphereGenerator::getCenterX() const {
    return centerX;
}

/**
 * @brief Получение координаты Y центра сфер
 * @return Текущая координата Y центра
 */
double SphereGenerator::getCenterY() const {
    return centerY;
}

/**
 * @brief Получение координаты Z центра сфер
 * @return Текущая координата Z центра
 */
double SphereGenerator::getCenterZ() const {
    return centerZ;
}

/**
 * @brief Получение внутреннего радиуса R1
 * @return Текущее значение внутреннего радиуса
 */
double SphereGenerator::getR1() const {
    return radius1;
}

/**
 * @brief Получение внешнего радиуса R2
 * @return Текущее значение внешнего радиуса
 */
double SphereGenerator::getR2() const {
    return radius2;
}

/**
 * @brief Вывод текущих настроек генератора на экран
 * 
 * Отображает текущий центр и радиусы сфер в удобочитаемом формате.
 */
void SphereGenerator::printSettings() {
    cout << "Центр: (" << centerX << ", " << centerY << ", " << centerZ << ")" << endl;
    cout << "Радиусы: R1=" << radius1 << ", R2=" << radius2 << endl;
}
