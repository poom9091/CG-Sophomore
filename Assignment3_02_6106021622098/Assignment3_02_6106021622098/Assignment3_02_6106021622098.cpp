#include<iostream>
#include<time.h>
using namespace std;
#include <GL/glut.h>
/////////////////กำหนดเป็น object///////////////
class Rectangle{
public:
	int x,y,size,speedX, speedY,color;
	bool show;
};

///////////////////ประกาศ Function///////////////////////////
void init(void);
void myDisplay(void);
void myKeyboard(GLubyte key,GLint x,GLint y);//สำหรับตัวอักษรธรรมดา
void showText(int x,int y,char text[]);//สำหรับแสดงข้อความ
void playGame();//ทำงานเมื่อกดP(Status=1)
void stopGame();//ทำงานเมื่อกดS(Status=0)
void setupRectangle();//กำหนดค่าเริ่มต้นให้กับวัตถุ
void moveRec(int value);//ช่วยให้รูปขยับ
void drawShape(Rectangle r);//วาดรูป

//////////////////ประกาศ ตัวแปร////////////////////////////
const int MAX_RECTANGLE = 5;//จำหนดจำนวนรูป 
Rectangle rec[MAX_RECTANGLE];
const int ScreenWidth = 800;
const int ScreenHeight = 600;
int Status = 0;

void main (int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(ScreenWidth,ScreenHeight);
	glutCreateWindow("Assignment3_02");
	init();
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutMainLoop();
}

void init (void){
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	setupRectangle();//กำหนดค่าเริ่มต้นให้กับวัตถุทำงานแค่ครั่งเดียว
	gluOrtho2D(0.0,ScreenWidth,0.0,ScreenHeight);
}

void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);
	if(Status == 1)playGame();
	else if(Status == 0)stopGame();
	glFlush();
}

//////////////////กำหนดขนาก สี ของวัตถุ////////////////////////////
void setupRectangle(){
	for(int n = 0; n < MAX_RECTANGLE; n++){
		rec[n].color=rand() % 4 + 1;
		cout<<rec[n].color;
		rec[n].x = rand() % 700 + 50;
		rec[n].y = rand() % 500 + 50;
		rec[n].size = rand() % 30 + 30;
		rec[n].show = true;
		rec[n].speedX = 1 + rand() % 5;
		rec[n].speedY = 1 + rand() % 5;
	}
}

/////////////////ทำงานตอนกด PLAY///////////////
void playGame(){
	for(int n = 0; n < MAX_RECTANGLE; n++){
		switch(rec[n].color){
			case 1:glColor3f(1.0,0.0,0.0);break;
			case 2:glColor3f(0.0,1.0,0.0);break;
			case 3:glColor3f(0.0,0.0,1.0);break;
			case 4:glColor3f(0.0,0.0,0.0);break;
		}//setcolor
		if(rec[n].show) //drawShape(rec[n]);
			glRecti(rec[n].x, rec[n].y, rec[n].x + rec[n].size, rec[n].y + rec[n].size);//สร้างรูป 
	}
	glColor3f(0.0,0.0,0.0);
	showText(300,ScreenHeight - 580,"Play Animation");
}

////////////สร้างรูป polygon////////////////////
/*void drawShape(Rectangle r)
{
	int point = 4;
	float value = 6.28 / point;
	float x, y;
	glBegin(GL_POLYGON);
	for(float radian = 0.0f; radian <= 6.28; radian += value){
		x = r.x + r.size * cos(radian);
		y = r.y + r.size * sin(radian);
		glVertex2i(x, y);
	}
	glEnd();
}*/

/////////////////ทำงานตอนกด STOP(Codeเหมือน PLAY///////////////
void stopGame(){
	for(int n = 0; n < MAX_RECTANGLE; n++){
		switch(rec[n].color){
			case 1:glColor3f(1.0,0.0,0.0);break;
			case 2:glColor3f(0.0,1.0,0.0);break;
			case 3:glColor3f(0.0,0.0,1.0);break;
			case 4:glColor3f(0.0,0.0,0.0);break;
		}
		if(rec[n].show) //drawShape(rec[n]); //รุปร่างอื่นๆ
			glRecti(rec[n].x, rec[n].y, rec[n].x + rec[n].size, rec[n].y + rec[n].size);//ทำให้เป็นรูป 4 เหลี่ยม
	}
	glColor3f(0.0,0.0,0.0);
	showText(300,ScreenHeight -580,"Stop Animation");
}

//////////////////Function ขยันรูป////////////////////////////
void moveRec(int value){
	for(int n = 0; n < MAX_RECTANGLE; n++){
		if(rec[n].show){
			rec[n].x += rec[n].speedX;
			if(rec[n].x >= ScreenWidth - rec[n].size || rec[n].x < 0){
				rec[n].speedX = - rec[n].speedX;
			}
			rec[n].y += rec[n].speedY;
			//else if(rec[n].x < 0) rec[n].speedX = - rec[n].speedX;
			
			if(rec[n].y >= ScreenHeight - rec[n].size || rec[n].y < 0){
				rec[n].speedY = - rec[n].speedY;
			}
			//else if(rec[n].y < 0) rec[n].speedY = - rec[n].speedY;
		}
	}
	glutPostRedisplay();
	if(Status == 1)
		glutTimerFunc(value, moveRec, value);	
}



////////////////////ตัวสั่ง Print ตัวหนังสือ//////////////////////////
void showText(int x,int y,char text[]){
	glRasterPos2i(x,y);
	for(int n=0;text[n]!='\0';n++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[n]);
}
////////////////////Function รับค่าจาก Keyboard//////////////////////////
void myKeyboard(GLubyte key,GLint x,GLint y){
	key=toupper(key);
	if(key=='P'&&Status == 0){
		Status=1;
		glutTimerFunc(15, moveRec, 15);//ตัวที่ทำให้รูปขยับ
	}
	else if(key =='S'&&Status == 1) {
		Status =0;
	}
	glutPostRedisplay();
}
