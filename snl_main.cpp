#include <GL/glut.h>
#include <iostream>
#include "snl_game.h"
#include <string>
#include <bits/stdc++.h> 

void init();
void display_callback();
void reshape_callback(int w, int h);
void input_callback(int, int, int);
void timer_callback(int);

std::string msg ("Player 1's turn: press right arrow to roll dice");

int player_1_position = 0;
int player_2_position = 0;
int turn = 0;
int dice_val;
int rolling = 1;
int victory = 0;

int main(int argc, char**argv)
{
	init_snakes_ladders();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(550, 600);
	glutCreateWindow("Snake and Ladder-OpenGL");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutSpecialFunc(input_callback);
	glutTimerFunc(10, timer_callback, 0);
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
	//std::string msg ("Welcome, press Enter to roll the dice");
	display_message(msg.c_str(), msg.length());
	render_board();
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

void input_callback(int key, int x, int y)
{
	if(rolling)
	{
		if(victory)
			exit(0);
	    if(key == GLUT_KEY_RIGHT)
	    {
			system("canberra-gtk-play -f wav/twitch.wav");
	    	dice_val = roll_dice();
	    	//std::cout<<"Player "<< turn <<" has rolled a" << dice_val << '\n';
	    	msg = "Player "+std::to_string(turn+1)+" has rolled a "+std::to_string(dice_val);
	    	rolling = 0;
	    }
	}
}

void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(10, timer_callback, 0);
}