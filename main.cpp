/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "RGBpixmap.cpp"
using namespace std;

float degree=0,degree1=0,degree2=0;
static int slices = 16;
static int stacks = 16;
float ss1 = .2,ss2=.2,ss3=.2;
float ex=0,ey=0,ez=15,cx=0,cy=8,cz=-5,hx=0,hy=1,hz=0;
float tt1=-1.2,tt2=-1.4,tt3=-7;
float choice=0;
float x_rot=0,y_rot=0,z_rot=0;
float rpy=0,rad=15;
float n1=-1.2,n2=-1.4,n3=-7;
float tx1=0,tx2=0,tx3=0,resX,resY,resZ;
float a,b,ar,frus=1;
float fa=0,fb=0,fc=0;
RGBpixmap pix[10];
float h,w;

const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat light_ambient1[]  = { 0.0f, 0.0f, 1.0f, 1.0f };
const GLfloat light_diffuse1[]  = { 0.0f, 0.0f, 1.0f, 1.0f };
const GLfloat light_specular1[] = { 0.0f, 0.0f, 1.0f, 1.0f };
const GLfloat light_position1[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.0f, 0.0f, 1.0f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.0f, 0.0f, 1.0f, 1.0f };
const GLfloat mat_specular[]   = { 0.0f, 0.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

const GLfloat mat_ambient_red[]    = { 1.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse_red[]    = { 1.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_specular_red[]   = { 1.0f, 0.0f, 0.0f, 1.0f };
const GLfloat high_shininess_red[] = { 100.0f };

const GLfloat mat_ambient_green[]    = { 0.0f, 1.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse_green[]    = { 0.0f, 1.0f, 0.0f, 1.0f };
const GLfloat mat_specular_green[]   = { .0f, 1.0f, 0.0f, 1.0f };
const GLfloat high_shininess_green[] = { 100.0f };

const GLfloat mat_ambient1[]    = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse1[]    = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat mat_specular1[]   = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat high_shininess1[] = { 100.0f };

const GLfloat mat_ambient2[]    = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse2[]    = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_specular2[]   = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat high_shininess2[] = { 100.0f };

const GLfloat mat_ambient_w[]    = { 0.9f, 0.6f, 1.0f, 1.0f };
const GLfloat mat_diffuse_w[]    = { 0.7f, 0.7f, 0.8f, 1.0f };
const GLfloat mat_specular_w[]   = { 0.7f, 0.9f, 0.9f, 1.0f };
const GLfloat high_shininess_w[] = { 100.0f };

const GLfloat mat_ambient_w1[]    = { 0.7f, 1.0f, 1.0f, 1.0f };
const GLfloat mat_diffuse_w1[]    = { 0.7f, 0.7f, 0.8f, 1.0f };
const GLfloat mat_specular_w1[]   = { 0.8f, 0.9f, 0.9f, 1.0f };
const GLfloat high_shininess_w1[] = { 100.0f };

//spot light
const GLfloat light_pos[] = { 10.0f, 5.0f, -10.0f, 1.0f };
const GLfloat light_dir[]= {0.0f, 0.0f, -25.0f, 1.0f};
const GLfloat light_r[]={10.0f};
//spot light


/* GLUT callback Handlers */

static void resize(int width, int height)
{
    ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    h=height;w=width;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

//koch curve
GLfloat xComplexMin = -0.25, xComplexMax = 1.25;
GLfloat yComplexMin = -0.75, yComplexMax = 0.75;

GLfloat oldx = -0.7, oldy = 0.5;
GLfloat lftx = oldx - 0.1, lfty = oldy - 0.1;
GLfloat rhtx = oldx + 0.1, rhty = oldy + 0.1;

double Depth=5;

void drawkoch(GLfloat dir, GLfloat len, GLint iter)
{
    GLdouble dirRad = 0.0174533 * dir;
    GLfloat newX = oldx + len * cos(dirRad);
    GLfloat newY = oldy + len * sin(dirRad);


    lftx = (newX - 0.1)<lftx ? newX - 0.1 : lftx;
    lfty = (newY - 0.1)<lfty ? newY - 0.1 : lfty;
    rhtx = (newX + 0.1)>rhtx? newX + 0.1:rhtx;
    rhty = (newY + 0.1)>rhty ? newY + 0.1 : rhty;


    if (iter == 0) {
        glVertex2f(oldx, oldy);
        glVertex2f(newX, newY);
        oldx = newX;
        oldy = newY;
    }
    else {
        iter--;


        drawkoch(dir, len, iter);
        dir += 60.0;
        drawkoch(dir, len, iter);
        dir -= 120.0;
        drawkoch(dir, len, iter);
        dir += 60.0;
        drawkoch(dir, len, iter);
    }
}
//
//
//
void KochCurve(int depth) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);


    drawkoch(0.0, 0.05, depth);
    drawkoch(+72.0, 0.05, depth);
    drawkoch(+144.0, 0.05, depth);
    drawkoch(216.0, 0.05, depth);
    drawkoch(288.0, 0.05, depth);

    glEnd();
    glFlush();
}
//koch curve


//new work
void tex_cube()
{
    glBegin(GL_QUADS);

        glTexCoord2f(0,0);
        glVertex2d(0,0);
        glTexCoord2f(1,0);
        glVertex2d(1,0);
        glTexCoord2f(1,1);
        glVertex2d(1, 1);
        glTexCoord2f(0,1);
        glVertex2d(0,1);
    glEnd();
}

//new work

void cube_texture()
{
          glPushMatrix();
          glTranslated(0,0,0);
          glScaled(2,2,2);
          tex_cube();
          glPopMatrix();


          glPushMatrix();
          glTranslated(2,0,0);
          glRotated(90,0,1,0);
          glScaled(2,2,2);
          tex_cube();
          glPopMatrix();


          glPushMatrix();
          glTranslated(0,0,-2);
          glRotated(270,0,1,0);
          glScaled(2,2,2);
          tex_cube();
          glPopMatrix();

          glPushMatrix();
          glTranslated(2,0,-2);
          glRotated(180,0,1,0);
          glScaled(2,2,2);
          tex_cube();
          glPopMatrix();

          glPushMatrix();
          glTranslated(0,2,0);
          glRotated(-90,1,0,0);
          glScaled(2,2,2);
          tex_cube();
          glPopMatrix();

          glPushMatrix();
          glTranslated(0,0,-2);
          glRotated(90,1,0,0);
          glScaled(2,2,2);
          tex_cube();
          glPopMatrix();
}
//new work texture cube
void main_car()
{
    glBegin(GL_QUADS);


     glVertex3f(0,0,5);
    glVertex3f(5,0,5);
    glVertex3f(5,5,5);
    glVertex3f(0,5,5);

    glVertex3f(0,0,5);
    glVertex3f(0,5,5);
    glVertex3f(0,5,0);
    glVertex3f(0,0,0);

    glVertex3f(5,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,5,0);
    glVertex3f(5,5,0);

    glVertex3f(5,0,0);
    glVertex3f(5,5,0);
    glVertex3f(5,5,5);
    glVertex3f(5,0,5);

    glVertex3f(0,0,0);
    glVertex3f(5,0,0);
    glVertex3f(5,0,5);
    glVertex3f(0,0,5);

    glVertex3f(0,5,5);
    glVertex3f(5,5,5);
    glVertex3f(5,5,0);
    glVertex3f(0,5,0);

    glEnd();
}
void wheel(int x,int y)
{
   float th;
   glBegin(GL_POLYGON);
   glColor3f(0,0,0);

   for(int i=0;i<360;i++)
   {
       th=i*(3.1416/180);
       glVertex2f(x+1.5*cos(th),y+1.5*sin(th));
   }

   glEnd();

}

void wheelanti(int x,int y)
{
   float th;
   glBegin(GL_POLYGON);
   glColor3f(0,0,0);

   for(int i=359;i>=0;i--)
   {
       th=i*(3.1416/180);
       glVertex2f(x+1.5*cos(th),y+1.5*sin(th));
   }

   glEnd();

}

void main_wheel()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*50.0;
    glPushMatrix();
    glTranslated(0,0,-6.2);
    glRotatef(a,0,0,1);
    glTranslated(0,0,6.2);
    glTranslated(0,0,6.2);
    gluCylinder(gluNewQuadric(),
                1.3,
                1.3,
                1.4,
                slices,
                stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.01,-0.01,-7.6);
    glRotated(a,0,0,1);
    glTranslated(.01,0.01,7.6);
    glTranslated(0,0,7.6);
   // glColor3d(0,1,0);
    wheel(0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.01,-.01,-6.2);
    glRotated(a,0,0,1);
    glTranslated(0.01,0.01,6.2);
    glTranslated(0,0,6.2);
    wheelanti(0,0);
    glPopMatrix();

}
//new work
void Car1()
{

    /* 1st cube */

    glPushMatrix();
    glScaled(3,.6,1.4);

        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
        glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
   // glColor3d(1,0.3,0);
    main_car();
    glPopMatrix();

    /* 2nd cube */

    glPushMatrix();
    //glColor3d(1,0.8,0);
     glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glTranslated(4,3,.3);
    glScaled(1.2,.6,1.28);
    main_car();
    glPopMatrix();



    /* 3rd cube */

    glPushMatrix();
   // glColor3d(0,1,1);
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_red);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_red);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_red);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glTranslated(10,3,.5);
    glScaled(.08,.56,1.2);
    main_car();
    glPopMatrix();


    /* 4th cube */

    glPushMatrix();
  //  glColor3d(0,1,1);
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_red);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_red);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_red);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glTranslated(3.6,3,.5);
    glScaled(.08,.56,1.2);
    main_car();
    glPopMatrix();

    /* 5th cube */

    glPushMatrix();
    // glColor3d(0,1,1);
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_red);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_red);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_red);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glTranslated(4.5,3,6.7);
    glScaled(1,.56,.06);
    main_car();
    glPopMatrix();

    /* 6th cube */

    glPushMatrix();
   // glColor3d(0,1,1);
      glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_red);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_red);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_red);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glTranslated(4.5,3,0);
    glScaled(1,.56,.06);
    main_car();
    glPopMatrix();

    /* 7th cube */
    glPushMatrix();
   // glColor3d(0,0,0);
    glTranslated(15,0,.3);
    glScaled(.08,.1,1.28);
    main_car();
    glPopMatrix();

    /* 8th cube */
    glPushMatrix();
    //glColor3d(0,0,0);
    glTranslated(-.6,0,.3);
    glScaled(.12,.1,1.28);
    main_car();
    glPopMatrix();

    /* 9th cube */

    glPushMatrix();
   // glColor3d(0,0,1);
    glTranslated(-.5,2.5,.3);
    glScaled(.1,.05,1.28);
    main_car();
    glPopMatrix();


    /* Head Light rightside */

    glPushMatrix();
  //  glColor3d(1,1,0);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_w);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_w);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_w);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_w);
    glTranslated(15,2,6);
    glutSolidSphere(.6,slices,stacks);
    glPopMatrix();

    /* Head Light leftside */

    glPushMatrix();
  //  glColor3d(1,1,0);
    glTranslated(15,2,1);
    glutSolidSphere(0.6,slices,stacks);
    glPopMatrix();

    /* 1st wheel */
    glPushMatrix();
  //  glColor3d(0,0,0);
    glTranslated(3.3,0,0);
    main_wheel();
    glPopMatrix();


    /* 2nd wheel */

    glPushMatrix();

 //   glColor3d(0,0,0);
    glTranslated(3.3,0,-6.9);
    main_wheel();
    glPopMatrix();

    /* 3rd wheel */

    glPushMatrix();
 //   glColor3d(0,0,0);
    glTranslated(11,0,0);
    main_wheel();
    glPopMatrix();



    /* 4th wheel */

    glPushMatrix();
 //   glColor3d(0,0,0);
    glTranslated(11,0,-6.9);
    main_wheel();
    glPopMatrix();



}

void table1()
{
    //table upper portion
    glPushMatrix();
    glTranslated(-15,5,-90);
    glScaled(12.5,.15,10);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient1);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse1);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular1);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess1);
    main_car();
    glPopMatrix();
    //back left leg
    glPushMatrix();
    glTranslated(-15,5,-90);
    glScaled(.15,-6.75,.15);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient2);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse2);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular2);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess2);
    main_car();
    glPopMatrix();
        //front left leg
    glPushMatrix();
    glTranslated(-15,5,-40);
    glScaled(.15,-6.75,.15);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient2);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse2);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular2);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess2);
    main_car();
    glPopMatrix();
           //front right leg
    glPushMatrix();
    glTranslated(46.75,5,-40);
    glScaled(.15,-6.75,.15);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient2);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse2);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular2);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess2);
    main_car();
    glPopMatrix();
               //back right leg
    glPushMatrix();
    glTranslated(46.5,5,-90);
    glScaled(.15,-6.75,.15);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient2);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse2);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular2);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess2);
    main_car();
    glPopMatrix();
}
void Jack1(){

    glPushMatrix(); //Jack
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_w);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_w);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular_w);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess_w);
    glScaled(1,7,1);
    glutSolidSphere(1,50,50);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_w1);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_w1);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular_w1);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess_w1);
    glTranslated(0,7,0);
    glScaled(2.5,2.5,2.5);
    glutSolidSphere(1,50,50);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_w1);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_w1);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular_w1);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess_w1);
        glTranslated(0,-7,0);
        glScaled(2.5,2.5,2.5);
        glutSolidSphere(1,50,50);
    glPopMatrix();

}

void House1()
{
    //floor
    glPushMatrix();
    glTranslated(-50,-30,-190);
    glScaled(25.5,.15,30);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
    main_car();
    glPopMatrix();
//back wall
    glPushMatrix();
    glTranslated(-50,-29.25,-190);
    glScaled(25.5,30,.15);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_red);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_red);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular_red);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess_red);
    main_car();
    glPopMatrix();
    //left wall
    glPushMatrix();
    glTranslated(-50,-29.25,-190);
    glScaled(.15,30,30);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_green);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_green);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular_green);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess_green);
    main_car();
    glPopMatrix();

    //table
    glTranslated(0,0,-20);
    table1();

    //jack
    glTranslated(-5,15,-50);
    Jack1();
    //glTranslated(-5,15,-50);
    glRotated(45,0,0,1);
    Jack1();
    glRotated(90,0,0,1);
    Jack1();

    //car
    glRotated(220,0,0,1);
    glTranslated(20,-5.5,0);
    Car1();

}
//new work
void Car()
{

    /* 1st cube */

    glPushMatrix();
    glScaled(3,.6,1.4);

    glBindTexture(GL_TEXTURE_2D,5);
    glEnable(GL_TEXTURE_2D);
   // glColor3d(1,0.3,0);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /* 2nd cube */

    glPushMatrix();
    //glColor3d(1,0.8,0);
    glBindTexture(GL_TEXTURE_2D,6);
    glEnable(GL_TEXTURE_2D);
    glTranslated(4,3,.3);
    glScaled(1.2,.6,1.28);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    /* 3rd cube */

    glPushMatrix();
   // glColor3d(0,1,1);
    glBindTexture(GL_TEXTURE_2D,6);
    glEnable(GL_TEXTURE_2D);
    glTranslated(10,3,.5);
    glScaled(.08,.56,1.2);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    /* 4th cube */

    glPushMatrix();
  //  glColor3d(0,1,1);
    glBindTexture(GL_TEXTURE_2D,7);
    glEnable(GL_TEXTURE_2D);
    glTranslated(3.6,3,.5);
    glScaled(.08,.56,1.2);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /* 5th cube */

    glPushMatrix();
    // glColor3d(0,1,1);
    glBindTexture(GL_TEXTURE_2D,7);
    glEnable(GL_TEXTURE_2D);
    glTranslated(4.5,3,6.7);
    glScaled(1,.56,.06);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /* 6th cube */

    glPushMatrix();
   // glColor3d(0,1,1);
    glBindTexture(GL_TEXTURE_2D,7);
    glEnable(GL_TEXTURE_2D);
    glTranslated(4.5,3,0);
    glScaled(1,.56,.06);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /* 7th cube */
    glPushMatrix();
   // glColor3d(0,0,0);
    glTranslated(15,0,.3);
    glScaled(.08,.1,1.28);
    main_car();
    glPopMatrix();

    /* 8th cube */
    glPushMatrix();
    //glColor3d(0,0,0);
    glTranslated(-.6,0,.3);
    glScaled(.12,.1,1.28);
    main_car();
    glPopMatrix();

    /* 9th cube */

    glPushMatrix();
   // glColor3d(0,0,1);
    glTranslated(-.5,2.5,.3);
    glScaled(.1,.05,1.28);
    main_car();
    glPopMatrix();


    /* Head Light rightside */

    glPushMatrix();
  //  glColor3d(1,1,0);
    glBindTexture(GL_TEXTURE_2D,5);
    glEnable(GL_TEXTURE_2D);
    glTranslated(15,2,6);
    glutSolidSphere(.6,slices,stacks);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /* Head Light leftside */

    glPushMatrix();
  //  glColor3d(1,1,0);
    glTranslated(15,2,1);
    glutSolidSphere(0.6,slices,stacks);
    glPopMatrix();

    /* 1st wheel */
    glPushMatrix();
  //  glColor3d(0,0,0);
    glTranslated(3.3,0,0);
    glBindTexture(GL_TEXTURE_2D,6);
    glEnable(GL_TEXTURE_2D);
    main_wheel();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    /* 2nd wheel */

    glPushMatrix();

 //   glColor3d(0,0,0);
    glTranslated(3.3,0,-6.9);
    glBindTexture(GL_TEXTURE_2D,6);
    glEnable(GL_TEXTURE_2D);
    main_wheel();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /* 3rd wheel */

    glPushMatrix();
 //   glColor3d(0,0,0);
    glTranslated(11,0,0);
    glBindTexture(GL_TEXTURE_2D,6);
    glEnable(GL_TEXTURE_2D);
    main_wheel();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    /* 4th wheel */

    glPushMatrix();
 //   glColor3d(0,0,0);
    glTranslated(11,0,-6.9);
    glBindTexture(GL_TEXTURE_2D,6);
    glEnable(GL_TEXTURE_2D);
    main_wheel();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



}

void table()
{
    //table upper portion
    glPushMatrix();
    //glRotated(-90,0,0,1);
    glBindTexture(GL_TEXTURE_2D,3);
    glEnable(GL_TEXTURE_2D);
    glTranslated(-15,5,-90);
    glRotated(90,1,0,0);
    glScaled(12.5,10,.15);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //back left leg
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,3);
    glEnable(GL_TEXTURE_2D);
    glTranslated(-15,5,-90);
    glScaled(.15,-6.75,.15);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
        //front left leg
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,3);
    glEnable(GL_TEXTURE_2D);
    glTranslated(-15,5,-40);
    glScaled(.15,-6.75,.15);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
           //front right leg
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,3);
    glEnable(GL_TEXTURE_2D);
    glTranslated(46.75,5,-40);
    glScaled(.15,-6.75,.15);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
               //back right leg
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,3);
    glEnable(GL_TEXTURE_2D);
    glTranslated(46.5,5,-90);
    glScaled(.15,-6.75,.15);
    main_car();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void Jack(){

    glPushMatrix(); //Jack
    glBindTexture(GL_TEXTURE_2D,4);
    glEnable(GL_TEXTURE_2D);
    glScaled(1,7,1);
    glutSolidSphere(1,50,50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,4);
    glEnable(GL_TEXTURE_2D);
    glTranslated(0,7,0);
    glScaled(2.5,2.5,2.5);
    glutSolidSphere(1,50,50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,4);
    glEnable(GL_TEXTURE_2D);
    glTranslated(0,-7,0);
    glScaled(2.5,2.5,2.5);
    glutSolidSphere(1,50,50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void House()
{
    //floor

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,2);
    glEnable(GL_TEXTURE_2D);
    glTranslated(-50,-30,-190);
    glRotated(450,1,0,0);
    glScaled(100,70,.15);
    cube_texture();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //floor

//back wall
    glPushMatrix();
    glTranslated(-50,-30,-190);
    glScaled(100,100,.15);
    glBindTexture(GL_TEXTURE_2D,8);
    glEnable(GL_TEXTURE_2D);
    cube_texture();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //picture
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,7);
    glEnable(GL_TEXTURE_2D);
    glTranslated(20,70,-189);
    glScaled(50,50,0);
    tex_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //picture

    //left wall
    glPushMatrix();
    glTranslated(-50,-30,-190);
    glRotated(-90,0,1,0);
    glScaled(70,100,.15);
    glBindTexture(GL_TEXTURE_2D,8);
    glEnable(GL_TEXTURE_2D);
    cube_texture();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //table
    glTranslated(0,0,-20);
    table();

    //jack
    glTranslated(-5,15,-50);
    Jack();
    //glTranslated(-5,15,-50);
    glRotated(45,0,0,1);
    Jack();
    glRotated(90,0,0,1);
    Jack();

    //car
    glRotated(220,0,0,1);
    glTranslated(20,-5.5,0);

    glTranslated(-3.5,2.5,0);
    glScaled(2.5,2.5,1);
    Car();

}

//homework pitch,roll,yaw
void my_rotation(GLdouble x, GLdouble y, GLdouble z)
{
    GLfloat m[16];

    m[0] = cos(z)*cos(y);m[4] = cos(z)*sin(y)*sin(x)-sin(z)*cos(x);m[8] = cos(z)*sin(y)*cos(x)+sin(z)*sin(x);m[12] = 0;
    m[1] = sin(z)*cos(y);m[5] = sin(z)*sin(y)*sin(x)+cos(z)*cos(x);m[9] = sin(z)*sin(y)*cos(x)-cos(z)*sin(x);m[13] = 0;
    m[2] = -sin(y);      m[6] = cos(y)*sin(x);                     m[10] = cos(y)*cos(x);                    m[14] = 0;
    m[3] = 0;            m[7] = 0;                                 m[11] = 0;                                m[15] = 1;

    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(m);
}
//homework pitch,roll,yaw

//My new work lab 02
void my_new_scaleFunction(GLfloat sx, GLfloat sy, GLfloat sz){
GLfloat scalemat[16];
scalemat[0] =sx; scalemat[4] = 0; scalemat[8] = 0; scalemat[12] = 0;
scalemat[1] = 0; scalemat[5] =sy; scalemat[9] = 0; scalemat[13] = 0;
scalemat[2] = 0; scalemat[6] = 0; scalemat[10] =sz; scalemat[14] = 0;
scalemat[3] = 0; scalemat[7] = 0; scalemat[11] = 0; scalemat[15] = 1;
glMatrixMode(GL_MODELVIEW);
glMultMatrixf(scalemat);
}


static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*100000.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);


    glViewport(0, 0, w/2, h);
    glPushMatrix();

    //glTranslatef(tt1,tt2,tt3);
    glRotated(degree,0,0,1);
    glRotated(degree1,0,1,0);
    glRotated(degree2,1,0,0);
    //pitch_roll_yaw
    //my_new_pitch_roll_yaw(x_rot,y_rot,z_rot);
    //pitch_roll_yaw
    glScalef(ss1,ss2,ss3);
    glRotated(20,1,0,0);
    glScaled(1.5,.70,2);
    //glTranslated(0,15,0);
    tt1=0;tt2=0;tt3=0;
    //koch curve
    glPushMatrix();
    glTranslated(-5,42,0);
    glTranslated(fx,fy,fz);
    glScaled(.35,.35,.35);
    KochCurve(Depth);
    glPopMatrix();
    //koch curve
    House();
    glPopMatrix();

    glViewport(w/2, 0, w/2, h);
    glPushMatrix();

    //glTranslatef(tt1,tt2,tt3);
    glRotated(degree,0,0,1);
    glRotated(degree1,0,1,0);
    glRotated(degree2,1,0,0);
    //pitch_roll_yaw
    //my_new_pitch_roll_yaw(x_rot,y_rot,z_rot);
    //pitch_roll_yaw
    glScalef(ss1,ss2,ss3);
    glRotated(20,1,0,0);
    glScaled(1.5,.70,2);
    //glTranslated(0,15,0);
    tt1=0;tt2=0;tt3=0;
    House1();
    glPopMatrix();
    //Cube();
    //For back wheel on front side
    /*
    */
    //New Lab_work
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(ex,ey,ez,cx,cy,cz,hx,hy,hz);
    //New_lab_work_02
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'z':
        degree=0;
        degree1=0;
        degree2=0;
        choice=1;
        break;
    case 'y':
        degree=0;
        degree1=0;
        degree2=0;
        choice=2;
        break;
    case 'x':
        degree=0;
        degree1=0;
        degree2=0;
        choice=3;
        break;
    case 'e':
        choice=4;
        break;
    case 'h':
        choice=5;
        break;
    case 'c':
        choice=6;
        break;
    case 't':
        choice=7;
        break;
    case 's':
        choice=8;
        break;
    case 'r':
        choice=9;
        break;
    case 'p':
        choice=10;
        break;
    case 'w':
        choice=11;
        break;
    case '.':
        choice=12;
        break;
    case '!':
        choice=13;
        break;
    case '@':
        choice=100;
        break;
    }
    if(choice==100)
    {
        switch(key)
        {
        case'+':
                ar+=.1;
                frus+=.1;

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glFrustum(-ar, ar, -frus, frus, 2.0, 100.0);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity() ;
                break;
        case'-':
                ar-=.1;
                frus-=.1;

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glFrustum(-ar, ar, -frus, frus, 2.0, 100.0);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity() ;
                break;
        }
    }
    if(choice==11)
    {
        switch(key)
        {
        case '+':
            Depth++;
            break;
        case '-':
            Depth--;
            break;
        }
    }

    if(choice==13)
    {
        switch(key)
        {
        case 'o':
            glEnable(GL_LIGHT0);
            break;
        case 'f':
            glDisable(GL_LIGHT0);
            break;
        case 'b':
            glEnable(GL_LIGHT1);
            break;
        case 'n':
            glDisable(GL_LIGHT1);
            break;
        }
    }

    if(choice==12)
    {
        switch(key)
        {
        case '1':
            choice=13;
            //ey=0;
            //ez=0;
            ex=0;
            rpy=0;
            break;
        case '2':
            choice=14;
            ey=0;
            //ez=0;
            //ex=0;
            rpy=0;
            break;
        case '3':
            choice=15;
            //ey=0;
            ez=-2;
            //ex=0;
            rpy=0;
            break;
        }
    }
    //roll
    if(choice==13)
    {
        switch(key)
        {
        case '+':
            rpy++;
            glTranslated(-n1,-n2,-n3);
            ey = rad * cos(((3.1416)*rpy)/180.0);
            ez = rad * sin(((3.1416)*rpy)/180.0);
            glTranslated(n1,n2,n3);
            break;
        case '-':
            rpy--;
            glTranslated(-n1,-n2,-n3);
            ey = rad * cos(((3.1416)*rpy)/180.0);
            ez = rad * sin(((3.1416)*rpy)/180.0);
            glTranslated(n1,n2,n3);
            break;
        }
    }
    //roll end
    //pitch
    if(choice==14)
    {
        switch(key)
        {
        case '+':
            rpy++;

            glTranslated(-n1,-n2,-n3);
            ex = rad * cos(((3.1416)*rpy)/180.0);
            ez = rad * sin(((3.1416)*rpy)/180.0);
            glTranslated(n1,n2,n3);
            break;
        case '-':
            rpy--;
            glTranslated(-n1,-n2,-n3);
            ex = rad * cos(((3.1416)*rpy)/180.0);
            ez = rad * sin(((3.1416)*rpy)/180.0);
            glTranslated(n1,n2,n3);
            break;
        }
    }

    //pitch end
    //yaw
    if(choice==15)
    {
        switch(key)
        {
        case '+':
            rpy++;
            glTranslated(n1,n2,n3);
            ex = rad * cos(((3.1416)*rpy)/180.0);
            ey = rad * sin(((3.1416)*rpy)/180.0);
            glTranslated(-n1,-n2,-n3);
            break;
        case '-':
            rpy--;
            glTranslated(n1,n2,n3);
            ex = rad * cos(((3.1416)*rpy)/180.0);
            ey = rad * sin(((3.1416)*rpy)/180.0);
            glTranslated(-n1,-n2,-n3);
            break;
        }
    }
    //yaw end


   //roll
    if(choice==9)
    {
        switch(key)
        {
        case '+'://yaw
            a=cx-ex;
            b=cz-ez;
            resX=a*cos(.1)+b*sin(.1) ;
            resZ=b*cos(.1)-a*sin(.1);
            cx=resX+ex;
            cz=resZ+ez;
            break;
        case'-'://yaw
            a=cx-ex;
            b=cz-ez;
            resX=a*cos(.1)-b*sin(.1) ;
            resZ=b*cos(.1)+a*sin(.1);
            cx=resX+ex;
            cz=resZ+ez;
            break;
        case'#'://pitch
            hx=hx*cos(.1)+hy*sin(.1) ;
            hy=hy*cos(.1)-hx*sin(.1);
            break;
        case'$'://pitch
            hx=hx*cos(.1)-hy*sin(.1) ;
            hy=hy*cos(.1)+hx*sin(.1);
            break;
        case'%'://roll
            a=cy-ey;
            b=cz-ez;
            resY=a*cos(.1)-b*sin(.1) ;
            resZ=b*cos(.1)+a*sin(.1);
            cy=resY+ey;
            cz=resZ+ez;
            break;
        case'^'://roll
            a=cy-ey;
            b=cz-ez;
            resY=a*cos(.1)+b*sin(.1) ;
            resZ=b*cos(.1)-a*sin(.1);
            cy=resY+ey;
            cz=resZ+ez;
            break;


        }
    }/*
    //roll end

    //pitch
    if(choice==10)
    {
        switch(key)
        {
        case '+':
            y_rot+=.5;
            break;
        case '-':
            y_rot-=.5;
            break;
        }
    }
    //pitch end


     //yaw
    if(choice==10)
    {
        switch(key)
        {
        case '+':
            z_rot+=.5;
            break;
        case '-':
            z_rot-=.5;
            break;
        }
    }
    //yaw end

*/




    //translate
    if(choice==7)
    {
        switch(key)
        {
        case '+':
            tt1+=.5;
            break;
        case '-':
            tt2+=.5;
            break;
        case ')':
            tt3+=.5;
            break;
        case '?':
            tt1-=.5;
            break;
        case '>':
            tt2-=.5;
            break;
        case '<':
            tt3-=.5;
            break;
        }
    }
    //translate end
    //scaling
    if(choice==8)
    {
        switch(key)
        {
        case '+':
            ss1+=.01;
            break;
        case '-':
            ss2+=.01;
            break;
        case ')':
            ss3+=.01;
            break;
        case '?':
            ss1-=.01;
            break;
        case '>':
            ss2-=.01;
            break;
        case '<':
            ss3-=.01;
            break;
        }
    }
    //scaling end
    //x-direction rotation
    if(choice==1)
    {
        switch(key)
        {
        case '+':
            degree+=.8;
            break;
        case '-':
            degree-=.8;
            break;
        }
    }
    //x-direction rotation end
    //y-direction rotation
    if(choice==2)
    {
        switch(key)
        {
        case '+':
            degree1+=.8;
            break;
        case '-':
            degree1-=.8;
            break;
        }
    }
    //y-direction rotation end
    //z-direction rotation

    if(choice==3)
    {
        switch(key)
        {
        case '+':
            degree2+=.8;
            break;
        case '-':
            degree2-=.8;
            break;
        }
    }
    //z-direction rotation end
    //eye-direction rotation
    if(choice==4)
    {
        switch(key)
        {
        case '+':
            ex+=.5;
            break;
        case '-':
            ey+=.5;
            break;
        case ')':
            ez+=.5;
            break;
        case '?':
            ex-=.5;
            break;
        case '>':
            ey-=.5;
            break;
        case '<':
            ez-=.5;
            break;
        }
    }
    //eye-direction rotation end
    //head-direction rotation
    if(choice==5)
    {
        switch(key)
        {
        case '+':
            hx+=.5;
            break;
        case '-':
            hy+=.5;
            break;
        case ')':
            hz+=.5;
            break;
        case '?':
            hx-=.5;
            break;
        case '>':
            hy-=.5;
            break;
        case '<':
            hz-=.5;
            break;
        }
    }
    //head-direction rotation end
    //camera-direction rotation
    if(choice==6)
    {
        switch(key)
        {
        case '+':
            cx+=.5;
            break;
        case '-':
            cy+=.5;
            break;
        case ')':
            cz+=.5;
            break;
        case '?':
            cx-=.5;
            break;
        case '>':
            cy-=.5;
            break;
        case '<':
            cz-=.5;
            break;
        }
    }
    //camera-direction rotation end
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}


static void idle(void)
{
    glutPostRedisplay();
}



/* Program entry point */

void Init()
{
	glEnable(GL_TEXTURE_2D);


    pix[0].makeCheckImage();
	pix[0].setTexture(1);

	pix[1].readBMPFile("N:\\4th Year 2nd Semister\\Graphics lab\\Project Texture\\real_floor.bmp");
	pix[1].setTexture(2);

	pix[2].readBMPFile("N:\\4th Year 2nd Semister\\Graphics lab\\Project Texture\\table6.bmp");
	pix[2].setTexture(3);

	pix[3].readBMPFile("N:\\4th Year 2nd Semister\\Graphics lab\\Project Texture\\teapot.bmp");
	pix[3].setTexture(4);

    pix[4].readBMPFile("N:\\4th Year 2nd Semister\\Graphics lab\\Project Texture\\red.bmp");
	pix[4].setTexture(5);

    pix[5].readBMPFile("N:\\4th Year 2nd Semister\\Graphics lab\\Project Texture\\gr.bmp");
	pix[5].setTexture(6);

	pix[6].readBMPFile("N:\\4th Year 2nd Semister\\Graphics lab\\Project Texture\\deyal.bmp");
	pix[6].setTexture(7);

	pix[7].readBMPFile("N:\\4th Year 2nd Semister\\Graphics lab\\Project Texture\\brick1.bmp");
	pix[7].setTexture(8);
/*
    pix[4].readBMPFile("C:\\Users\\Shauqi\\Google Drive\\CSE KUET\\Even Semesters\\CSE 4208 Computer Graphics Laboratory\\lab4 texturing\\cone.bmp");
	pix[4].setTexture(5);*/



}

int main(int argc, char *argv[])
{
    cout<<"'x' to rotate x-direction\n'y' to rotate y-direction\n'z' to rotate z-direction\n'e' to rotate eye-direction\n'h' to rotate head-direction\n'c' to rotate camera-direction\n'.' to rotate yaw_roll_pitch-direction\n's' to scaling\n't' to rotate translate\n"<<endl;
    cout<<"'r' to roll"<<endl;
    glutInit(&argc, argv);
    glutInitWindowSize(1340,780);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Nirob's World");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0,0,0,0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    //glLightfv(GL_LIGHT1, GL_POSITION, light_position);

    //spot light
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, light_r);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, .2);
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    //spot light

    Init();
    glutMainLoop();

    return EXIT_SUCCESS;
}




/*
void two_D_cube()
{
    glBegin(GL_QUADS);


    glVertex3f(0,0,0);
    glVertex3f(5,0,0);
    glVertex3f(5,5,0);
    glVertex3f(0,5,0);

    glEnd();
}
*/
