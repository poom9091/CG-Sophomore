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
//////////////////ประกาศ Function////////////////////////////
void init(void);
void myDisplay(void);
void myKeyboard(GLubyte key,GLint x,GLint y);//สำหรับตัวอักษรธรรมดา
void specialKey(GLint specialKey , GLint x, GLint y);//สำหรับตัวอักษรพิเศษ
void myMouse(GLint button,GLint action,GLint x,GLint y);//สำหรับ ActionMouse
void showText(int x,int y,char text[]);//สำหรับแสดงข้อความ
void showMenu();//(Status=0)
void playGame();//ทำงานเมื่อกดF1(Status=1)
void compleateGame();//cleargame(Status=2)
void TimeOut();//หมดเวลา(Status=3)
void exitGame();//ทำงานตอนกด F10
void countTime(int value);//นับเวลา
void setupRectangle();//กำหนดค่าเริ่มต้นให้กับวัตถุ
int checkRectangle(int x,int y);//checkว่ากดโดนหรือป่าว
void moveRec(int value);//ช่วยให้รูปขยับ
void drawShape(Rectangle r);//วาดรูป


//////////////////ประกาศ ตัวแปร////////////////////////////
const int MAX_RECTANGLE = 10;//จำหนดจำนวนรูป 
Rectangle rec[MAX_RECTANGLE];
const int ScreenWidth = 800;
const int ScreenHeight = 600;
int Score = 0;//เก็บคะแนน
char strScore[15];
int Time = 0;//เก็บเวลา
char strTime[15];
int Status = 0;

void main (int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(ScreenWidth,ScreenHeight);
	glutCreateWindow("Assignment3_02");
	init();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(specialKey);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutMainLoop();
}

void init (void){
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,ScreenWidth,0.0,ScreenHeight);
}

void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);
	if(Status == 1)playGame();
	else if(Status == 0)showMenu();
	else if(Status == 2)compleateGame();
	else if(Status == 3)TimeOut();
	glFlush();
}

//////////////////showMenu////////////////////////////
void showMenu(){
	glColor3f(0.0,0.0,0.0);
	showText(300,450,"F1 -Play Game");
	showText(300,400,"F2 -Stop Game");
	showText(300,350,"F10 -Exit Game");
}

//////////////////จะแสดงผลตอนClearGame////////////////////////////
void compleateGame(){
	glColor3f(0.0,0.0,0.0);
	showText(350,400,"Score : 10");
	showText(250,350,"You Win,press space key to menu.");
}

//////////////////จะแสดงผลตอนหมดเวลา////////////////////////////
void TimeOut(){
	glColor3f(0.0,0.0,0.0);
	showText(350,400,"Time out!");
	showText(250,350,"You lose,press space key to menu.");
}

//////////////////จะทำงานตอนกด F10////////////////////////////
void exitGame(){
	exit(0);
}

//////////////////กำหนดขนาก สี ของวัตถุ////////////////////////////
void setupRectangle()
{
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
		}
		if(rec[n].show) //drawShape(rec[n]);//สร้างรูปอื่นที่ไม่ใช่ 4 เหลี่ยใ
			glRecti(rec[n].x, rec[n].y, rec[n].x + rec[n].size, rec[n].y + rec[n].size);//สร้างรูป 4 เหลี่ยม
	}
	sprintf(strTime, "Time : %d", Time);
	showText(10, ScreenHeight - 20, strScore);//แสดงผลเวลา
	sprintf(strScore, "Score : %d", Score);
	showText(ScreenWidth - 100, ScreenHeight - 20, strTime);//แสดงคะแนน
}

////////////สร้างรูป polygon////////////////////
/*void drawShape(Rectangle r)
{
	int point = 50;
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


//////////////////Function ขยันรูป////////////////////////////
void moveRec(int value)
{
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

////////////////////Function รับค่าจาก Keyboard(specialKey)//////////////////////////
void specialKey(GLint specialKey , GLint x, GLint y){
	if(specialKey==GLUT_KEY_F1&&Status == 0){//F1
		Status=1;
		Score=0;
		Time = 0;
		setupRectangle();
		glutTimerFunc(1000, countTime, 1000);//จับเวลานับ 1000=1วินาที
		glutTimerFunc(15, moveRec, 15);//ตัวที่ทำให้รูปขยับ//กำหนดความเร็วของวัตถุ 
	}
	else if(specialKey ==GLUT_KEY_F2&&Status == 1) {//F2
		Status =0;
	}
	else if(specialKey ==GLUT_KEY_F10&&Status == 0) {//F10
		exitGame();
	}
	glutPostRedisplay();
}

////////////////////Function รับค่าจาก Keyboard//////////////////////////
void myKeyboard(GLubyte key,GLint x,GLint y){
	if(key == ' ' && (Status == 3||Status == 2)) Status = 0; //(' ')คือตอนกด SpaceBar
	glutPostRedisplay();
}

////////////////////Function คลิก Mouse//////////////////////////
void myMouse(GLint button,GLint action,GLint x,GLint y){
	if(Status == 1){//ทำงานตอน Playgame เท่านั้น
		if(button == GLUT_LEFT_BUTTON&&action==GLUT_DOWN){//เมื่อกดคลิกขวา
			y=ScreenHeight-y;
			cout<<"Point of Click : "<<x<<", "<<y<<endl;
			int pos = checkRectangle(x, y);
			if(pos > -1){//ทำงานถ้าเรากดโดนรูป
				rec[pos].show = !rec[pos].show;//ทำให้รูปกดเรากดนั้นหายไอ
				Score ++; //บวกคะแนน
				if(Score== MAX_RECTANGLE ) Status=2;//ทำงานตอนที่เรา Score ของเราเท่ากับจำนวนรูป
			}
			glutPostRedisplay();
		}
	}
}
////////////////////นับเวลา//////////////////////////
void countTime(int value)
{
	Time += 1;
	glutPostRedisplay();
	if(Status == 1) glutTimerFunc(value, countTime, value);
	if(Time > 30) Status = 3;
}

/////////////////////checkว่ากดโดนหรือป่าว//////////////////////////
int checkRectangle(int x, int y)
{
	for(int n = 0; n < MAX_RECTANGLE; n++){
		if(rec[n].show)
		if(x >= rec[n].x && x <= rec[n].x + rec[n].size)
			if(y >= rec[n].y && y <= rec[n].y + rec[n].size){
				return (n);
			}
	}
	return (-1);
}


