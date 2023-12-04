#include <GL/glut.h>

#include <math.h>
#include <stdio.h>

#include <glm/vec2.hpp> //glm Vector2D
#include <glm/gtx/projection.hpp> //proj funkcija

// g++ -o p mainGLM.cpp -lGL -lglut
// ./p

using namespace glm;

void drawSquare(float a_length, float fi, vec2 A)
{
	vec2 ABnorm(cos(fi), sin(fi));
	vec2 ADnorm(cos(M_PI/2.0 + fi), sin(M_PI/2.0 + fi));
	vec2 AB = ABnorm * a_length;
	vec2 AD = ADnorm * a_length;
	vec2 AC = AB + AD;
	vec2 xAxis(1.0,0.0);

	float senka = length(proj(AB,xAxis)) + length(proj(AD,xAxis));
	printf("%f\n",senka);
	
	vec2 B = A + AB;
	vec2 C = A + AC;
	vec2 D = A + AD;
	
	glColor3f (1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f (A.x, A.y);
		glVertex2f (B.x, B.y);
		glVertex2f (C.x, C.y);
		glVertex2f (D.x, D.y);
	glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    
    drawSquare(0.5, 1, vec2(0.6, 0.1));
    
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

