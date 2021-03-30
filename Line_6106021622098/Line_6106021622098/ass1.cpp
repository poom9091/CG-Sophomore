#include<iostream>
using namespace std;
#include "Line_6106021622098.h"
#include<GL\glut.h>
void init (void);
void display(void);
void main(int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition ( 50, 100);
	glutInitWindowSize (640,480);
	glutCreateWindow (" OpenGL Program Assignment #1 : Line ");
	init ( );
	glutDisplayFunc (display);
	glutMainLoop ( );
}
void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D ( 0.0, 640.0, 0.0, 480.0);
}
void display (void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glPointSize(1);
	glColor3f (0.0, 0.0, 1.0);
	lineSimple( 50, 50, 50, 300);
	lineSimple( 50, 50, 300, 300);
	lineSimple( 50, 50, 300, 50);

	glColor3f (1.0, 0.0, 0.0);
	for(int n = 10 ; n <= 240 ; n += 10) {
		lineSimple( 50, 50, 50 + n, 300);
		lineSimple( 50, 50, 300, 50 + n );
	}
	glColor3f (0.0, 0.0, 1.0);
	lineDDA( 350, 50, 350, 300);
	lineDDA( 350, 50, 600, 300);
	lineDDA( 350, 50, 600, 50);
	glColor3f (1.0, 0.0, 0.0);
	for(int n = 10 ; n <= 240 ; n += 10) {
		lineDDA( 350, 50, 350 + n, 300);
		lineDDA( 350, 50, 600, 50 + n );
	}
	glColor3f (1.0, 0.0, 0.0);
	for(int n = 10 ; n <= 100 ; n += 10)
		lineBres ( 200, 350, 500, 350 + n );
	glFlush ( );
}