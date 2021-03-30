
#include <iostream>
using namespace std;
#include <GL\glut.h>


void putPixel(int x,int y){
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}
void lineSimple(int x1,int y1,int x2,int y2){ 
	int dx,dy;
	dx = x2 - x1;
	dy = y2 - y1;
	if(dx==0){
		dx=1;
	}
	float m = (float) dy/dx;
	float b = y1 - m * x1;
	if(m<=1){
		int x = x1;
		float  y = y1;
		cout << "x = " << x << " y = " << y << endl;
		putPixel(x,y); 
		for(int k = 0; k < dx; k++){
			x = x+1;
			y = m*x+b;
			cout << "x = " << x << " y = " << y << endl;
			putPixel(x,y);
		}
	}
	else{
		float x = x1;
		int  y = y1;
		cout << "x = " << x << " y = " << y << endl;
		putPixel(x,y); 
		for(int k = 0; k < dy; k++){
			x = (y-b)/m;
			y = y+1;
			cout << "x = " << x << " y = " << y << endl;
			putPixel(x,y);
		}
	}
}
void lineDDA(int x1,int y1,int x2,int y2){
	int dx = x2 - x1 ;
	int dy = y2 - y1 ;
	float m = (float)dy/dx ;
	if(m<=1){
		int x = x1;
		float  y = y1;
		cout << "x = " << x << " y = " << y << endl;
		putPixel(x,y); 
		for(int k = 0; k < dx; k++){
			x = x+1;
			y = y+m;
			cout << "x = " << x << " y = " << y << endl;
			putPixel(x,y);
		}
	}
	else{
		float x = x1;
		int  y = y1;
		cout << "x = " << x << " y = " << y << endl;
		putPixel(x,y);
		for(int k = 0; k < dy; k++){
			x = x+(1/m);
			y = y+1;
			cout << "x = " << x << " y = " << y << endl;
			putPixel(x,y);
		}
	}

}
void lineBres(int x1,int y1,int x2,int y2){
	int dx = x2 - x1 ;
	int dy = y2 - y1 ;
	int x = x1;
	int y = y1;
	int pk;
	for(int k = 0; k < dx; k++){
		if(k==0) pk=(2*dy)-dx;
		if(pk<0){
			x++;
			cout << "x = " << x << " y = " << y << endl;
			putPixel(x,y);
			pk=pk+(2*dy);
		}else{
			x++;
			y++;
			cout << "x = " <<  x << " y = " << y << endl;
			putPixel(x,y);
			pk=pk+(2*dy)-(2*dx);
		}
	}
}

