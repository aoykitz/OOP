/**
 * @file main.cpp
 * @brief Главный файл программы для генерации точек между концентрическими сферами
 * @author Adam
 * @date 2025
 * 
 * @mainpage Лабораторная работа №1 по ООП
 * 
 * Программа для генерации случайных точек в объеме между двумя концентрическими сферами.
 * 
 * Функциональность:
 * - Настройка центра и радиусов сфер
 * - Генерация случайных точек в сферическом слое
 * - Просмотр и ручное добавление точек
 * - Сохранение точек в файл
 * - Создание Python скрипта для визуализации
 * 
 * @see SphereGenerator
 * @see Point3D
 * @see FileManager
 * @see Menu
 */

#include <iostream>
#include "point3d.h"
#include "spheregenerator.h"
#include "filemanager.h"
#include "menu.h"
using namespace std;

// Максимальное количество точек
const int MAX_POINTS = 10000;

/**
 * @brief Главная функция программы
 * @return int Код завершения программы
 * 
 * Создает экземпляр генератора точек и предоставляет пользователю
 * интерактивное меню для работы с программой.
 */
int main() {
    setlocale(LC_ALL, "Russian");
    
    SphereGenerator generator;
    Point3D points[MAX_POINTS]; // Статический массив вместо vector
    int pointCount = 0;         // Текущее количество точек
    int choice;
    
    cout << "=== ПРОГРАММА ДЛЯ ГЕНЕРАЦИИ ТОЧЕК МЕЖДУ КОНЦЕНТРИЧЕСКИМИ СФЕРАМИ ===" << endl;
    cout << "Вариант №4: Точки заполняют область пространства между двумя концентрическими сферами" << endl;
    cout << "Максимальное количество точек: " << MAX_POINTS << endl;
    
    do {
        Menu::showMainMenu();
        cin >> choice;
        Menu::clearInput();
        
        switch(choice) {
            case 1: {
                // Настройка параметров сфер
                double cx, cy, cz, r1, r2;
                cout << "Введите координаты центра сфер (x y z): ";
                cin >> cx >> cy >> cz;
                cout << "Введите внутренний радиус R1: ";
                cin >> r1;
                cout << "Введите внешний радиус R2: ";
                cin >> r2;
                
                generator.setCenter(cx, cy, cz);
                generator.setRadii(r1, r2);
                cout << "Настройки сохранены" << endl;
                break;
            }
            
            case 2: {
                // Генерация точек
                int count;
                cout << "Сколько точек сгенерировать? ";
                cin >> count;
                
                if (count <= 0) {
                    break;
                }
                
                if (pointCount + count > MAX_POINTS) {
                    cout << "Превышен максимальный лимит точек (" << MAX_POINTS << ")" << endl;
                    cout << "Доступно для генерации: " << MAX_POINTS - pointCount << " точек" << endl;
                    break;
                }
                
                for (int i = 0; i < count; i++) {
                    points[pointCount + i] = generator.generatePoint();
                }
                pointCount += count;
                
                cout << "Сгенерировано " << count << " точек!" << endl;
                cout << "Всего точек: " << pointCount << endl;
                break;
            }
            
            case 3: {
                // Просмотр точки
                if (pointCount == 0) {
                    cout << "Сначала сгенерируйте точки." << endl;
                    break;
                }
                
                int index;
                cout << "Введите номер точки (0-" << pointCount-1 << "): ";
                cin >> index;
                
                if (index < 0 || index >= pointCount) {
                    cout << "Неверный номер!" << endl;
                    break;
                }
                
                cout << "Точка " << index << ": ";
                points[index].print();
                break;
            }
            
            case 4: {
                // Ручное добавление точки
                if (pointCount >= MAX_POINTS) {
                    cout << "Достигнут максимальный лимит точек (" << MAX_POINTS << ")" << endl;
                    break;
                }
                
                double x, y, z;
                cout << "Введите координаты точки (x y z): ";
                cin >> x >> y >> z;
                
                points[pointCount] = Point3D(x, y, z);
                pointCount++;
                
                cout << "Всего точек: " << pointCount << endl;
                break;
            }
            
            case 5: {
                // Сохранение и создание скрипта визуализации
                if (pointCount == 0) {
                    cout << "Нет точек для сохранения" << endl;
                    break;
                }
                
                FileManager::savePointsToFile(points, pointCount);
                FileManager::createPythonScript(generator.getCenterX(), generator.getCenterY(), 
                                  generator.getCenterZ(), generator.getR1(), generator.getR2());
                break;
            }
            
            case 6: {
                // Показать настройки
                cout << "\nТекущие настройки:" << endl;
                generator.printSettings();
                cout << "Количество точек в массиве: " << pointCount << endl;
                cout << "Максимальное количество точек: " << MAX_POINTS << endl;
                break;
            }
            
            case 0: {
                cout << "Выход из программы..." << endl;
                break;
            }
            
            default: {
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
            }
        }
        
    } while (choice != 0);
    
    return 0;
}
