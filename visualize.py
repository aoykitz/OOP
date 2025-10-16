import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_points(filename):
    points = []
    with open(filename, 'r') as f:
        for line in f:
            if line.strip() and not line.startswith('#'):
                coords = list(map(float, line.split()))
                if len(coords) == 3:
                    points.append(coords)
    return np.array(points)

def create_sphere(center_x, center_y, center_z, radius, resolution=30):
    u = np.linspace(0, 2 * np.pi, resolution)
    v = np.linspace(0, np.pi, resolution)
    x = center_x + radius * np.outer(np.cos(u), np.sin(v))
    y = center_y + radius * np.outer(np.sin(u), np.sin(v))
    z = center_z + radius * np.outer(np.ones(np.size(u)), np.cos(v))
    return x, y, z

def main():
    try:
        points = read_points('points.txt')
        print(f"Прочитано {len(points)} точек")

        # Параметры из C++ программы
        center_x = 1
        center_y = 3
        center_z = 3
        r1 = 1
        r2 = 3

        fig = plt.figure(figsize=(14, 10))
        ax = fig.add_subplot(111, projection='3d')

        # Отображение точек
        ax.scatter(points[:, 0], points[:, 1], points[:, 2], 
                   c='blue', alpha=0.6, s=20, label=f'Точки ({len(points)} шт)')

        # Отображение центра сфер (большая красная звезда)
        ax.scatter([center_x], [center_y], [center_z], 
                   c='red', s=200, marker='*', label=f'Центр ({center_x:.1f}, {center_y:.1f}, {center_z:.1f})')

        # Создание сфер
        x1, y1, z1 = create_sphere(center_x, center_y, center_z, r1)
        x2, y2, z2 = create_sphere(center_x, center_y, center_z, r2)

        # Внутренняя сфера
        ax.plot_wireframe(x1, y1, z1, color='red', alpha=0.3, linewidth=1, 
                         label=f'Внутренняя сфера R1={r1:.2f}')

        # Внешняя сфера
        ax.plot_wireframe(x2, y2, z2, color='green', alpha=0.3, linewidth=1, 
                         label=f'Внешняя сфера R2={r2:.2f}')

        # Настройка осей - ФИКСИРОВАННЫЕ ГРАНИЦЫ!
        ax.set_xlabel('Ось X')
        ax.set_ylabel('Ось Y')
        ax.set_zlabel('Ось Z')
        
        # ФИКСИРОВАННЫЕ ГРАНИЦЫ ОСЕЙ от -10 до 10
        axis_limit = 10
        ax.set_xlim(-axis_limit, axis_limit)
        ax.set_ylim(-axis_limit, axis_limit)
        ax.set_zlim(-axis_limit, axis_limit)
        
        # Добавляем координатную сетку
        ax.grid(True, alpha=0.3)
        
        # Отображаем координатные оси через центр (0,0,0)
        ax.quiver(0, 0, 0, axis_limit, 0, 0, color='r', arrow_length_ratio=0.1, linewidth=1, alpha=0.7)
        ax.quiver(0, 0, 0, 0, axis_limit, 0, color='g', arrow_length_ratio=0.1, linewidth=1, alpha=0.7)
        ax.quiver(0, 0, 0, 0, 0, axis_limit, color='b', arrow_length_ratio=0.1, linewidth=1, alpha=0.7)
        
        ax.set_title(f'Точки между концентрическими сферами\\nЦентр: ({center_x:.1f}, {center_y:.1f}, {center_z:.1f}) R1={r1:.1f} R2={r2:.1f}')
        ax.legend()

        # Статистика
        distances = np.sqrt((points[:, 0] - center_x)**2 + 
                           (points[:, 1] - center_y)**2 + 
                           (points[:, 2] - center_z)**2)
        print("=" * 60)
        print(f"ЦЕНТР СФЕР: ({center_x:.2f}, {center_y:.2f}, {center_z:.2f})")
        print(f"Радиусы: R1={r1:.2f}, R2={r2:.2f}")
        print(f"Фактические: min={np.min(distances):.2f}, max={np.max(distances):.2f}")
        print("Границы осей: от -10 до 10")
        print("=" * 60)

        plt.tight_layout()
        plt.show()

    except FileNotFoundError:
        print("Файл points.txt не найден! Сначала запустите C++ программу.")
    except Exception as e:
        print(f"Ошибка: {e}")

if __name__ == "__main__":
    main()
