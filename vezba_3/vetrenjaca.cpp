#include <GL/glut.h>
#include <math.h>
#include <random>
#include<list> 

#define PI 3.1415

struct {
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
} wmBodyRGB, roofRGB, thunderRGB;

double WINDOW_HIGHT = 900;
double Y_AXES = 3.0;
double aspectRatio = 4.0 / 3.0;

int circle_points = 360;
int thundering_counter = 0;

bool night = false;
double global_sun_counter = 360;
double global_windmill_counter = 1.0;

double global_red = 1.00;
double global_green = 0.00;
double global_blue = 0.00;

double global_shadow_green = 0.25;
double global_ground_green = 0.60;

bool will_thunder = false;
bool thundering = true;
bool thunder_black = true;
bool thunder_white = false;

double xArray[20];
double yArray[20];

void drawSky();
void drawSun(); 
void initRgbs();
void drawShadow();
void drawGround();
void drawThunder();
void drawGroundOld();
void drawWindmillBody();
double roundTwo(double x);
int randomInt(int min, int max);
double randomDouble(double min, double max);
void drawWindmillRotator(GLdouble x, GLdouble y, GLdouble r);
void drawCircle(GLenum mode, GLdouble x, GLdouble y, GLdouble r, GLint circle_points, int drawFrom, int drawTo, double red, double green, double blue);

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	drawSky();
	drawSun();
	drawGround();
	drawShadow();
	drawWindmillBody();
	drawWindmillRotator(2.0, 1.1, 0.6);

	drawThunder();
	
	glFlush();
	glutPostRedisplay();
}

void lowerRoofRGB(double substractValue, double minValue)
{
	if (roofRGB.red - substractValue < minValue)
		roofRGB.red = minValue;
	else
	{
		roofRGB.red -= substractValue;
		roofRGB.green -= (substractValue / 2);
		roofRGB.blue -= substractValue;
	}
}

void resetRoofRGB()
{
	roofRGB.red = 0.4;
	roofRGB.green = 0.2;
	roofRGB.blue = 0.0;
}

void lowerWindmillBodyRGB(double substractValue, double minValue)
{
	if (wmBodyRGB.red - substractValue < minValue)
		wmBodyRGB.red = minValue;
	else
	{
		wmBodyRGB.red -= substractValue * 2;
		wmBodyRGB.green -= substractValue * 1.5;
		wmBodyRGB.blue -= substractValue;
	}
}

void resetWindmillBodyRGB()
{
	wmBodyRGB.red = 1.0;
	wmBodyRGB.green = 0.8;
	wmBodyRGB.blue = 0.6;
}

void drawSky()
{
	if (!night)
	{
		if (global_sun_counter > 0 && global_sun_counter < 60)
		{
			global_red -= 0.0017;
			global_green -= 0.0017;
			if (global_blue - 0.0016 < 0.1)
				global_blue = 0.1;
			else
				global_blue -= 0.0016;
			
			if (global_ground_green - 0.0006 < 0.25)
				global_ground_green = 0.25;
			else
				global_ground_green -= 0.0006;
			lowerWindmillBodyRGB(0.001, 0.6);
			lowerRoofRGB(0.001, 0.2);
		}
		else
		{
			if (global_sun_counter > 300 && global_sun_counter < 360)
			{
				if (global_shadow_green - 0.0006 < 0.25)
					global_shadow_green = 0.25;
				else
					global_shadow_green -= 0.0006;
			}
			global_red = 1;
			global_green = 1;
			global_blue = 1;
		}
	}
	if (night && thunder_black)
	{
		if (global_sun_counter > 0 && global_sun_counter < 60)
		{
			global_red += 0.0017;
			global_green += 0.0017;
			global_blue += 0.0016;

			if (global_ground_green + 0.0006 > 0.60)
				global_ground_green = 0.60;
			else
				global_ground_green += 0.0006;
			resetWindmillBodyRGB();
			resetRoofRGB();
		}
		else
		{
			global_red = 0;
			global_green = 0;
			global_blue = 0.1;
		}
		global_shadow_green = 0.6;
	}

	if (night && !thundering && thunder_white)
	{
		thunderRGB.red = 0.5;
		thunderRGB.green = 1;
		thunderRGB.blue = 1;

		global_red = 1;
		global_green = 1;
		global_blue = 1;		
	}
	glClearColor(global_red, global_green, global_blue, 0.0);
}

void drawWindmillRotator(GLdouble x, GLdouble y, GLdouble r)
{
	double alpha = 2 * PI / circle_points;
	double angle = alpha * global_windmill_counter;
	double angle90 = 2 * PI / 4;
	double angle30 = 2 * PI / 12;
	double angleX = 2 * PI / 32;

	glLineWidth(10);
	glBegin(GL_LINES);
	for (int i = 0; i < 4; i++)
	{
		glColor3f(0.251, 0.251, 0.251);
		glVertex2f(x, y);
		glVertex2f(x + r * cos(angle + i * angle90), y + r * sin(angle + i * angle90));
	}
	glEnd();

	double malo_r = 0.2;

	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(0.6275, 0.6275, 0.6275);
		glVertex2f(x + malo_r * cos(angle + i * angle90), y + malo_r * sin(angle + i * angle90));
		glVertex2f(x + r * cos(angle + i * angle90), y + r * sin(angle + i * angle90));
		glColor3f(0.251, 0.251, 0.251);
		glVertex2f(x + (r + 0.025) * cos(angle + i * angle90 + angleX), y + (r + 0.025) * sin(angle + i * angle90 + angleX));
		glVertex2f(x + (malo_r + 0.025) * cos(angle + i * angle90 + angle30), y + (malo_r + 0.025) * sin(angle + i * angle90 + angle30));
		glEnd();
	}
}

void drawSimpleCircle(GLdouble x, GLdouble y, GLdouble r, double red, double green, double blue)
{
	double alpha = 2 * PI / circle_points;
	glColor3f(red, green, blue);
	for (int i = 0; i < circle_points; i++)
	{
		double angle = i * alpha;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
}

void drawSun(){

	double R = 3.5;
	double angle = (global_sun_counter / 2) * 2 * PI / circle_points;
	double r_sun = 0.2;
	double r_moon = 0.1;
	double x = 2.0;
	x += R * cos(angle);
	double y = -1.0;
	y += R * sin(angle);

	 
	for (double i = 50; i > 0; i--)
	{
		glBegin(GL_POLYGON);
		if (!night) drawSimpleCircle(x, y, r_sun + (i / 150), 1.0, 1.0, 0.0 + (i / 50));
		if  (night && thundering) drawSimpleCircle(x, y, r_moon/4 + (i / 150), 0.8 - (i / 50), 0.8 - (i / 50), 0 + (i / 400) > 0.1 ? 0 + (i / 400) : 0.1);
		glEnd();
	}

	double alpha = 2 * PI / circle_points;

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	for (int i = 0; i < circle_points; i++)
	{
		double angle = i * alpha;
		if (night && thundering)
			glColor3f(0.9, 0.9, 0.9);
		else 
			glColor3f(1.0, 1.0, 1.0);
		if (!night)
			glVertex2f(x + r_sun * cos(angle), y + r_sun * sin(angle));
		else 
			glVertex2f(x + r_moon * cos(angle), y + r_moon * sin(angle));
	}
	glEnd();

}

void drawShadow()
{
	if (!night)
	{
		double alpha = PI / circle_points;
		double angle = (global_sun_counter * alpha) + PI;
		glBegin(GL_POLYGON);
		glColor3f(0.0, global_shadow_green, 0.0);
		glVertex3f(1.70, 0.50, 0.0);
		glVertex3f(2.30, 0.50, 0.0);
		glVertex2f(3.0 + 2 * cos(angle), 0.0);
		glVertex2f(1.0 + (global_sun_counter / 1000) + 2 * cos(angle), 0.0);
		glEnd();
	}
}

void drawWindmillBody()
{
	
	// draw foot of the walls
	drawCircle(GL_POLYGON, 2.0, 3.987, 3.5, circle_points, (circle_points / 4 * 3) - 5, (circle_points / 4 * 3) + 5, wmBodyRGB.red, wmBodyRGB.green, wmBodyRGB.blue);

	// draw windmill walls
	glColor3f(wmBodyRGB.red, wmBodyRGB.green, wmBodyRGB.blue);
	glBegin(GL_POLYGON);
	glVertex3f(1.70, 0.50, 0.0);
	glVertex3f(2.30, 0.50, 0.0);
	glVertex3f(2.20, 1.00, 0.0);
	glVertex3f(1.80, 1.00, 0.0);
	glEnd();


	// draw roof
	glColor3f(roofRGB.red, roofRGB.green, roofRGB.blue);
	glBegin(GL_POLYGON);
	glVertex3f(1.75, 1.00, 0.0);
	glVertex3f(2.25, 1.00, 0.0);
	glVertex3f(2.00, 1.25, 0.0);	
	glEnd();

	// draw roof foot
	drawCircle(GL_POLYGON, 2.0, 4.51, 3.52, 720, (720 / 4 * 3) - 9, (720 / 4 * 3) + 9, roofRGB.red, roofRGB.green, roofRGB.blue);

	// draw door
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(2.10, 0.50, 0.0);
	glVertex3f(2.20, 0.50, 0.0);
	glVertex3f(2.20, 0.65, 0.0);
	glVertex3f(2.10, 0.65, 0.0);
	glEnd();

	// draw window1
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.90, 0.70, 0.0);
	glVertex3f(2.00, 0.70, 0.0);
	glVertex3f(2.00, 0.80, 0.0);
	glVertex3f(1.90, 0.80, 0.0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glVertex3f(1.90, 0.70, 0.0);
	glVertex3f(2.00, 0.70, 0.0);
	glVertex3f(2.00, 0.80, 0.0);
	glVertex3f(1.90, 0.80, 0.0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex3f(1.95, 0.70, 0.0);
	glVertex3f(1.95, 0.80, 0.0);
	glVertex3f(2.00, 0.75, 0.0);
	glVertex3f(1.90, 0.75, 0.0);
	glEnd();

	// draw window2
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.91, 0.85, 0.0);
	glVertex3f(1.99, 0.85, 0.0);
	glVertex3f(1.99, 0.93, 0.0);
	glVertex3f(1.91, 0.93, 0.0);
	glEnd();


	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(1.91, 0.85, 0.0);
	glVertex3f(1.99, 0.85, 0.0);
	glVertex3f(1.99, 0.93, 0.0);
	glVertex3f(1.91, 0.93, 0.0);
	glEnd();


	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(1.95, 0.85, 0.0);
	glVertex3f(1.95, 0.93, 0.0);
	glVertex3f(1.99, 0.89, 0.0);
	glVertex3f(1.91, 0.89, 0.0);
	glEnd();
}

void drawGroundOld()
{
	if (night)
		drawCircle(GL_POLYGON, 2.0, -7.25, 8, circle_points, 0, 360, 0, global_ground_green, 0);
	else
		drawCircle(GL_POLYGON, 2.0, -7.25, 8, circle_points, 0, 360, 0, global_ground_green, 0);
}

void drawGround()
{
	drawCircle(GL_POLYGON, 2.3, -0.6, 2.0, circle_points, 0, 360, 0, global_ground_green - 0.23, 0);
	drawCircle(GL_POLYGON, 0.0, -0.5, 2.0, circle_points, 0, 360, 0, global_ground_green - 0.15, 0);
	drawCircle(GL_POLYGON, 4.5, -0.5, 2.0, circle_points, 0, 360, 0, global_ground_green - 0.20, 0);
	drawCircle(GL_POLYGON, 2.0, -1.0, 2.0, circle_points, 0, 360, 0, global_ground_green - 0.10, 0);

	drawCircle(GL_POLYGON, 2.0, -7.25, 8, circle_points, 0, 360, 0, global_ground_green, 0);
}

void drawCircle(GLenum mode, GLdouble x, GLdouble y, GLdouble r, GLint circle_points, int drawFrom, int drawTo, double red, double green, double blue)
{
	double alpha = 2 * PI / circle_points;
	glBegin(mode);
	glColor3f(red, green, blue);
	for (int i = 0; i < circle_points; i++)
	{	
		double angle = i * alpha;
		if (i >= drawFrom && i <= drawTo) 
		{
			glColor3f(red, green, blue);
			glVertex2f(x + r * cos(angle), y + r * sin(angle));
		}
	}
	glEnd();
}

void StartDayNight(void)
{
	if (global_sun_counter < 0)
	{
		global_sun_counter = 360;
		will_thunder = randomInt(0, 2) == 1;
		night = !night;
	}
	global_sun_counter -= 0.1;
}

void StartRunningWindmill(void)
{
	if (global_windmill_counter < 0)
	{
		global_windmill_counter = 360;
	}
	global_windmill_counter -= 1;
}

void drawThunder()
{
	if (night && will_thunder && global_windmill_counter > 300 && global_windmill_counter < 325)
	{
		if (global_windmill_counter > 300 && global_windmill_counter < 310)
		{
			thunder_black = true;
			thunder_white = false;
		}
		if (global_windmill_counter > 310 && global_windmill_counter < 315)
		{
			thunder_black = false;
			thunder_white = true;
		}
		if (global_windmill_counter > 315 && global_windmill_counter < 325)
		{
			thunder_black = true;
			thunder_white = false;
		}

		if (thundering)
		{
			for (int i = 25; i > 5; i--)
			{
				xArray[i - 6] = 1.5 + roundTwo(randomDouble(1.0, 2.0));
				yArray[i - 6] = (double) i / 5;
			}
			thundering = false;
		}
		
		glColor3f(thunderRGB.red, thunderRGB.green, thunderRGB.blue);
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < 20; i++)
		{
			glVertex2d(xArray[i], yArray[i]);
			glVertex2d(xArray[i] + roundTwo(randomDouble(0.01, 0.02)), yArray[i] + roundTwo(randomDouble(0.01, 0.02)));
		}
		glEnd();
	}
	else 
	{
		if (!thundering) 
		{
			thundering = true;
			thunderRGB.red = 0.8;
			thunderRGB.green = 1.0;
			thunderRGB.blue = 1.0;
		}
	}
}

double randomDouble(double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(gen);
}

int randomInt(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(gen);
}

double roundTwo(double x)
{
	return round(x * 100.0) / 100.0;
}

void initRgbs()
{

	wmBodyRGB.red = 1.0;
	wmBodyRGB.green = 0.8;
	wmBodyRGB.blue = 0.6;

	roofRGB.red = 0.4;
	roofRGB.green = 0.2;
	roofRGB.blue = 0.0;

	thunderRGB.red = 0.8;
	thunderRGB.green = 1.0;
	thunderRGB.blue = 1.0;
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Y_AXES * aspectRatio, 0.0, Y_AXES, -1.0, 1.0);
	initRgbs();
}

void reshape(int w, int h)
{
	if (w < h)
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
		if (state == GLUT_DOWN)
			glutIdleFunc(StartDayNight);
		else 
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

void timer(int v)
{
	StartRunningWindmill();
	glutTimerFunc(1000 / 60, timer, v);
	glutPostRedisplay();
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
	glutTimerFunc(100, timer, 0);
	glutMouseFunc(mousePress);
	glutMainLoop();

	return 0;
}

