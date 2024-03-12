#include <GL/glut.h>

float rotationAngle = 0.0f;  // Initial rotation angle

void initialize() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void drawTetrahedron() {
    int subdivisions = 5; // Number of subdivisions for each face
    int numLargeTriangles = 4; // Number of large triangles to form a tetrahedron

    glBegin(GL_TRIANGLES);

    for (int k = 0; k < numLargeTriangles; ++k) {
        for (int i = 0; i < subdivisions; ++i) {
            for (int j = 0; j <= i; ++j) {
                float u0 = static_cast<float>(j) / static_cast<float>(subdivisions);
                float v0 = static_cast<float>(i) / static_cast<float>(subdivisions);

                float u1 = static_cast<float>(j + 1) / static_cast<float>(subdivisions);
                float v1 = static_cast<float>(i + 1) / static_cast<float>(subdivisions);

                // Vertices for the smaller triangles
                float x0 = 2.0 * u0 - 1.0;
                float y0 = -1.0 + 2.0 * v0;
                float z0 = -1.0 + 2.0 * u0;

                float x1 = 2.0 * u1 - 1.0;
                float y1 = -1.0 + 2.0 * v0;
                float z1 = -1.0 + 2.0 * u1;

                float x2 = 2.0 * u0 - 1.0;
                float y2 = -1.0 + 2.0 * v1;
                float z2 = -1.0 + 2.0 * u0;

                float x3 = 2.0 * u1 - 1.0;
                float y3 = -1.0 + 2.0 * v1;
                float z3 = -1.0 + 2.0 * u1;

                // Draw the four smaller triangles
                glVertex3f(x0, y0, z0);
                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);

                glVertex3f(x1, y1, z1);
                glVertex3f(x3, y3, z3);
                glVertex3f(x2, y2, z2);
            }
        }
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);  // Set the viewpoint

    // Apply rotation
    glRotatef(rotationAngle, 1, 1, 1); // Rotate for a better view

    drawTetrahedron();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (double)width / height, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle() {
    rotationAngle += 0.5f;  // Adjust the rotation speed
    if (rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Tetrahedron - Multiple Large Triangles");
    glutInitWindowSize(800, 600);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
