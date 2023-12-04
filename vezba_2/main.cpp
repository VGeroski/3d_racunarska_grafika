#include <GL/glut.h>
#include <math.h>

// g++ -o p main.cpp -lGL -lglut
// ./p

void nacrtajTacke(float velicinaTacke) 
{
  glColor3f(1.0, 1.0, 0.0);
  glEnable(GL_POINT_SMOOTH);
  glPointSize(velicinaTacke);
  glBegin(GL_POINTS);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, 2.0, 0.0);
    glVertex3f(2.0, 3.0, 0.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(2.0, 4.0, 0.0);
    glVertex3f(3.0, 1.0, 0.0);
  glEnd();
}

void nacrtajLinije() 
{
  glBegin(GL_LINES);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, 2.0, 0.0);
    glVertex3f(2.0, 3.0, 0.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(2.0, 2.0, 0.0);
    glVertex3f(3.0, 1.0, 0.0);
    glEnd();
}

void nacrtajPoligon()
{  
  glColor3f(0.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
    glVertex3f(5.0, 4.0, 0.0);
    glVertex3f(5.0, 2.0, 0.0);
    glVertex3f(9.0, 2.0, 0.0);
    glVertex3f(9.0, 4.0, 0.0);
  glEnd();
}

void nacrtajKrug(GLdouble x, GLdouble y, GLdouble r, GLint broj_tacaka)
{
  double crvena = 1.0;
  double zelena = 0.0;
  double plava = 0.0;
  double alfa = 2 * M_PI / broj_tacaka;

  glBegin(GL_POLYGON);
    for (int i = 0; i < broj_tacaka; i++)
    {
      glColor3f(crvena, zelena, plava);
      crvena -= 1.0 / broj_tacaka;
      zelena += 1.0 / broj_tacaka;
      double ugao = i * alfa;
      glVertex2f(x + r*cos(ugao), y + r*sin(ugao));
    }
  glEnd();
}

void display(void)
{
    /* clear all pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    nacrtajTacke(10.0);
    nacrtajLinije();
    nacrtajPoligon();
    nacrtajKrug(5.0, 5.0, 2.0, 100);
    nacrtajKrug(5.0, 8.0, 2.0, 100);

    glFlush ();
}

void init(void)
{
    /* select clearing (background) color */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    /* initialize viewing values */
    glMatrixMode(GL_PROJECTION);
    // glFrontFace(GL_CW);
    glLoadIdentity();
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
}
/* Declare initial window size, position, and display mode
   (single buffer and RGBA). Open window with "hello"
   in its title bar. Call initialization routines.
   Register callback function to display graphics.
   Enter main loop and process events. */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(670, 330);
    glutCreateWindow("first program");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
	
    return 0; /* ISO C requires main to return int. */
}
