import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

def draw_tetrahedron(ax):
    #vertices
    vertices = [
        [1, 0, -1 / 3**0.5],
        [-1, 0, -1 / 3**0.5],
        [0, 1, 2 / 3**0.5],
        [0, -1, 2 / 3**0.5]
    ]

    #faces
    faces = [
        [vertices[0], vertices[1], vertices[2]],
        [vertices[0], vertices[1], vertices[3]],
        [vertices[0], vertices[2], vertices[3]],
        [vertices[1], vertices[2], vertices[3]]
    ]

    #add 3d collection
    ax.add_collection3d(Poly3DCollection(faces, facecolors='white', linewidths=1, edgecolors='black'))

def main():
    #create figObj with larger window size
    fig = plt.figure(figsize=(5, 5))
    
    #create a 3D subplot on figObj
    ax = fig.add_subplot(111, projection='3d')
    
    #draw the tetrahedron
    draw_tetrahedron(ax)

    #set axes' labels and title
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title('3D Tetrahedron')

    plt.show()

if __name__ == "__main__":
    main()
