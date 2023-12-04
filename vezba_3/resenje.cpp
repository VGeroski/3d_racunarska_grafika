#include <GL/glut.h>
#include <math.h>

int red = 1.0;
int green = 0.0;
int blue = 0.0;

double WINDOW_HIGHT = 500;
double Y_AXES = 2.0;
double aspectRatio = 4.0/3.0;

double a = 1.25;
double b = 1.75;
double c = 1.50;
double d = 1.50;

int flag_cut = 0;

void display()
{
	glClear (GL_COLOR_BUFFER_BIT);
 	if(red == 1.0)
	{
		red = 0.0;
		green = 1.0;
	}
	else if(green == 1.0)
	{
		green = 0.0;
		blue = 1.0;
	}
	else if(blue == 1.0)
	{
		blue = 0.0;
		red = 1.0;
	}
	
	glColor3f(red, green, blue);
	glBegin(GL_POLYGON);
		glVertex3f (0.25, 0.25, 0.0);
		glVertex3f (0.75, 0.25, 0.0);
		glVertex3f (0.75, 0.75, 0.0);
		glVertex3f (0.25, 0.75, 0.0);
	glEnd();
	
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f (a, 1.25, 0.0);
		glVertex3f (d, 1.25, 0.0);
		glVertex3f (d, 1.75, 0.0);
		glVertex3f (a, 1.75, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f (c, 1.25, 0.0);
		glVertex3f (b, 1.25, 0.0);
		glVertex3f (b, 1.75, 0.0);
		glVertex3f (c, 1.75, 0.0);
	glEnd();
	
	glFlush ();
	
	glutPostRedisplay();
}

void ChangePosition(void)
{
	if(b > Y_AXES * aspectRatio || flag_cut == 1)
	{
		flag_cut = 1;
		
		if(b + 0.05 > Y_AXES * aspectRatio)
		{
			b = 0.05;
			c = 0.0;
			d = Y_AXES * aspectRatio;
		}
		else
		{
			b += 0.05;
			c = 0.0;
		}
		
		a += 0.05;
	}
	
	if(a + 0.05 > Y_AXES * aspectRatio && flag_cut == 1)
	{
		a = 0.0;
		b += 0.05;
		c += 0.05;
		d = c;
		flag_cut = 0;
	}
	if(flag_cut == 0)
	{
		a += 0.05;
		b += 0.05;
		c += 0.05;
		d = c;
	}
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

