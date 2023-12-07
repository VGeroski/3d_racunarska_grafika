#include <GL/glut.h>
#include <math.h>

int red = 1.0;
int green = 0.0;
int blue = 0.0;

double WINDOW_HIGHT = 500;
double Y_AXES = 2.0;
double aspectRatio = 4.0/3.0;

float xa = 0.5;
float stranica_kvadrata = 0.5;

double a = 1.25;
double b = 1.75;
double c = 1.5;
double d = 1.5;

int flag_cut = 0;

float korak_za_boju = 0.001;
float korak_za_pomeranje = 0.001;

float crvena = 0.0;
float zelena = 0.0;
float plava = 0.0;

void display()
{
	glClear (GL_COLOR_BUFFER_BIT);
 	
	if ( crvena <= 1.0)
	{
		crvena += korak_za_boju;
	} else crvena = 0.0;

	if ( zelena <= 1.0) 
	{
		zelena += 0.7 * korak_za_boju;
	} else zelena = 0.0;

	if ( plava <= 1.0) 
	{
		plava += korak_za_boju / 3.0;
	} else plava = 0.0;

	glColor3f(crvena, zelena, plava);

	// crtanje kvadrata
	glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.25);
		glVertex2f(stranica_kvadrata, 0.25);
		glVertex2f(stranica_kvadrata, 0.25 + stranica_kvadrata);
		glVertex2f(0.0, 0.25 + stranica_kvadrata);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(a, 1.25);
		glVertex2f(d, 1.25);
		glVertex2f(d, 1.75);
		glVertex2f(a, 1.75);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2f(c, 1.25);
		glVertex2f(b, 1.25);
		glVertex2f(b, 1.75);
		glVertex2f(c, 1.75);
	glEnd();

	glFlush ();
	glutPostRedisplay();
}

void ChangePosition(void)
{
	if (b > Y_AXES*aspectRatio || flag_cut == 1)
	{
		flag_cut = 1.0;

		if (b + korak_za_pomeranje > Y_AXES*aspectRatio)
		{
			b = korak_za_pomeranje;
			c = 0.0;
			d = Y_AXES*aspectRatio;
		}
		else
		{
			b += korak_za_pomeranje;
			c = 0.0;
		}

		a += korak_za_pomeranje;
	}

	if (a + korak_za_pomeranje > Y_AXES*aspectRatio && flag_cut == 1)
	{
		a = 0.0;
		b += korak_za_pomeranje;
		c += korak_za_pomeranje;
		d = c;
		flag_cut = 0;
	}

	if (flag_cut == 0)
	{
		a += korak_za_pomeranje;
		b += korak_za_pomeranje;
		c += korak_za_pomeranje;
		d = c;
	}

	glutPostRedisplay();
}

void init (void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
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

