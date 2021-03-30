#include<iostream>
#include<time.h>
using namespace std;
#include<GL\glut.h>;

void ellipseMidpoint(int xc,int yc,int xr,int yr);
void plot(int xc,int yc,int x,int y);
void putPixel(int x,int y);
void EnterIT(void);
void display(void);
void init(void);
int xc,yc,xr,yr;

void main(int argc,char** argv){
	EnterIT();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("Assignment2 EllipseMidpoint");
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
	glPointSize(5);
	//glColor3f(1.0,0,1.0);
	//putPixel(100,500);
	//putPixel(xc,yc);
	glPointSize(1.2);
	glColor3f(1.0,0,0);
	ellipseMidpoint(xc,yc,xr,yr);
	if(xr>yr){
		ellipseMidpoint(xc-(xr/2.3),yc+(yr/2.3),xr/5,yr/5);
		ellipseMidpoint(xc+(xr/2.3),yc+(yr/2.3),xr/5,yr/5);
		ellipseMidpoint(xc,yc-yr/2,yr/5,xr/5);
	}
	else if(yr>xr){
		ellipseMidpoint(xc-(xr/2.3),yc+(yr/2.3),yr/5,xr/5);
		ellipseMidpoint(xc+(xr/2.3),yc+(yr/2.3),yr/5,xr/5);
		ellipseMidpoint(xc,yc-yr/2,xr/5,yr/5);
	}
	glFlush();
}
void putPixel(int x,int y){
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}
void ellipseMidpoint(int xc,int yc,int xr,int yr){
	float x,y,dx,dy,d1,d2;
	x=0;
	y=yr;
	d1 = (yr * yr) - (xr * xr * yr) +  (0.25 * xr * xr);
	dx = 2 * yr * yr * x; 
    dy = 2 * xr * xr * y; 

	while(dx<dy){
		plot(xc,yc,x,y);
		x++; 
		if(d1<=0){
            dx = dx + (2 * yr * yr); 
            d1 = d1 + dx + (yr * yr); 
		}else{
			y--;
			dx = dx + (2 * yr * yr); 
            dy = dy - (2 * xr * xr); 
            d1 = d1 + dx - dy + (yr * yr); 
		}
		
	}
	d2 = ((yr * yr) * ((x + 0.5) * (x + 0.5))) +  ((xr * xr) * ((y - 1) * (y - 1))) -(xr * xr * yr * yr);
	while (y >= 0) {
		plot(xc,yc,x,y);
		y--; 
		if (d2 > 0)  
        { 
            dy = dy - (2 * xr * xr); 
            d2 = d2 + (xr * xr) - dy; 
        } 
        else 
        { 
            x++; 
            dx = dx + (2 * yr * yr); 
            dy = dy - (2 * xr * xr); 
            d2 = d2 + dx - dy + (xr * xr); 
        } 
	}

}

void plot(int xc,int yc,int x,int y){
	putPixel(xc+x,yc+y);
	putPixel(xc-x,yc+y);
	putPixel(xc+x,yc-y);
	putPixel(xc-x,yc-y);
	
}
void EnterIT(void){
	cout<<"Enter Center Point (Xc,Yc) :";
	cin>>xc>>yc;
	cout<<"Enter Radius X:";
	cin>>xr;
	cout<<"Enter Radius Y:";
	cin>>yr;
}