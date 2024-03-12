#include <GL/glut.h>

float rotationAngle = 0.0f;  //initial angle

//draw octahedron func
void drawOctahedron() {
    glBegin(GL_LINES);

    //Verices for each face of the octahedron
    //face 1 coordinates
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);

    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 1.0, 0.0);

    //face 2 coordinates
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);

    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);

    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 1.0, 0.0);

    //face 3 coordinates
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);

    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -1.0);

    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, -1.0, 0.0);

    //face 4 coordinates
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -1.0);

    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, -1.0, 0.0);

    //face 5 coordinates
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);

    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, -1.0, 0.0);

    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 0.0, -1.0);

    //face 6 coordinates
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, -1.0);

    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, -1.0, 0.0);

    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0); //set viewpoint
    glRotatef(rotationAngle, 1, 1, 1); //rotate octahedron
    drawOctahedron();
    glutSwapBuffers();
}

//reshape func
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (double)width / height, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

//rotation logic
void idle() {
    rotationAngle += 0.5f;
    if (rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
    glutPostRedisplay(); //fluid rotation
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Octahedron Surface Tessellation");
    glutInitWindowSize(800, 600);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
