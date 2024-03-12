from OpenGL.GL import *
from OpenGL.GLUT import *
import pygame
from pygame.locals import *
from OpenGL.GLU import gluPerspective

#vertices
vertices = (
    (1, -1, -1),
    (1, -1, 1),
    (-1, -1, 1),
    (-1, -1, -1),
    (0, 1, 0)
)

#edges
edges = (
    (0, 1),
    (1, 2),
    (2, 3),
    (3, 0),
    (0, 4),
    (1, 4),
    (2, 4),
    (3, 4)
)

#draw tetrahedron
def draw_tetrahedron():
    glBegin(GL_LINES) #lines(edges) show polyhedron clearly
    for edge in edges:
        for vertex in edge:
            glVertex3fv(vertices[vertex])
    glEnd()

#initializer func
def initialize():
    glClearColor(0, 0, 0, 1)
    gluPerspective(45, (display_size[0] / display_size[1]), 0.1, 50.0)
    glTranslatef(0.0, 0.0, -5)

#display configs
def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    draw_tetrahedron()
    pygame.display.flip()

def main():
    pygame.init()
    global display_size
    display_size = (800, 600)
    pygame.display.set_mode(display_size, DOUBLEBUF | OPENGL)
    pygame.display.set_caption("Tetrahedron Tessellation")

    glEnable(GL_DEPTH_TEST)
    initialize()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        glRotatef(1, 3, 1, 1)
        display()
        pygame.time.wait(10)

if __name__ == "__main__":
    main()
