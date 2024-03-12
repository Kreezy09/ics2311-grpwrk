#include <GL/glut.h>
#include <cmath>

float rotationAngle = 0.0f;  // Initial rotation angle

void initialize() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void drawDodecahedron() {
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;

    glBegin(GL_LINES);

    // Vertices for each face of the dodecahedron
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    glVertex3f(-1, 1, 1);
    glVertex3f(-phi, phi, phi);

    glVertex3f(-phi, phi, phi);
    glVertex3f(0, 1 + phi, 1);

    glVertex3f(0, 1 + phi, 1);
    glVertex3f(phi, phi, phi);

    glVertex3f(phi, phi, phi);
    glVertex3f(1, 1, 1);

    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);

    glVertex3f(1, -1, 1);
    glVertex3f(phi, -phi, phi);

    glVertex3f(phi, -phi, phi);
    glVertex3f(0, -1 - phi, 1);

    glVertex3f(0, -1 - phi, 1);
    glVertex3f(-phi, -phi, phi);

    glVertex3f(-phi, -phi, phi);
    glVertex3f(-1, -1, 1);

    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);

    glVertex3f(-1, 1, -1);
    glVertex3f(-phi, phi, -phi);

    glVertex3f(-phi, phi, -phi);
    glVertex3f(0, 1 + phi, -1);

    glVertex3f(0, 1 + phi, -1);
    glVertex3f(phi, phi, -phi);

    glVertex3f(phi, phi, -phi);
    glVertex3f(1, 1, -1);

    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);

    glVertex3f(1, -1, -1);
    glVertex3f(phi, -phi, -phi);

    glVertex3f(phi, -phi, -phi);
    glVertex3f(0, -1 - phi, -1);

    glVertex3f(0, -1 - phi, -1);
    glVertex3f(-phi, -phi, -phi);

    glVertex3f(-phi, -phi, -phi);
    glVertex3f(-1, -1, -1);

    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);

    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);

    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);

    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);

    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);  // Set the viewpoint

    // Apply rotation
    glRotatef(rotationAngle, 1, 1, 1);

    drawDodecahedron();
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
    glutCreateWindow("Dodecahedron - Surface Tessellation");
    glutInitWindowSize(800, 600);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
