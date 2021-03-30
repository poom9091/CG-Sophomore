#include<iostream>
#include<time.h>
using namespace std;
#include<GL\glut.h>;

void circleMidpoint(int xc,int yc,int r);
void plot(int xc,int yc,int x,int y);
void putPixel(int x,int y);
void EnterIT(void);
void display(void);
void init(void);
int x,y,r;

void main(int argc,char** argv){
	EnterIT();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(400,400);
	glutInitWindowSize(800,600);
	glutCreateWindow("Assignment2 CircleMidpoint");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

void init(void){
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D ( 0.0, 800.0, 0.0, 600.0);
}
void display(void){
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0,0);
	glPointSize(1.2);
	circleMidpoint(x,y,r);
	circleMidpoint(x-(r/2.3),y+(r/2.3),r/5);
	circleMidpoint(x+(r/2.3),y+(r/2.3),r/5);
	circleMidpoint(x,y-(r/2.3),r/5);
	glFlush();
}
void putPixel(int x,int y){
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}
void circleMidpoint(int xc,int yc,int r){
	int x,y,p;
	x=0;
	y=r;
	plot(xc,yc,x,y);
	p=1-r;
	while(x<y){
		x++;
		if(p<=0){
			p=p+(2*x)+1;
		}else{
			
			y--;
			p = p+(2*x)+1-(2*y);
		}
		plot(xc,yc,x,y);
	}
}

void plot(int xc,int yc,int x,int y){
	putPixel(xc+x,yc+y);
	putPixel(xc-x,yc+y);
	putPixel(xc+x,yc-y);
	putPixel(xc-x,yc-y);
	putPixel(xc+y,yc+x);
	putPixel(xc-y,yc+x);
	putPixel(xc+y,yc-x);
	putPixel(xc-y,yc-x);
}
void EnterIT(void){
	cout<<"Enter Center Point (Xc,Yc) :";
	cin>>x>>y;
	cout<<"Enter Radius :";
	cin>>r;
}