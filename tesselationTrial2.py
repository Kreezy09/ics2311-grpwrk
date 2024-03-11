import glfw
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

vertex_shader_source = """
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos, 1.0);
}
"""

geometry_shader_source = """
#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 9) out;

void main()
{
    for(int i = 0; i < 3; ++i)
    {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}
"""

fragment_shader_source = """
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
"""

def compile_shader(shader_source, shader_type):
    shader = glCreateShader(shader_type)
    glShaderSource(shader, shader_source)
    glCompileShader(shader)

    if not glGetShaderiv(shader, GL_COMPILE_STATUS):
        error = glGetShaderInfoLog(shader)
        print(f"Shader compilation failed:\n{error}")
        glDeleteShader(shader)
        return None

    return shader

def main():
    if not glfw.init():
        return

    window = glfw.create_window(800, 600, "OpenGL Platonic Solid", None, None)
    if not window:
        glfw.terminate()
        return

    glfw.make_context_current(window)
    glEnable(GL_DEPTH_TEST)

    vertex_shader = compile_shader(vertex_shader_source, GL_VERTEX_SHADER)
    geometry_shader = compile_shader(geometry_shader_source, GL_GEOMETRY_SHADER)
    fragment_shader = compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER)

    if not (vertex_shader and geometry_shader and fragment_shader):
        glfw.terminate()
        return

    program = glCreateProgram()
    glAttachShader(program, vertex_shader)
    glAttachShader(program, geometry_shader)
    glAttachShader(program, fragment_shader)
    glLinkProgram(program)

    if not glGetProgramiv(program, GL_LINK_STATUS):
        error = glGetProgramInfoLog(program)
        print(f"Program linking failed:\n{error}")
        glDeleteProgram(program)
        glfw.terminate()
        return

    glUseProgram(program)

    while not glfw.window_should_close(window):
        glfw.poll_events()
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glDrawArrays(GL_TRIANGLES, 0, 3)
        glfw.swap_buffers(window)

    glDeleteShader(vertex_shader)
    glDeleteShader(geometry_shader)
    glDeleteShader(fragment_shader)
    glDeleteProgram(program)
    glfw.terminate()

if __name__ == "__main__":
    main()
