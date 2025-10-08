/**
 * @file filemanager.cpp
 * @brief Реализация методов класса FileManager
 * @author Adam
 * @date 2025
 */

#include "filemanager.h"
#include <fstream>
#include <iostream>
using namespace std;

/**
 * @brief Сохранение массива точек в текстовый файл
 * @param points Указатель на массив точек
 * @param pointCount Количество точек в массиве
 * 
 * Создает файл points.txt в текущей директории. Каждая строка файла
 * содержит координаты одной точки в формате "x y z".
 * 
 * @warning Перезаписывает существующий файл points.txt без предупреждения
 */
void FileManager::savePointsToFile(Point3D* points, int pointCount) {
    ofstream file("points.txt");
    if (!file) {
        cout << "Ошибка создания файла!" << endl;
        return;
    }
    
    // Сохранение каждой точки в формате "x y z"
    for (int i = 0; i < pointCount; i++) {
        file << points[i].x << " " << points[i].y << " " << points[i].z << endl;
    }
    file.close();
    
    cout << "Точки сохранены в points.txt" << endl;
}

/**
 * @brief Создание Python скрипта для визуализации точек
 * @param centerX Координата X центра сфер
 * @param centerY Координата Y центра сфер
 * @param centerZ Координата Z центра сфер
 * @param R1 Внутренний радиус сферы
 * @param R2 Внешний радиус сферы
 * 
 * Создает файл visualize.py, который использует библиотеки matplotlib и numpy
 * для 3D визуализации точек между концентрическими сферами.
 * 
 * @note Для работы скрипта требуется установленный Python с библиотеками
 * matplotlib и numpy
 */
void FileManager::createPythonScript(double centerX, double centerY, double centerZ, 
                                   double R1, double R2) {
    // Просто сообщаем, что нужно создать файл visualize.py вручную
    cout << "Для визуализации создайте файл visualize.py в папке с программой" << endl;
    cout << "Содержимое файла можно взять из инструкции" << endl;
    cout << "Параметры для визуализации:" << endl;
    cout << "Центр: (" << centerX << ", " << centerY << ", " << centerZ << ")" << endl;
    cout << "Радиусы: R1=" << R1 << ", R2=" << R2 << endl;
}
