#include<iostream>
using namespace std;
#include <GL/glut.h>
///////////////////ประกาศ Function///////////////////////////
void init(void);
void myDisplay(void);
void myMouse(GLint button,GLint action,GLint x,GLint y);
void myPassiveMotion(GLint x,GLint y);
void setPixel(int x,int y);
void myKeyboard(GLubyte key,GLint x,GLint y);
void specialKey(GLint specialKey,GLint x,GLint y);
void motionFunc(GLint x,GLint y); //function ที่ทำให้เราสามารถ drag mouse ได้(กดค้างแล้วลาก)
void setColor(int Color);
void drawShape(int Type);
void setLine(int WLine);
void showText(int x,int y,char text[]);

//////////////////ประกาศ ตัวแปร////////////////////////////
const int ScreenWidth = 800;
const int ScreenHeight = 600;
GLint X1,Y1,X2,Y2;
int Type,Color,WLine;
int mouseX,mouseY;
char strMouse[10];
char type[10] = {"Type: "}; char color[10] = {"Color: "};
char strText[][10] = {"Lines","Rectangle","Triangle"};
char strColor[][10] = {"Red","Green","Blue"};

void main (int argc,char **argv){
	X1=Y1=X2=Y2=0;
	Type=Color=1;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(ScreenWidth,ScreenHeight);
	glutCreateWindow("Example use Mouse");
	init();
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(specialKey);
	glutMotionFunc(motionFunc);
	glutMouseFunc(myMouse);
	glutPassiveMotionFunc(myPassiveMotion);
	glutMainLoop();
}
 void init(void){
	 glClearColor(1.0,1.0,1.0,0.0);
	 glColor3f(1.0,0.0,0.0);
	 glPointSize(3.0);
	
	 glMatrixMode(GL_PROJECTION);
	 gluOrtho2D(0.0,ScreenWidth,0.0,ScreenHeight);
 }

 void myDisplay(void){
	 glClear(GL_COLOR_BUFFER_BIT);
	 setColor(Color);
	 drawShape(Type);
	 setLine(WLine);
	 showText(5,ScreenHeight -15,type);
	 showText(50,ScreenHeight -15,strText[Type-1]);
	 showText(ScreenWidth- 110,ScreenHeight-15,color);
	 showText(ScreenWidth- 50,ScreenHeight-15,strColor[Color-1]);
	 showText(ScreenWidth- 100,10,strMouse);
	 glFlush();
 }
 ////////////////////กำหนด ขนาดเส้น//////////////////////////
 void setLine(int WLine){
	 switch(WLine){
		case 1: glLineWidth(1);break;
		case 2: glLineWidth(2);break;
		case 3: glLineWidth(3);break;
	 }
 }
 ////////////////////กำหนด สี//////////////////////////
 void setColor(int Color){
	 switch(Color){
		case 1:glColor3f(1.0,0.0,0.0);break;
		case 2:glColor3f(0.0,1.0,0.0);break;
		case 3:glColor3f(0.0,0.0,1.0);break;
		case 4:glColor3f(1.0,0.0,0.0);break;
	 }
 }
  ////////////////////กำหนดรูแบบรูป//////////////////////////
 void drawShape(int Type){
	 if(Type == 1){
		 glBegin(GL_LINES);
			glVertex2i(X1,Y1);
			glVertex2i(X2,Y2);
		glEnd();
		glColor3f(0.0,0.0,0.0);
		setPixel(X1,Y1); setPixel(X2,Y2);
	 }
	 else if(Type == 2){
		 glBegin(GL_LINE_LOOP);
			glVertex2i(X1,Y1);
			glVertex2i(X1,Y2);
			glVertex2i(X2,Y2);
			glVertex2i(X2,Y1);
		glEnd();
		glColor3f(0.0,0.0,0.0);
		setPixel(X1,Y1); setPixel(X1,Y2);
		setPixel(X2,Y2); setPixel(X2,Y1);
	 }
	 else if(Type == 3){
		 glBegin(GL_LINE_LOOP);
			glVertex2i(X1,Y1);
			glVertex2i(X2,Y2);
			glVertex2i(X2,Y1);
		glEnd();
		glColor3f(0.0,0.0,0.0);
		setPixel(X1,Y1);
		setPixel(X2,Y2); setPixel(X2,Y1);
	 }
 }
  ////////////////////แสดงข้อความ//////////////////////////
 void showText(int x,int y,char text[]){
	 glRasterPos2i(x,y);
	 for(int n=0;text[n] != '\0';n++)
		 glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[n]);
 }
 
 ////////////////////action ของ Mouse//////////////////////////
 void myMouse (GLint button,GLint action,GLint x,GLint y){

	 ////////Lock จุดเริ่มต้น
	 if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
		 X1=x;Y1=ScreenHeight - y;
	 }

	 ////////Lock จุดปลายทาง
	 else if(button == GLUT_LEFT_BUTTON && action == GLUT_UP){//ไม่ต้องใส่ else นี้ code ก็ทำงานได้
		 X2=x;Y2=ScreenHeight - y;
	 }
 }
 ////////////////ส่วนที่เพิ่มมาจาก ชีท การDragMouse//////////////
 void motionFunc(GLint x,GLint y){
	 y=600-y;
	 sprintf(strMouse,"(%d,%d)",x,y);
	 X2 = x; Y2 = y;//จุดปลายของเส้นจะตรงกับตำแหน่งของMouseเราตอนDragอยู่
	 glutPostRedisplay();
 }

 void myPassiveMotion(GLint x,GLint y){
	 y=600-y;
	 sprintf(strMouse,"(%d,%d)",x,y);
	 glutPostRedisplay();
		
 }
 
 void setPixel(int x,int y){
	 glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
 }

 void myKeyboard(GLubyte key,GLint x,GLint y){
	 switch(toupper(key)){
		case 27:exit(0);
		case 'R':Color = 1;break;
		case 'G':Color = 2;break;
		case 'B':Color = 3;break;
		case 'K':Color = 4;break;
		case '1':WLine =1 ;break;
		case '2':WLine =2 ;break;
		case '3':WLine =3 ;break;
	 }
	 glutPostRedisplay();
 }
 void specialKey(GLint specialKey,GLint x,GLint y){
	 if (specialKey == GLUT_KEY_F1) Type =1;
	 else if (specialKey == GLUT_KEY_F2)Type =2;
	 else if (specialKey == GLUT_KEY_F3)Type =3;
 }