#include <GL/glut.h>
#include <math.h>

int red = 1.0;
int green = 0.0;
int blue = 0.0;

double WINDOW_HIGHT = 500;
double Y_AXES = 2.0;
double aspectRatio = 4.0/3.0;

void display()
{
	glClear (GL_COLOR_BUFFER_BIT);
 	
	glFlush ();
	
	glutPostRedisplay();
}

void ChangePosition(void)
{
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

