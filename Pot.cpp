#include <GL/glut.h>

float rotationAngle = 0.0f; //rotation angle

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); 
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0); //set viewpoint
    glRotatef(rotationAngle, 1, 1, 1); //rotate teapot 
    glutWireTeapot(1.0); //draw teapot
    glutSwapBuffers();
}

void reshape(int width, int height) { 
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, (double)width / height, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

//rotation logic
void idle() {
    rotationAngle += 0.5f;
    //set angle to 0 if > 360
    if (rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
    glutPostRedisplay(); //fluid rotation
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Utah Teapot");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
