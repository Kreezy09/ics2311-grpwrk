from OpenGL.GL import *
from OpenGL.GLUT import *
import pygame
from pygame.locals import *
from OpenGL.GLU import gluPerspective
glutInit()

#below is initializer func
def initialize():
    glClearColor(0, 0, 0, 1)
    gluPerspective(45, (display_size[0] / display_size[1]), 0.1, 50.0)
    glTranslatef(0.0, 0.0, -5)

#display func
def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glutWireTetrahedron() #draws wireframe tetrahedron
    pygame.display.flip()

def main():
    pygame.init()
    global display_size
    display_size = (800, 600)
    pygame.display.set_mode(display_size, DOUBLEBUF | OPENGL)
    pygame.display.set_caption("Tetrahedron (Wireframe)")

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
