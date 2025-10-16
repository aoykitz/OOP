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

void FileManager::createPythonScript(double centerX, double centerY, double centerZ,
                                   double R1, double R2) {
    ofstream file("visualize.py");

    file << "import numpy as np\n";
    file << "import matplotlib.pyplot as plt\n";
    file << "from mpl_toolkits.mplot3d import Axes3D\n\n";

    file << "def read_points(filename):\n";
    file << "    points = []\n";
    file << "    with open(filename, 'r') as f:\n";
    file << "        for line in f:\n";
    file << "            if line.strip() and not line.startswith('#'):\n";
    file << "                coords = list(map(float, line.split()))\n";
    file << "                if len(coords) == 3:\n";
    file << "                    points.append(coords)\n";
    file << "    return np.array(points)\n\n";

    file << "def create_sphere(center_x, center_y, center_z, radius, resolution=30):\n";
    file << "    u = np.linspace(0, 2 * np.pi, resolution)\n";
    file << "    v = np.linspace(0, np.pi, resolution)\n";
    file << "    x = center_x + radius * np.outer(np.cos(u), np.sin(v))\n";
    file << "    y = center_y + radius * np.outer(np.sin(u), np.sin(v))\n";
    file << "    z = center_z + radius * np.outer(np.ones(np.size(u)), np.cos(v))\n";
    file << "    return x, y, z\n\n";

    file << "def main():\n";
    file << "    try:\n";
    file << "        points = read_points('points.txt')\n";
    file << "        print(f\"Прочитано {len(points)} точек\")\n\n";

    file << "        # Параметры из C++ программы\n";
    file << "        center_x = " << centerX << "\n";
    file << "        center_y = " << centerY << "\n";
    file << "        center_z = " << centerZ << "\n";
    file << "        r1 = " << R1 << "\n";
    file << "        r2 = " << R2 << "\n\n";

    file << "        fig = plt.figure(figsize=(14, 10))\n";
    file << "        ax = fig.add_subplot(111, projection='3d')\n\n";

    file << "        # Отображение точек\n";
    file << "        ax.scatter(points[:, 0], points[:, 1], points[:, 2], \n";
    file << "                   c='blue', alpha=0.6, s=20, label=f'Точки ({len(points)} шт)')\n\n";

    file << "        # Отображение центра сфер (большая красная звезда)\n";
    file << "        ax.scatter([center_x], [center_y], [center_z], \n";
    file << "                   c='red', s=200, marker='*', label=f'Центр ({center_x:.1f}, {center_y:.1f}, {center_z:.1f})')\n\n";

    file << "        # Создание сфер\n";
    file << "        x1, y1, z1 = create_sphere(center_x, center_y, center_z, r1)\n";
    file << "        x2, y2, z2 = create_sphere(center_x, center_y, center_z, r2)\n\n";

    file << "        # Внутренняя сфера\n";
    file << "        ax.plot_wireframe(x1, y1, z1, color='red', alpha=0.3, linewidth=1, \n";
    file << "                         label=f'Внутренняя сфера R1={r1:.2f}')\n\n";

    file << "        # Внешняя сфера\n";
    file << "        ax.plot_wireframe(x2, y2, z2, color='green', alpha=0.3, linewidth=1, \n";
    file << "                         label=f'Внешняя сфера R2={r2:.2f}')\n\n";

    file << "        # Настройка осей - ФИКСИРОВАННЫЕ ГРАНИЦЫ!\n";
    file << "        ax.set_xlabel('Ось X')\n";
    file << "        ax.set_ylabel('Ось Y')\n";
    file << "        ax.set_zlabel('Ось Z')\n";
    file << "        \n";
    file << "        # ФИКСИРОВАННЫЕ ГРАНИЦЫ ОСЕЙ от -10 до 10\n";
    file << "        axis_limit = 10\n";
    file << "        ax.set_xlim(-axis_limit, axis_limit)\n";
    file << "        ax.set_ylim(-axis_limit, axis_limit)\n";
    file << "        ax.set_zlim(-axis_limit, axis_limit)\n";
    file << "        \n";
    file << "        # Добавляем координатную сетку\n";
    file << "        ax.grid(True, alpha=0.3)\n";
    file << "        \n";
    file << "        # Отображаем координатные оси через центр (0,0,0)\n";
    file << "        ax.quiver(0, 0, 0, axis_limit, 0, 0, color='r', arrow_length_ratio=0.1, linewidth=1, alpha=0.7)\n";
    file << "        ax.quiver(0, 0, 0, 0, axis_limit, 0, color='g', arrow_length_ratio=0.1, linewidth=1, alpha=0.7)\n";
    file << "        ax.quiver(0, 0, 0, 0, 0, axis_limit, color='b', arrow_length_ratio=0.1, linewidth=1, alpha=0.7)\n";
    file << "        \n";
    file << "        ax.set_title(f'Точки между концентрическими сферами\\\\nЦентр: ({center_x:.1f}, {center_y:.1f}, {center_z:.1f}) R1={r1:.1f} R2={r2:.1f}')\n";
    file << "        ax.legend()\n\n";

    file << "        # Статистика\n";
    file << "        distances = np.sqrt((points[:, 0] - center_x)**2 + \n";
    file << "                           (points[:, 1] - center_y)**2 + \n";
    file << "                           (points[:, 2] - center_z)**2)\n";
    file << "        print(\"=\" * 60)\n";
    file << "        print(f\"ЦЕНТР СФЕР: ({center_x:.2f}, {center_y:.2f}, {center_z:.2f})\")\n";
    file << "        print(f\"Радиусы: R1={r1:.2f}, R2={r2:.2f}\")\n";
    file << "        print(f\"Фактические: min={np.min(distances):.2f}, max={np.max(distances):.2f}\")\n";
    file << "        print(\"Границы осей: от -10 до 10\")\n";
    file << "        print(\"=\" * 60)\n\n";

    file << "        plt.tight_layout()\n";
    file << "        plt.show()\n\n";

    file << "    except FileNotFoundError:\n";
    file << "        print(\"Файл points.txt не найден! Сначала запустите C++ программу.\")\n";
    file << "    except Exception as e:\n";
    file << "        print(f\"Ошибка: {e}\")\n\n";

    file << "if __name__ == \"__main__\":\n";
    file << "    main()\n";

    file.close();

    cout << "Создан файл visualize.py с параметрами:" << endl;
    cout << "Центр: (" << centerX << ", " << centerY << ", " << centerZ << ")" << endl;
    cout << "Радиусы: R1=" << R1 << ", R2=" << R2 << endl;
}
