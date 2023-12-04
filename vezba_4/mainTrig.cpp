#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

// g++ -o p mainTrig.cpp -lGL -lglut
// ./p

void drawSquareTrig(float a_length, float fi, float xa, float ya)
{
	float xb, yb, xc, yc, xd, yd;
	
	float senka = a_length * cos(fi) + a_length * sin(fi);
	printf("%f\n", senka);
	
	xb = xa+ a_length * cos(fi);
	yb = ya+ a_length * sin(fi);
	xd = xa+ a_length * cos(M_PI/2.0 + fi);
	yd = ya+ a_length * sin(M_PI/2.0 + fi);
	
	float d = sqrt(a_length*a_length + a_length*a_length);
	xc = xa+ d * cos(M_PI/4.0 + fi);
	yc = ya+ d * sin(M_PI/4.0 + fi);
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f (xa, ya);
		glVertex2f (xb, yb);
		glVertex2f (xc, yc);
		glVertex2f (xd, yd);
	glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    
    drawSquareTrig(0.5, 1, 0.6, 0.1);
    
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(670, 330);
    glutCreateWindow("hello");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

