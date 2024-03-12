import numpy as np
import matplotlib.pyplot as plt

def loadTeapotCoordinates():# function to load teapot coordinates in obj file
    with open('teapot.obj', 'r') as teaPotCoords: #open file as f
        vertices = [] #empty llist of vertices
        faces = [] #empty list of faces
        for line in teaPotCoords: #for each line in the file
            if line.startswith('v '):
                #removes whitespace, spits the line to a list of subtstrings and starts taking elements from the first index
                #converts strings to float and converts resulting map object to list
                vertices.append(list(map(float, line.strip().split()[1:]))) #append the vertices to the list
            elif line.startswith('f '):
                #removes whitespace, spits the line to a list of subtstrings and starts taking elements from the first index
                #converts strings to int and subtracts 1 from each element and converts resulting map object to list
                faces.append([int(x.split('/')[0]) - 1 for x in line.strip().split()[1:]]) #appends faces to list
        return np.array(vertices), np.array(faces) #returns the vertices and faces as numpy arrays

#funct to plot the teapot
def plot_teapot(vertices, faces):
    figOBJ = plt.figure() #create fig object
    ax = figOBJ.add_subplot(111, projection='3d') #adds single subplot (3D) to fig obj with 1 row & col
    for face in faces: 
        x = vertices[face, 0] #x coordinates
        y = vertices[face, 1] #y coordinates
        z = vertices[face, 2] #z coordinates
        ax.plot_trisurf(x, y, z, color='grey', linewidth=0) #plot teapot defined by coordinates
    ax.set_xlabel('x') #set x label
    ax.set_ylabel('y') #set y label
    ax.set_zlabel('z') #set z label
    ax.set_title('Teapot') #set title
    plt.show()

#driver code
if __name__ == '__main__':
    vertices, faces = loadTeapotCoordinates()
    plot_teapot(vertices, faces)
