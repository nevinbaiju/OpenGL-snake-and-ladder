#include <GL/glut.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void unit(int x, int y);
void draw_numbers();
void display_message(const char *text, int length);
void draw_text(const char *text, int length, double x, double y);
void draw_grid();
void render_ladders();
void render_snakes();
void render_board();
void draw_player(float cx, float cy);
void plot_player(int player_id, int position);
int roll_dice();
void update_piece();

extern int player_1_position;
extern int player_2_position;
extern std::string msg;
extern int turn;
extern int dice_val;
extern int rolling;

void render_board()
{
	draw_grid();
	render_ladders();
	render_snakes();
	draw_numbers();
	if(((player_1_position+dice_val)>100) && turn == 0)
	{
		dice_val = 0;
	}
	else if (((player_2_position+dice_val)>100) && turn)
	{
		dice_val = 0;
	}
	else if((player_1_position == 100)|(player_2_position == 100))
	{
		msg = "Game over";
	}
	else
	{
		update_piece();
	}
}

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
			draw_text(text.c_str(), text.length(), x, y);
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
	glLineWidth(5.0);
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

void render_snakes()
{
	glLineWidth(5.0);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex2f(-0.65, 0.31); glVertex2f(-.55, 0.55);
		glVertex2f(0.15, 0.31); glVertex2f(0.18, 0.55);
		glVertex2f(0.55, 0.31); glVertex2f(0.63, 0.55);
		glVertex2f(0.35, 0.37); glVertex2f(-0.05, -0.34);
		glVertex2f(-0.65, 0.06); glVertex2f(-0.62, -0.68);
		glVertex2f(0.25, -0.12); glVertex2f(0.25, -0.38);
		glVertex2f(-0.85, -0.03); glVertex2f(-0.35, 0.04);
		glVertex2f(-.25, -0.78); glVertex2f(0.25, -0.83);
	glEnd();
}

void update_piece()
{
	if(dice_val>0)
	{
		if(turn)
		{
			player_2_position++;
			dice_val--;
			//usleep(500000);
		}
		else
		{
			player_1_position++;
			dice_val--;
			//usleep(500000);
		}
	}
	else if(rolling == 0)
	{
		if(turn)
			turn = 0;
		else
			turn = 1;
		rolling = 1;
	}
	plot_player(0, player_1_position);
	plot_player(1, player_2_position);
}

void draw_player(float cx, float cy)
{	
	float r = 0.02;
	int num_segments = 360;
	glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}

void plot_player(int player_id, int position)
{
	double x, y, x_increment = 0.199, y_increment = 0.1625, x_pos, y_pos;
	if(player_id)
	{
		glColor3f(1, 0.5, 0.5);
		x = -0.85;
		y = -0.915;
	}
	else
	{
		glColor3f(0, 0.5, 0.5);
		x = -0.95;
		y = -0.836;
	}
	int units_place = position%10;
	int tens_place = position/10;


	if((tens_place%2 == 0) && (units_place != 0))
	{
		x_pos = x+x_increment*(units_place-1);
		y_pos = y+y_increment*tens_place;
	}
	else if((tens_place%2 != 0) && (units_place == 0))
	{
		x_pos = x+x_increment*9;
		y_pos = y+y_increment*(tens_place-1);
	}
	else if(units_place != 0)
	{
		x_pos = x+x_increment*(10-(units_place));
		y_pos = y+y_increment*tens_place;
	}
	else
	{
		x_pos = x;
		y_pos = y+y_increment*(tens_place-1);
	}
	draw_player(x_pos, y_pos);

}

int roll_dice()
{
	srand(time(NULL));
	return rand()%6+1;
}