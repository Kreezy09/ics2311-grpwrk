import glfw
from OpenGL.GL import *
from OpenGL.GLUT import *

# Vertices for a tetrahedron
vertices = [
    [1, 1, 1],
    [-1, -1, 1],
    [-1, 1, -1],
    [1, -1, -1]
]

indices = [
    0, 1, 2,
    0, 3, 1,
    2, 1, 3,
    0, 2, 3
]

def draw_tetrahedron():
    glBegin(GL_TRIANGLES)
    for i in range(0, len(indices), 3):
        for j in range(3):
            glVertex3fv(vertices[indices[i + j]])
    glEnd()

def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    draw_tetrahedron()
    glfw.swap_buffers(window)

def main():
    if not glfw.init():
        return

    window = glfw.create_window(800, 600, "OpenGL Platonic Solid", None, None)
    if not window:
        glfw.terminate()
        return

    glfw.make_context_current(window)
    glEnable(GL_DEPTH_TEST)

    shader_program = create_shader_program()
    if not shader_program:
        glfw.terminate()
        return

    while not glfw.window_should_close(window):
        glfw.poll_events()
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        glFrustum(-1, 1, -1, 1, 0.1, 50.0)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        glTranslatef(0.0, 0.0, -5.0)
        display(window, shader_program)

    glDeleteProgram(shader_program)
    glfw.terminate()

if __name__ == "__main__":
    main()
