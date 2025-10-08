/**
 * @file filemanager.h
 * @brief Заголовочный файл для класса FileManager
 * @author Adam
 * @date 2025
 */

#pragma once
#include "point3d.h"

/**
 * @class FileManager
 * @brief Класс для работы с файлами
 * 
 * Предоставляет статические методы для сохранения точек в файл
 * и создания Python скрипта для визуализации.
 */
class FileManager {
public:
    /**
     * @brief Сохранение точек в текстовый файл
     * @param points Массив точек для сохранения
     * @param pointCount Количество точек в массиве
     * 
     * Формат файла: каждая строка содержит координаты x y z через пробел
     */
    static void savePointsToFile(Point3D* points, int pointCount);
    
    /**
     * @brief Создание Python скрипта для визуализации
     * @param centerX Координата X центра сфер
     * @param centerY Координата Y центра сфер
     * @param centerZ Координата Z центра сфер
     * @param R1 Внутренний радиус
     * @param R2 Внешний радиус
     * 
     * Создает файл visualize.py с использованием matplotlib
     * для 3D визуализации точек с заданными параметрами сфер.
     */
    static void createPythonScript(double centerX, double centerY, double centerZ,
                                 double R1, double R2);
};
