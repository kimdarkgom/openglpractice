#include "gl/glut.h"
#include <cstdio>
#include "GCBezierCurve.h"
#include <vector>

Vec2 mousePt = { 1, 0 };
float rotateAngle = 0.0;
std::vector<Vec2> ctrlPts;
std::vector<Vec2> vec;
int num = 10.0;
void displayGlutPrimitives() {

    glutWireTeapot(1.0);

}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0); //지정 값만큼 크기 지정

    // --------------- 3. Bezier Curve --------------------------
    BezierCurve2D curve(ctrlPts);

    glPointSize(15.0);
    glLineWidth(1.0);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    for (auto& pt : ctrlPts)
        glVertex2f(pt.x, pt.y);
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (auto& pt : ctrlPts)
        glVertex2f(pt.x, pt.y);
    glEnd();


    for (int i = 0; i <= 100; i++) {
        auto pt = curve.Evaluate(i / 100.0);//c(t)값을 구해주는 함수임
        glColor3f(0, 0, 0);
        glLineWidth(2.0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(pt.x, pt.y);
        /*if (i == 1) {
            vec.push_back({ pt.x,pt.y });
        }
        if (i == 50) {

            glPointSize(10.0);
            glColor3f(1, 0, 0);
            glBegin(GL_LINE_STRIP);
            glVertex2f(pt.x, pt.y);

        }*/
    }
    glEnd();

    // ----------------------------------------------------------------

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
    case 27: // ESC
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        rotateAngle += 10;
        break;
    case GLUT_KEY_DOWN:
        rotateAngle -= 10;
        break;
    case GLUT_KEY_RIGHT:
        num += 1;
        break;
    case GLUT_KEY_LEFT:
        num -= 1;
        break;
    }
    glutPostRedisplay();
}

void mouseCoordinateTranslate(int winX, int winY)
{
    mousePt.x = winX / 50.0 - 5;
    mousePt.y = (winY / 50.0 - 5) * (-1.0);
}

void changeCtrlPts()
{
    for (auto& pt : ctrlPts) {
        if (sqrt(pow(pt.x - mousePt.x, 2) + pow(pt.y - mousePt.y, 2)) < 0.5) {
            pt = mousePt;
            break;
        }
    }
}

void mouse(int button, int state, int x, int y)
{
    printf("mouse: %d %d %d %d\n", button, state, x, y);
    if (state == GLUT_DOWN) {
        mouseCoordinateTranslate(x, y);
        changeCtrlPts();
    }
    glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
    printf("mouse motion: %d %d\n", x, y);
    mouseCoordinateTranslate(x, y);
    changeCtrlPts();

    glutPostRedisplay();
}

void mousePassiveMotion(int x, int y)
{
    printf("mouse passive motion: %d %d\n", x, y);
    mouseCoordinateTranslate(x, y);
    glutPostRedisplay();
}

int main(int argc, char** argv)
{


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(1480, 100);

    ctrlPts.push_back({ -2, -1 });
    ctrlPts.push_back({ 0, 2 });
    ctrlPts.push_back({ 2, -1 });
    ctrlPts.push_back({ 4, 2 });

    glutCreateWindow("OpenGL");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();

    return 0;
}