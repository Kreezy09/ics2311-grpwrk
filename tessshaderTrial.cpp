#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

GLuint programID;

void initShaders() {
    // Vertex Shader
    const char* vertexShaderCode = R"(
        #version 430 core
        layout(location = 0) in vec3 vertexPosition;
        void main() {
            gl_Position = vec4(vertexPosition, 1.0);
        }
    )";

    // Tessellation Control Shader
    const char* tessControlShaderCode = R"(
        #version 430 core
        layout(vertices = 3) out;
        void main() {
            if (gl_InvocationID == 0) {
                gl_TessLevelInner[0] = 5.0;
                gl_TessLevelOuter[0] = 5.0;
                gl_TessLevelOuter[1] = 5.0;
                gl_TessLevelOuter[2] = 5.0;
            }
            gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
        }
    )";

    // Tessellation Evaluation Shader
    const char* tessEvalShaderCode = R"(
        #version 430 core
        layout(triangles, equal_spacing, cw) in;
        void main() {
            gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
                           gl_TessCoord.y * gl_in[1].gl_Position +
                           gl_TessCoord.z * gl_in[2].gl_Position);
        }
    )";

    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint tessControlShaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
    GLuint tessEvalShaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);

    glShaderSource(vertexShaderID, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShaderID);

    glShaderSource(tessControlShaderID, 1, &tessControlShaderCode, nullptr);
    glCompileShader(tessControlShaderID);

    glShaderSource(tessEvalShaderID, 1, &tessEvalShaderCode, nullptr);
    glCompileShader(tessEvalShaderID);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, tessControlShaderID);
    glAttachShader(programID, tessEvalShaderID);
    glLinkProgram(programID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(tessControlShaderID);
    glDeleteShader(tessEvalShaderID);
}

void init() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    initShaders();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);
    glPatchParameteri(GL_PATCH_VERTICES, 3);
    glDrawArrays(GL_PATCHES, 0, 3);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Tetrahedron Tessellation");

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
