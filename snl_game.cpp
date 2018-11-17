#include <GL/glut.h>
#include <iostream>
#include <string>

void unit(int x, int y);
void display_message(const char *text, int length);

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
	/*
	double x = -0.995;
	glBegin(GL_LINES);
	        glVertex2f(x, 0.667); glVertex2f(x, -.96);
	glEnd();
	*/

	// This loop renderes the vertical lines of the board
	for(float x = -0.995; x<=1; x = x+0.199)
    {
	    glBegin(GL_LINES);
	        glVertex2f(x, 0.667); glVertex2f(x, -.96);
	    glEnd();
	}

    std::string msg ("Welcome, press Enter to roll the dice");
    display_message(msg.c_str(), msg.length());

}

void display_message(const char *text, int length)
{
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