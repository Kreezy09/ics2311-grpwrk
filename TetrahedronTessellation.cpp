#include <GL/glut.h>

float rotationAngle = 0.0f; //initial angle

void drawTetrahedron() {
    glBegin(GL_LINES);

    //Vertices for faces and edges
    //face 1
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0, -1.0);

    //face 2
    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(0.0, 1.0, 1.0);

    //face 3
    glVertex3f(0.0, 1.0, 1.0);
    glVertex3f(1.0, 0.0, -1.0);

    //face4
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(0.0, -1.0, 1.0);

    //face 5
    glVertex3f(0.0, -1.0, 1.0);
    glVertex3f(-1.0, 0.0, -1.0);

    //face6
    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(0.0, 1.0, 1.0);

    //finaledges to connect the faces
    glVertex3f(0.0, -1.0, 1.0);
    glVertex3f(0.0, 1.0, 1.0);

    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0); //set viewpoint
    glRotatef(rotationAngle, 1, 1, 1); //rotate tetrahedron
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
    glutCreateWindow("Tetrahedron (Surface Tessellation)");
    glutInitWindowSize(800, 600);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
