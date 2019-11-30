#include <stdio.h>
#include <math.h>
#include <windows.h>

#include <GL/glut.h>

#include "RGBpixmap.cpp"


#define PI 3.1415926535897932384626433832795
#define MaximumTheta 1.0
#define MinimumTheta 0.0009
#define MaximumRadious 10.5
#define MinimumRadious .9


//DATATYPE DECLERATION
GLfloat IncrementTheta = 0.05;
GLint WindowSizX=640,WindowSizY=480;
GLfloat EyePosition_X=2.0,EyePosition_Y=1.3,EyePosition_Z= 2.0;
GLfloat Radious=3.3,ProRadious=3.0,InitialTheta1=0.716,InitialTheta2=0.403;
GLfloat Center_X=0.0,Center_Y=0.0,Center_Z=0.0;
GLfloat Up_X=0.0,Up_Y=1.0,Up_Z=0.0;
enum { ClockWise,AntiClockWise };
enum {Theta1,Theta2};
float Near=.05, Far=10.0,fova = 50.0;
GLint direction = AntiClockWise;
GLint PressMovenent=Theta1;

RGBpixmap pix[6];

//FUNCTION DECLEARATION
void CalculationX_Y_Z();
void CalculationTH1();
void CalculationTH2();
void Movenent();



void tableLeg(double thick, double len)

{

	glPushMatrix();

    glTranslated(0, len/2, 0);
    glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}

void jackPart()
{
	glPushMatrix();
	glScaled(0.2, 0.2, 1.0);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();
    glPushMatrix();
	glTranslated(0, 0, 1.2);
	glutSolidSphere(0.2, 15, 15);
	glTranslated(0, 0, -2.4);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();
}

void jack()
{

	glPushMatrix();
	//jackPart();
	glRotated(45, 0, 1, 0);
	jackPart();
	glRotated(90, 1, 0, 0);
	jackPart();
	glRotated(90, 0, 1, 0);
	jackPart();

	glPopMatrix();
}

void table(double topWidth, double topThick, double legThick, double legLen)
{

	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWidth, topThick, topWidth);
	glutSolidCube(1.0);
	glPopMatrix();

	double dist = 0.95 * topWidth/2.0 - legThick/2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2*dist);
	tableLeg(legThick, legLen);
	glTranslated(-2*dist, 0, 2*dist);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2*dist);
	tableLeg(legThick, legLen);
	glPopMatrix();
}



void displaySolid(void)
{

	GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat mat_defused[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[] = {50.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_defused);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	//GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
//	GLfloat lightPosition[] = {2.0f, 6.0f, 3.0f, 0.0f};


//	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);


	glViewport(0, 0, WindowSizX,WindowSizY );


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspectR = (float)WindowSizX / WindowSizY;


	gluPerspective(fova,aspectR, Near, Far);

	glMatrixMode(GL_MODELVIEW);/////
	glLoadIdentity();//////



	gluLookAt(EyePosition_X,EyePosition_Y,EyePosition_Z,Center_X,Center_Y,Center_Z,Up_X,Up_Y,Up_Z);

	//start drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,3);
	//This function enables you to create or switch to a named texture state.
	// On first use, this function creates a new texture state
	//identified by the texture name, which is an unsigned integer.
	//Subsequent calls with the same texture identifier select that texture state and make it current.
	//parameters:
	//P1: GLenum: The texture target to bind to.
		//It must be GL_TEXTURE_1D, GL_TEXTURE_2D, or GL_TEXTURE_3D.

	//P2: GLuint: The name or handle of the texture object.



	glEnable(GL_TEXTURE_2D);
	glTranslated(0.4, 0.38, 0.6);
	glRotated(55, 0, 0, 1);
	glScaled(0.08, 0.08, 0.08);
	jack();
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,2);
	glEnable(GL_TEXTURE_2D);

	glTranslated(0.6, 0.37, 0.5);
	glRotated(30, 0, 1, 0);
	glutSolidTeapot(0.08);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslated(0.25, 0.40, 0.35);
	glutSolidSphere(0.1, 15, 15);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
    glTranslated(0.4, 0, 0.4);
	glBindTexture(GL_TEXTURE_2D,4);
	glEnable(GL_TEXTURE_2D);

	table(0.6, 0.02, 0.02, 0.3);
	glDisable(GL_TEXTURE_2D);
	//glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
	glPopMatrix();

    glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,5);
    glEnable(GL_TEXTURE_2D);
	glTranslatef( .55, .30, .25);
	glRotatef(-90,1,0,0);
	glutSolidCone(.1,.4,8,8);
	glPopMatrix();



	glFlush();

	glutSwapBuffers();
}



void RepeatDisplay()
{
	glutPostRedisplay();
}


void Movenent()
{

	CalculationX_Y_Z();

	if(PressMovenent == Theta1)
		CalculationTH1();
	else
		CalculationTH2();

}


void CalculationX_Y_Z()
{

		ProRadious = Radious * cos(InitialTheta2);
		EyePosition_Y = Radious * sin(InitialTheta2);

		EyePosition_X = ProRadious * cos(InitialTheta1);
		EyePosition_Z = ProRadious * sin(InitialTheta1);


		printf("EyePosition_X: %f\n",EyePosition_X);
		printf("EyePosition_Y: %f\n",EyePosition_Y);
		printf("EyePosition_Z: %f\n\n",EyePosition_Z);
}



void CalculationTH1()
{


	if (InitialTheta1 > PI*2)
		InitialTheta1 = 0.0;
	if(direction == AntiClockWise)
	{
	   InitialTheta1 += IncrementTheta;
        printf("InitialTheta1: %f\n",InitialTheta1);
	}
	else
	   InitialTheta1 -= IncrementTheta;
       printf("InitialTheta1: %f\n",InitialTheta1);
}



void CalculationTH2(){


	if (InitialTheta2 > PI*2)
		InitialTheta2 = 0.0;

	if(direction == AntiClockWise)
	{
		InitialTheta2 += IncrementTheta;
        printf("InitialTheta2: %f\n",InitialTheta2);
	}

	else
		InitialTheta2 -= IncrementTheta;
       printf("InitialTheta2: %f\n",InitialTheta2);

}



void CalculationRadious(unsigned int key)
{

	if(key == '-')
	{
	if(Radious > MaximumRadious)
		Radious = MaximumRadious;
	else
		Radious += 0.2;
		printf("Radious: %f\n",Radious);
	}
	else if(key == '+')
	{
	if(Radious <= MinimumRadious)
		Radious = MinimumRadious;
	else
		Radious -= 0.2;
		printf("Radious: %f\n",Radious);
	}

	CalculationX_Y_Z();
}


void KeybordFunction( unsigned char key, int x, int y )
{

    if(key=='-')
        CalculationRadious(key);

	else if(key=='+')
        CalculationRadious(key);

	else if(key == '4')
	{
		direction = ClockWise;
		PressMovenent = Theta1;
		Movenent();
	}

	else if(key == '6')
	{

		direction = AntiClockWise;
		PressMovenent = Theta1;
		Movenent();
	}
	else if(key == '8')
	{

		direction = ClockWise;
		PressMovenent = Theta2;
		Movenent();
	}
	else if(key == '2')
	{

		direction = AntiClockWise;
		PressMovenent = Theta2;
		Movenent();
	}

}



void Init()
{
	glEnable(GL_TEXTURE_2D);


    pix[0].makeCheckImage();
	pix[0].setTexture(1);

	pix[1].readBMPFile("C:\\Users\\Shauqi\\Google Drive\\CSE KUET\\Even Semesters\\CSE 4208 Computer Graphics Laboratory\\lab4 texturing\\teapot.bmp");
	pix[1].setTexture(2);

	pix[2].readBMPFile("C:\\Users\\Shauqi\\Google Drive\\CSE KUET\\Even Semesters\\CSE 4208 Computer Graphics Laboratory\\lab4 texturing\\jack.bmp");
	pix[2].setTexture(3);

	pix[3].readBMPFile("C:\\Users\\Shauqi\\Google Drive\\CSE KUET\\Even Semesters\\CSE 4208 Computer Graphics Laboratory\\lab4 texturing\\table.bmp");
	pix[3].setTexture(4);

    pix[4].readBMPFile("C:\\Users\\Shauqi\\Google Drive\\CSE KUET\\Even Semesters\\CSE 4208 Computer Graphics Laboratory\\lab4 texturing\\cone.bmp");
	pix[4].setTexture(5);



}


int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
	glutInitWindowSize(WindowSizX, WindowSizY);
	glutCreateWindow("Texturing");
	glutKeyboardFunc(KeybordFunction);
	glutIdleFunc(RepeatDisplay);
	glutDisplayFunc(displaySolid);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	Init();
	//glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
	glutMainLoop();

	return 0;
}
