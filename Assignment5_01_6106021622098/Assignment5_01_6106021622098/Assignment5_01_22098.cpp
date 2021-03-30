#include <iostream>
using namespace std;
#include<GL/glut.h>
//////////////Function//////////////
void init (void);
void myDisplay(void);
void myKeyboard(GLubyte key,GLint x,GLint y);//functionใช้รับค่าจาก keyboard
//void mySpecial(GLint key,GLint x,GLint y);//functionใช้รับค่าจาก keyboard(Specialkey)
void myMouse(GLint button,GLint action,GLint x,GLint y);//functionใช้รับค่าจาก Mouse
//void showText(int x,int y,char text[]); //แสดงข้อคว่ม
void define3dView();
void defineLight();//function กำหนดทิศทางของแสเง
void Rotate(int value);//function ที่ทำให้หมุดได้
void Move(int value);//function ที่ทำให้เคลื่อนที่ได้

//////////////ตัวแปร//////////////
bool play=false;//เก็บสถานนะของการเล่น
int SPtime=100;
int shape=0;//เก็บสถานนะของการเปลี่ยนวัสถุ
int angle = 0;//เก็บรัศมี
GLfloat light_color[]={1.0,1.0,1.0};//สีของแสง
GLfloat light_position[]={30.0,30.0,30.0,0.0};//ตำแหน่งของแสง
int tx=0;
int speed=1;

//char angleText[15]="Angle : 0";
//char positionText[24]="Light X : 50 , Y : 50";

//////////////Main//////////////
void main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Assignment5_1");
	init();
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);//เปิดใช้งาน รับค่าจาก keyboard
	//glutSpecialFunc(mySpecial);//เปิดใช้งาน รับค่าจาก keyboard(Specialkey)
	glutMouseFunc(myMouse);//เปิดใช้งาน รับค่าจาก Mouse

	//glutTimerFunc(SPtime,Rotate,SPtime);
	//glutTimerFunc(20,Move,20);

	glutPostRedisplay();
	glutMainLoop();
}
void init(void){
	glClearColor(1.0,1.0,1.0,0.0);//กำหนดสีหน้าจอ
	define3dView();
	defineLight();
}


void define3dView(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50,50,-50,50,-30,30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//////////////Function Setสีและตำแหน่งของแสง//////////////
void defineLight(){
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);//Set ตำแหน่งแสง 
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);//Set สีแสง 
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);//Set สีแสง 
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_color); //Set สีแสง 
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();//วัสถุหลัก
		glRotatef(angle,0.0,0.0,1.0);//ทำให้วัตถุหมุน(องศา,หมุนตามแกน x,หมุนตามแกน y,หมุนตามแกน z)

		glPushMatrix();//วัสถุย่อยอันที่ 1 (ขวา)
			glTranslatef(15,0.0,0.0);//ทำให้วัตถเคลื่อนย้าย x + 15
			switch (shape){
				case  0: glutSolidSphere(5.0,20,20); break;//รปวงกลม(รัศมี,จำนวนเส้นรอบแกนz,จำนวนชั้นแกนz);
				case  1: glutSolidCube(8.0); break;//รูปสี่เหลี่ยม(ความยามเส้นของแต่ละด้าน);
				//case  1: glutSolidCone(4.0,20,20,20); break; //รูปกรวย(รัศมีฐาน,ความสูงกรวย,จำนวนเส้นรอบแกนz,จำนวนชั้นแกนz);
				case  2: glutSolidTorus(1.5,5,10,20); break;//รูปโดนัท(รัศมีฐาน,ความสูงกรวย,จำนวนเส้นรอบแกนz,จำนวนชั้นแกนz)
				//glutSolidTeapot(GLdouble size); //รุปกาน้ำ
				//glutWire.....จะแสดงแค่เส้นปะ
				//glutSolid.....จะแสดงพื้นผิว
			}
		glPopMatrix();//เสร็จสินการสร่้างวัสถุย่อยอันที่ 1

		glPushMatrix();//วัสถุย่อยอันที่ 2 (ซ้าย)
			glTranslatef(-15,0.0,0.0);//ทำให้วัตถเคลื่อนย้ายตามแกน x -15
			switch (shape){
				case  0: glutSolidSphere(5.0,20,20); break;
				case  1: glutSolidCube(8.0); break;
				case  2: glutSolidTorus(1.5,5,10,20); break;
			}
		glPopMatrix();//เสร็จสินการสร่้างวัสถุย่อยอันที่ 2

		glPushMatrix();//วัสถุย่อยอันที่ 3 (บน)
			glTranslatef(0,15.0,0.0);//ทำให้วัตถเคลื่อนย้ายตามแกน Y + 15
			switch (shape){
				case  0: glutSolidSphere(5.0,20,20); break;
				case  1: glutSolidCube(8.0); break;
				case  2: glutSolidTorus(1.5,5,10,20); break;
			}
		glPopMatrix();//เสร็จสินการสร่้างวัสถุย่อยอันที่ 3

		glPushMatrix();//วัสถุย่อยอันที่ 4 (ล่าง)
			glTranslatef(tx,-15.0,0.0);//ทำให้วัตถเคลื่อนย้ายตามแกน Y - 15
			switch (shape){
				case  0: glutSolidSphere(5.0,20,20); break;
				case  1:glutSolidCube(8.0); break;
				case  2: glutSolidTorus(1.5,5,10,20); break;
			}
		glPopMatrix();//เสร็จสินการสร่้างวัสถุย่อยอันที่ 4

		//glScalef(1.0,3.0,1.0);//การยืด x*1,y*3,z*1	
	glPopMatrix();//เสร็จสินการสร่้างวัสถุหลัก
	glutSwapBuffers();
	glFlush();
}

//////////////Function Mouse //////////////
void myMouse(GLint button,GLint action,GLint x,GLint y){
	if(button == GLUT_LEFT_BUTTON) { //จะทำเงื่อนไขทำงานคลิกซ้าย
		if(!play){//จะทำเงื่อนไขถ้ารูปยังไม่ขยัน(ถ้าไม่มีเวลาคลิกซ้ายรูปจะหมุนเร็วขึ้นทุกครั้งที่คลิกmouse)
			play=true;//เปลี่ยนสถานนะให้เล่น
			glutTimerFunc(100,Rotate,100);//เข้าไปทำงาน function ทุก 100 มิลลิวินาที
		}
	}else if (button == GLUT_RIGHT_BUTTON) play=false;//เปลี่ยนสถานนะให้หยุดเล่นตอนคลิกขวา
	glutPostRedisplay();
}

//////////////Function mySpecial //////////////
/*void mySpecial(GLint key,GLint x,GLint y){
	//if(key == GLUT_KEY_RIGHT) play=false; 
	//else if (key == GLUT_KEY_LEFT){
		//if(play){
			play=true;
		//}
	//}
	
	glutPostRedisplay();
}*/

//////////////Function Keyboard //////////////
void myKeyboard(GLubyte key,GLint x,GLint y){
	key=toupper(key);//ทำการเปลี่ยนเป็นตัวพิมพ์ใหญ่
	if(key=='R'){//เปลี่ยนเป็นสีแดงเมื่อกด R
		light_color[0]=1.0;
		light_color[1]=0.0;
		light_color[2]=0.0;
		glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
	}else if(key=='G'){//เปลี่ยนเป็นสีเขียวเมื่อกด G
		light_color[0]=0.0;
		light_color[1]=1.0;
		light_color[2]=0.0;
		glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
	}else if(key=='B'){//เปลี่ยนเป็นสีน้ำเงินเมื่อกด B
		light_color[0]=0.0;
		light_color[1]=0.0;
		light_color[2]=1.0;
		glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
	}else if(key=='W'){//เปลี่ยนเป็นสีขาวเมื่อกด W
		light_color[0]=1.0;
		light_color[1]=1.0;
		light_color[2]=1.0;
		glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
	}else if(key=='S') shape=0;  //รูปวงกลม
	else if(key=='C') shape=1;	//รูปสีเหลี่ยม
	else if(key=='T') shape=2;	//รูปโดนัท
	else if(key== 27 ) exit (0); //ออกจากโปรแกรมตอนกด ESC
	//key== ' ' space bar
	//key== 13 enter
	glutPostRedisplay();
}

/*void showText(int x,int y,char text[]){
	glRasterPos2i(x,y);
	for(int n=0;text[n] != '\0';n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[n]);
}*/
//////////////Function Rotate ให้รูปหมด //////////////
void Rotate(int value){
	angle += 5;
	if(angle == 360)angle =0;
	if(play) glutTimerFunc(value,Rotate,value); //สถานนะ play ยังเป็น ture อยู่ก็จะหมุนรูปต่อไป
	glutPostRedisplay();
}

/*void Move(int value){
	tx += speed;
	if(tx == 50 ) speed = -speed ;
	else if(tx == -50) speed = -speed; 
	glutPostRedisplay();
	glutTimerFunc(value,Move,value);
}*/