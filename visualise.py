import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_points(filename):
    points = []
    with open(filename, 'r') as f:
        for line in f:
            if line.strip():
                coords = list(map(float, line.split()))
                if len(coords) == 3:
                    points.append(coords)
    return np.array(points)

def main():
    points = read_points('points.txt')
    print(f"Прочитано {len(points)} точек")
    
    # ЗАМЕНИТЕ НА ВАШИ ПАРАМЕТРЫ!
    center_x = 0
    center_y = 0  
    center_z = 0
    r1 = 1
    r2 = 3
    
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(points[:,0], points[:,1], points[:,2], c='blue', alpha=0.6, s=20)
    ax.set_xlabel('X')
    ax.set_ylabel('Y') 
    ax.set_zlabel('Z')
    ax.set_title('Сгенерированные точки')
    plt.show()

if __name__ == "__main__":
    main()
