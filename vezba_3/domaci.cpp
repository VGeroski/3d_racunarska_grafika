#include <GL/glut.h>
#include <math.h>

double WINDOW_HIGHT = 900;
double Y_AXES = 3.0;
double aspectRatio = 4.0/3.0;

double rotacija_krila = 0.0;
double rotacija_sunca = 0.0;

// metoda za iscrtavanje krila vetrenjace
// (x, y) - tacka vezivanja nosaca
void krila_vetrenjace(float x, float y)
{ 
    double alfa = M_PI / 180;
    // trenutni ugao pod kojim se nalaze krila
    double ugao = alfa * rotacija_krila;
	double ugao90 = M_PI / 2;
	double ugao30 = M_PI / 4;
	// izmedju horizontale i prave koji prolazi kroz kraj krila
	double mali_ugao = M_PI / 16;
    // duzina nosaca
    double nosac = 0.75;

    // 4 'nosaca' krila
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(10);
    glBegin(GL_LINES);
    for(int i = 0; i < 4; i++)
    {
        // zajednicka tacka (pocetak)
        glVertex2f(x, y);
        // krajnja tacka (svaka linija rotirana za 90 stepeni)
        double rot_ugao = ugao + i*ugao90;
        glVertex2f(x + nosac * cos(rot_ugao), y + nosac * sin(rot_ugao));
    }
    glEnd();

    double r = 0.2;
	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(0.8, 0.8, 0.8);
		glVertex2f(x + r * cos(ugao + i * ugao90), y + r * sin(ugao + i * ugao90));
		glVertex2f(x + nosac * cos(ugao + i * ugao90), y + nosac * sin(ugao + i * ugao90));
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(x + (nosac + 0.025) * cos(ugao + i * ugao90 + mali_ugao), y + (nosac + 0.025) * sin(ugao + i * ugao90 + mali_ugao));
		glVertex2f(x + (r + 0.025) * cos(ugao + i * ugao90 + ugao30), y + (r + 0.025) * sin(ugao + i * ugao90 + ugao30));
		glEnd();
	}
}

void rotiraj_vetrenjacu(float korak)
{
    // rotiranje krila vetrenjaca (0 - 360)
    if (rotacija_krila < 0)
	{
		rotacija_krila = 360;
	}
	rotacija_krila -= korak;
}

void rotiraj_sunce(float korak)
{
	// rotiranje sunca (0 - 360)
    if (rotacija_sunca < 0)
	{
		rotacija_sunca = 360;
	}
	rotacija_sunca -= korak;
}

void nacrtaj_krug( GLdouble x, GLdouble y, GLdouble r, GLint broj_tacaka )
{
  double alfa = 2 * M_PI / broj_tacaka;

  glBegin(GL_POLYGON);
    for (int i = 0; i < broj_tacaka; i++)
    {
      double ugao = i * alfa;
      glVertex2f(x + r*cos(ugao), y + r*sin(ugao));
    }
  glEnd();
}

void sunce()
{
	// poluprecnik kruga po kome se krece sunce
	float R = 3.5;
	int broj_tacaka = 100;
	float ugao = rotacija_sunca * 2 * M_PI / broj_tacaka;
	double x = 2.0;
	x += R * cos(ugao);
	double y = -1.0;
	y += R * sin(ugao);
	
	nacrtaj_krug(x, y, 0.25, 100);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

 	// sunce
	glColor3f(0.9, 0.9, 0.0);
	sunce();

	// podloga
	glColor3f(0.0, 0.7, 0.0);
	nacrtaj_krug(2.0,-9.0, 10, 100);

    // zidovi
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_POLYGON);
        glVertex3f(1.6, 0.50, 0.0);
        glVertex3f(2.4, 0.50, 0.0);
        glVertex3f(2.3, 1.50, 0.0);
        glVertex3f(1.7, 1.50, 0.0);
	glEnd();

    // krov
    glColor3f(1.0, 0.8, 0.6);
	glBegin(GL_POLYGON);
        glVertex3f(1.65, 1.50, 0.0);
        glVertex3f(2.35, 1.50, 0.0);
        glVertex3f(2.00, 1.85, 0.0);	
	glEnd();

	krila_vetrenjace(2.0, 1.7);
	// svakim pozivanje display - menja se ugao za koji se rotiraju krila
    rotiraj_vetrenjacu(0.05);

	glFlush();
	glutPostRedisplay();
}

void ChangePosition(void)
{
	// promeni poziciju sunca
	rotiraj_sunce(0.05);
	glutPostRedisplay();
}

void init (void)
{
	glClearColor(0.7, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Y_AXES * aspectRatio, 0.0, Y_AXES, -1.0, 1.0);
}

void reshape(int w, int h)
{
	if(w < h)
		WINDOW_HIGHT = w / aspectRatio;
	else
		WINDOW_HIGHT = h;
		
	glViewport(0, 0, WINDOW_HIGHT * aspectRatio, WINDOW_HIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Y_AXES * aspectRatio, 0.0, Y_AXES, -1.0, 1.0);
}

void mousePress(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN)
				glutIdleFunc(ChangePosition);
			else glutIdleFunc(NULL);
			break;
		default:
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_HIGHT * aspectRatio, WINDOW_HIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mousePress);
	glutMainLoop();
	
	return 0;
}

