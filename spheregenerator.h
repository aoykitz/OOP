/**
 * @file spheregenerator.h
 * @brief Заголовочный файл для класса SphereGenerator
 * @author Adam
 * @date 2025
 */

#pragma once
#include "point3d.h"

/**
 * @class SphereGenerator
 * @brief Класс для генерации случайных точек между двумя концентрическими сферами
 * 
 * Этот класс генерирует точки, равномерно распределенные в объеме между
 * двумя концентрическими сферами с заданными радиусами и центром.
 */
class SphereGenerator {
private:
    double centerX; ///< Координата X центра сфер
    double centerY; ///< Координата Y центра сфер
    double centerZ; ///< Координата Z центра сфер
    double radius1; ///< Внутренний радиус сферы (R1)
    double radius2; ///< Внешний радиус сферы (R2)

public:
    /**
     * @brief Конструктор генератора сфер
     * @param cx Координата X центра (по умолчанию 0)
     * @param cy Координата Y центра (по умолчанию 0)
     * @param cz Координата Z центра (по умолчанию 0)
     * @param r1 Внутренний радиус R1 (по умолчанию 1)
     * @param r2 Внешний радиус R2 (по умолчанию 2)
     */
    SphereGenerator(double cx = 0, double cy = 0, double cz = 0, double r1 = 1, double r2 = 2);
    
    /**
     * @brief Генерация случайной точки между сферами
     * @return Point3D Случайная точка в сферическом слое
     * 
     * Использует сферические координаты для равномерного распределения точек
     * в объеме между двумя концентрическими сферами.
     */
    Point3D generatePoint();
    
    /**
     * @brief Установка центра сфер
     * @param cx Координата X центра
     * @param cy Координата Y центра
     * @param cz Координата Z центра
     */
    void setCenter(double cx, double cy, double cz);
    
    /**
     * @brief Установка радиусов сфер
     * @param r1 Внутренний радиус R1
     * @param r2 Внешний радиус R2
     */
    void setRadii(double r1, double r2);
    
    /**
     * @brief Получение координаты X центра
     * @return Координата X центра сфер
     */
    double getCenterX() const;
    
    /**
     * @brief Получение координаты Y центра
     * @return Координата Y центра сфер
     */
    double getCenterY() const;
    
    /**
     * @brief Получение координаты Z центра
     * @return Координата Z центра сфер
     */
    double getCenterZ() const;
    
    /**
     * @brief Получение внутреннего радиуса
     * @return Внутренний радиус R1
     */
    double getR1() const;
    
    /**
     * @brief Получение внешнего радиуса
     * @return Внешний радиус R2
     */
    double getR2() const;
    
    /**
     * @brief Вывод текущих настроек генератора
     */
    void printSettings();
};
