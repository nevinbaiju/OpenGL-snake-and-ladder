#include <GL/glut.h>
#include <iostream>
#include "snl_game.h"

void init();
void display_callback();
void reshape_callback(int w, int h);

int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(550, 600);
	glutCreateWindow("Snake and Ladder-OpenGL");
	glutDisplayFunc(display_callback);
	//glutReshapeFunc(reshape_callback);
	//glutSpecialFunc(input_callback);
	//glutTimerFunc(100,timer_callback,0);
	init();
	glutMainLoop();
	return 0;
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	draw_grid();
	std::string msg ("Welcome, press Enter to roll the dice");
	display_message(msg.c_str(), msg.length());
	draw_numbers();
	render_ladders();
	glutSwapBuffers();
}

void render_text()
{
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			std::cout<<"nothing";
		}
	}
}

void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLfloat)(w), GLfloat(h+10));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 10, 0.0, 10, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}