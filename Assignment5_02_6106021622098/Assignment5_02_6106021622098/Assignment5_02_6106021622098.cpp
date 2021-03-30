#include <iostream>
using namespace std;
#include<GL/glut.h>
//////////////Function//////////////
void init (void);
void myDisplay(void);
void mainMenu (int option);
void myKeyboard(GLubyte key,GLint x,GLint y);//functionใช้รับค่าจาก keyboard
//void mySpecial(GLint key,GLint x,GLint y);
//void myMouse(GLint button,GLint action,GLint x,GLint y);
//void showText(int x,int y,char text[]);
void definePerspective();//ย้านกล้องเป็นมุมมอง Perspectiv
void defineFont();//ย้านกล้องเป็นมุมมองด้านหน้า
void defineRight();//ย้านกล้องเป็นมุมมองด้านขวา
void defineLight();//function กำหนดทิศทางของแสง
void animat (int option);
void camara (int option);
void Rotate(int value);//function ที่ทำให้หมุดได้

//////////////ตัวแปร//////////////
bool play=false;//เก็บสถานนะของการเล่น
int angle = 0;//เก็บรัศมี
GLfloat light_color[]={1.0,1.0,1.0,1.0};//สีของแสง

//////////////Main//////////////
void main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Assignment5_2");
	init();
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);//เปิดใช้งาน รับค่าจาก keyboard

	////สร้าง Menu////ต้องสร้าง subMenu ก่อนสร้าง mainMenu
	GLint subMenu1, subMenu2;//ตั้งตัวแปรเก็บ subMenu1
	subMenu1 = glutCreateMenu (animat);//สร้าง submenu แล้วส่งค่าไปที่ animat เมื่อมีการกดคลิก
		glutAddMenuEntry ("Play Animation", 1);
		glutAddMenuEntry ("Stop Animation", 2);
	subMenu2 = glutCreateMenu (camara);//สร้าง submenu แล้วส่งค่าไปที่ camara เมื่อมีการกดคลิก
		glutAddMenuEntry ("Front View", 1);
		glutAddMenuEntry ("Right View", 2);
		glutAddMenuEntry ("Perspective", 3);
	glutCreateMenu(mainMenu);// สร้าง main pop-up menu.
		glutAddSubMenu ("Animation", subMenu1);
		glutAddSubMenu ("Camara View", subMenu2);
		glutAddMenuEntry ("Exit Program", 3);
	glutAttachMenu (GLUT_RIGHT_BUTTON);//แสดง menu ตอนกดคลิกขวา
	//glutAttachMenu (GLUT_MIDDLE_BUTTON);//แสดง menu ตอนกดกลาง Mouse
	////////////////

	glutPostRedisplay();
	glutMainLoop();
}

void init(void){
	glClearColor(1.0,1.0,1.0,0.0);//กำหนดสีหน้าจอ
	defineFont();//กำหนดตำแหน่งให้กล่องเป็นมุมมองด้านหน้าตอนเริ่ม
	defineLight();//กำหนดตำแหน่งแสง
}
/////////////Main menu/////////////
void mainMenu (int option){
	switch (option){
		case 3: exit(0); break; //ออกจากโปรแกรม
	}
	glutPostRedisplay ( );
}
/////////////Supmenu1/////////////
void camara (int option){
	switch (option){
		case 1: defineFont(); break; //ย้านกล้องเป็นมุมมอง ด้านหน้า
		case 2: defineRight(); break; //ย้านกล้องเป็นมุมมอง ขวา
		case 3: definePerspective(); break; //ย้านกล้องเป็นมุมมอง Perspectiv
	}
	glutPostRedisplay ( );
}

/////////////Supmenu2/////////////
void animat (int option){
	switch (option){
		case 1: 
			if(!play){
				play=true;//เปลี่ยนสถานนะให้เล่น
				glutTimerFunc(100,Rotate,100);//เข้าไปทำงาน function ทุก 100 มิลลิวินาที
			} break;
		case 2: play=false; angle=0; break; //เปลี่ยนสถานนะให้เล่น และ ตั้งรัศมีการหมุนให้เหมือนเดิม
	}
	glutPostRedisplay ( );
}
/////////มุมอง Perspective/////////
void definePerspective(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,1,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20,20,20,0,0,0,0,1,0);
	//gluLookAt(GLdouble eyeX,GLdouble eyeY,GLdouble eyeZ,
	//GLdouble centerX,GLdouble centerY,GLdouble centerZ,
	//GLdouble upX,GLdouble upY,GLdouble upZ);
	//สนใจแค่ eyeX,eyeY,eyeZ ก็พอ
}
/////////มุมอง ด้านหน้า/////////
void defineFont(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,1,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,20,0,0,0,0,1,0);
}

/////////มุมอง ด้านขวา/////////
void defineRight(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,1,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20,0,0,0,0,0,0,1,0);
}

/////////Set ตำแหน่งแสง/////////
void defineLight(){
	GLfloat light_position[]={40.0,40.0,40.0,0.0};//ตำแหน่งของแสง
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void myDisplay(void){
	GLfloat no_mat[]={0.0,0.0,0.0,1.0};

	GLfloat G_ambient[]={0,0,0,1.0};
	GLfloat G_diffuse[]={0,0.7,0.7};//กำหนดสี ฟ้าอมเขียว มั้ง ปกติเป็น{0,1,1,} แต่ถ้าเป็น {0,0.7,0.7} จะทำให้มันทึบขึ้น
	GLfloat G_specular[]={0,0,0};

	GLfloat Y_ambient[]={0,0,0,1.0};
	GLfloat Y_diffuse[]={0.6,0.6,0};//กำหนดสี เป็นสีเหลืง
	GLfloat Y_specular[]={0,0,0};

	GLfloat shininess[]={12}; ////กำหนดแสงสะท้อน
	//ใครอยากรู้ว่า ambient,diffuse,specular คืออะไรไปดูเอง
	//http://jerome.jouvie.free.fr/opengl-tutorials/Tutorial14.php

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();//วัสถุหลัก
			glRotatef(angle,0,1,0);//ทำให้วัตถุหมุน(องศา,หมุนตามแกน x,หมุนตามแกน y,หมุนตามแกน z)

			glPushMatrix();//วัสถุย่อยอันที่ 1 (ตัว)
				glScalef( 0.8, 1.2, 0.6);
				glMaterialfv(GL_FRONT,GL_AMBIENT,G_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,G_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,G_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				glutSolidCube(2.5);
			glPopMatrix();//เสร็จสินการสร้างวัสถุย่อยอันที่ 1

			glPushMatrix(); //วัสถุย่อยอันที่ 2 (หัว)
				glTranslatef(0,2.2,0.0);
				glScalef(1,1,0.6);
				glMaterialfv(GL_FRONT,GL_AMBIENT,Y_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,Y_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,Y_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				glutSolidSphere(1.0,20,20);
			glPopMatrix();//เสร็จสินการสร้างวัสถุย่อยอันที่ 2

			glPushMatrix(); //วัสถุย่อยอันที่ 3 (แขนซ้าย)
				glTranslatef(-1.5,0.9,0.0);
				glScalef(3,0.8,0.8);
				glMaterialfv(GL_FRONT,GL_AMBIENT,Y_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,Y_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,Y_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				glutSolidCube(1);
			glPopMatrix();//เสร็จสินการสร้างวัสถุย่อยอันที่ 3

			glPushMatrix();//วัสถุย่อยอันที่ 4 (แขนขวา)
				glTranslatef(1.5,0.9,0.0);
				glScalef(3,0.8,0.8);
				glMaterialfv(GL_FRONT,GL_AMBIENT,Y_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,Y_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,Y_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);;
				glutSolidCube(1);
			glPopMatrix();//เสร็จสินการสร้างวัสถุย่อยอันที่ 4

			glPushMatrix();//วัสถุย่อยอันที่ 5 (ขาซ้าย)
				glTranslatef(-0.5,-2,0.0);
				glScalef(0.6,5,0.6);
				glMaterialfv(GL_FRONT,GL_AMBIENT,Y_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,Y_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,Y_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				glutSolidCube(1);
			glPopMatrix();//เสร็จสินการสร้างวัสถุย่อยอันที่ 5

			glPushMatrix();//วัสถุย่อยอันที่ 6 (ขาขวา)
				glTranslatef(0.5,-2,0.0);
				glScalef(0.6,5,0.6);
				glMaterialfv(GL_FRONT,GL_AMBIENT,Y_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,Y_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,Y_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				glutSolidCube(1);
			glPopMatrix();//เสร็จสินการสร้างวัสถุย่อยอันที่ 6
		glPopMatrix();//เสร็จสินการสร่้างวัสถุหลัก
	glutSwapBuffers();
	glFlush();
}
/////////Function Keyboard/////////
void myKeyboard(GLubyte key,GLint x,GLint y){
	key=toupper(key);
	if(key=='K') glClearColor(0.0,0.0,0.0,0.0); //เปลี่ยนหน้าจอเป็นสีดำ
	else if(key=='W')  glClearColor(1.0,1.0,1.0,0.0); //เปลี่ยนหน้าจอเป็นสีขาว
	//else if(key== 27 ) exit(0); //ออกโปรแกรม
	glutPostRedisplay();
}
/////////Function ควบคุมการหมุน/////////
void Rotate(int value){
	angle += 5;
	if(angle == 360)angle =0;
	if(play) glutTimerFunc(value,Rotate,value); //สถานนะ play ยังเป็น ture อยู่ก็จะหมุนรูปต่อไป
	glutPostRedisplay();
}

