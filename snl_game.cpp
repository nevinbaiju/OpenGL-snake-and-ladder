#include <GL/glut.h>
#include <iostream>
#include <string>

void unit(int x, int y);
void draw_numbers();
void display_message(const char *text, int length);
void draw_text(const char *text, int length, double x, double y);
void render_ladders();

void draw_grid()
{
    glColor3f(1.0,1.0,1.0);
    glLineWidth(3.0);

    //This loop renders the horizontal lines of the board.
    for(float y = 0.667; y>=-1; y = y-0.163)
    {
	    glBegin(GL_LINES);
	        glVertex2f(-296, y); glVertex2f(296, y);
	    glEnd();
	}

	// This loop renderes the vertical lines of the board
	for(float x = -0.995; x<=1; x = x+0.199)
    {
	    glBegin(GL_LINES);
	        glVertex2f(x, 0.667); glVertex2f(x, -.96);
	    glEnd();
	}
}

void draw_numbers()
{

	double x = -.92;
	double y = -.9;
	int num = 1, length, flag=1;
	for(int i = 0; i < 10; i++)
	{
		x = -0.92;
		for(int j = 0; j<10; j++)
		{
			std::string text = std::to_string(num);
			if(num < 10)
				length = 1;
			else if(num < 100)
				length = 2;
			else
				length = 3;
			draw_text(text.c_str(), 3, x, y);
			x = x+0.2;
			if(flag)
				num = num+1;
			else
				num = num-1;
		}
		if(flag)
		{
			num = num+9;
			flag = 0;
		}	
		else 
		{
			num = num+11;
			flag = 1;
		}
		length = 2;
		y = y+0.16;

	}
}

void display_message(const char *text, int length)
{
	glColor3f(1, 1, 1);
	double x_pos = length/56.0;
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	//glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(-x_pos, .9);
	for(int i=0; i<length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void draw_text(const char *text, int length, double x, double y)
{
	glColor3f(1, 1, 1);
	double x_pos = length/56.0;
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	//glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(x, y);
	for(int i=0; i<length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void render_ladders()
{
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
		glVertex2f(-.85, -.84); glVertex2f(-.56, -.4);
		glVertex2f(-0.25, -.84); glVertex2f(.23, -.78);
		glVertex2f(0.75, -.84); glVertex2f(.86, -.4);
		glVertex2f(-0.85, -.5); glVertex2f(-.78, -.28);
		glVertex2f(0.45, -.5); glVertex2f(-.23, .38);
		glVertex2f(0.85, 0); glVertex2f(.35, 0.05);
		glVertex2f(0.73, 0.3); glVertex2f(.82, 0.55);
		glVertex2f(-0.85, 0.31); glVertex2f(-.75, 0.55);
	glEnd();
}