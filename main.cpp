
#include <GL/freeglut.h>
#include <GL/gl.h>
//#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLsizei winWidth=900, winHeight=900;
//GLsizei winWidth=640, winHeight=480;            //set initial display window size
GLfloat	rtri = 180.0f;				// Angle For The Triangle ( NEW )
GLfloat	rquad = 45.0f;			// Angle For The Quad ( NEW )

void init(void) {
  glShadeModel(GL_SMOOTH);				// Enable Smooth Shading
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			// Black Background
  glClearDepth(1.0f);					// Depth Buffer Setup
  glEnable(GL_DEPTH_TEST);				// Enables Depth Testing
  glDepthFunc(GL_LEQUAL);				// The Type Of Depth Testing To Do
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}

void displayFcn(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
  glLoadIdentity();
  glTranslatef(0.0f,0.0f,-700.0f);
  //glRotatef(rquad,0.0f,1.0f,0.0f);			// Rotate The Triangle On The Y axis ( NEW )
  gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); // Camara mirando hacie eje -z
  float l = 110.0f; // Longitud media de los lados del cuadrado
  glBegin(GL_QUADS);
    glColor3f(0.133f, 0.447f, 0.855f);  //Cambio de color azul
    glVertex3f(l, l, 0.0f);  //Vertice arriba derecha
    glVertex3f(-l, l, 0.0f); //Vertice arriba izquieda
    glVertex3f(-l, -l, 0.0f); //Vertice abajo izquierda
    glVertex3f(l, -l, 0.0f);  //Vertice abajo derecha
  glEnd();
  glLoadIdentity();
  glTranslatef(0.0f,0.0f,-700.0f);
  //glRotatef(rquad,0.0f,1.0f,0.0f);			// Rotate The Triangle On The Y axis ( NEW )
  gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); // Camara mirando hacie eje -z
  float d = 400.0f; //Logitud de la profundidad en z del paralelogramo
  glBegin(GL_QUADS);
    glColor3f(0.216f, 0.467f, 0.482f);  //Cambio de color azul
    glVertex3f(l, l, 0.0f);  //Vertice arriba derecha
    glVertex3f(l, -l, 0.0f);  //Vertice abajo derecha
    glVertex3f(l, -l, d); //Vertice abajo derecha Punto
    glVertex3f(l, l, d); //Vertice abajo izquierda

  glEnd();
  /*glLoadIdentity();					// Reset The Current Modelview Matrix
  glTranslatef(-1.5f,0.0f,-10.0f);			// Move Left 1.5 Units And Into The Screen 6.0
  //glRotatef(rtri,0.0f,1.0f,0.0f);			// Rotate The Triangle On The Y axis ( NEW )
  glRotatef(rtri,1.0f,0.0f,0.0f);
	gluLookAt(0.0, 0.0, -1.0, 0.0 , 1.0, -1.0,0.0,0.0,1.0);
	glBegin(GL_TRIANGLES);				// Start Drawing A Triangle
    glColor3f(1.0f,0.0f,0.0f);				// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
    glColor3f(0.0f,1.0f,0.0f);				// Green
    glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
    glColor3f(0.0f,0.0f,1.0f);				// Blue
    glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)
    glColor3f(1.0f,0.0f,0.0f);				// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Right)
    glColor3f(0.0f,0.0f,1.0f);				// Blue
    glVertex3f( 1.0f,-1.0f, 1.0f);			// Left Of Triangle (Right)
    glColor3f(0.0f,1.0f,0.0f);				// Green
    glVertex3f( 1.0f,-1.0f, -1.0f);			// Right Of Triangle (Right)
    glColor3f(1.0f,0.0f,0.0f);				// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Back)
    glColor3f(0.0f,1.0f,0.0f);				// Green
    glVertex3f( 1.0f,-1.0f, -1.0f);			// Left Of Triangle (Back)
    glColor3f(0.0f,0.0f,1.0f);				// Blue
    glVertex3f(-1.0f,-1.0f, -1.0f);			// Right Of Triangle (Back)
    glColor3f(1.0f,0.0f,0.0f);				// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Left)
    glColor3f(0.0f,0.0f,1.0f);				// Blue
    glVertex3f(-1.0f,-1.0f,-1.0f);			// Left Of Triangle (Left)
    glColor3f(0.0f,1.0f,0.0f);				// Green
    glVertex3f(-1.0f,-1.0f, 1.0f);			// Right Of Triangle (Left)
  glEnd();						// Done Drawing The Pyramid

  glLoadIdentity();					// Reset The Current Modelview Matrix
  glTranslatef(1.5f,0.0f,-7.0f);			// Move Right 1.5 Units And Into The Screen 7.0
  //glRotatef(rquad,1.0f,1.0f,1.0f);			// Rotate The Quad On The X axis ( NEW )
	glRotatef(rquad,0.0f,0.0f,0.0f);
	glBegin(GL_QUADS);					// Draw A Quad
    glColor3f(0.0f,1.0f,0.0f);				// Set The Color To Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);				// Set The Color To Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);				// Set The Color To Red
    glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);				// Set The Color To Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);			// Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);			// Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);			// Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);			// Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);				// Set The Color To Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);				// Set The Color To Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Right)
  glEnd();						// Done Drawing The Quad

	glLoadIdentity();					// Reset The Current Modelview Matrix
  glTranslatef(1.5f,1.5f,-20.0f);			// Move Left 1.5 Units And Into The Screen 6.0
  //glRotatef(rtri,0.0f,1.0f,0.0f);			// Rotate The Triangle On The Y axis ( NEW )
  glRotatef(rtri,1.0f,0.0f,0.0f);
	glBegin(GL_TRIANGLES);				// Start Drawing A Triangle
    glColor3f(1.0f,0.0f,0.0f);				// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
    glColor3f(0.0f,1.0f,0.0f);				// Green
    glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
    glColor3f(0.0f,0.0f,1.0f);				// Blue
    glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)
    glColor3f(1.0f,0.0f,0.0f);				// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Right)
    glColor3f(0.0f,0.0f,1.0f);				// Blue
    glVertex3f( 1.0f,-1.0f, 1.0f);			// Left Of Triangle (Right)
    glColor3f(0.0f,1.0f,0.0f);				// Green
    glVertex3f( 1.0f,-1.0f, -1.0f);			// Right Of Triangle (Right)
    glColor3f(1.0f,0.0f,0.0f);				// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Back)
    glColor3f(0.0f,1.0f,0.0f);				// Green
    glVertex3f( 1.0f,-1.0f, -1.0f);			// Left Of Triangle (Back)
    glColor3f(0.0f,0.0f,1.0f);				// Blue
    glVertex3f(-1.0f,-1.0f, -1.0f);			// Right Of Triangle (Back)
    glColor3f(1.0f,0.0f,0.0f);				// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Left)
    glColor3f(0.0f,0.0f,1.0f);				// Blue
    glVertex3f(-1.0f,-1.0f,-1.0f);			// Left Of Triangle (Left)
    glColor3f(0.0f,1.0f,0.0f);				// Green
    glVertex3f(-1.0f,-1.0f, 1.0f);			// Right Of Triangle (Left)
  glEnd();						// Done Drawing The Pyramid*/

  glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight){
  if (newHeight==0) {					// Prevent A Divide By Zero By
    newHeight=1;					// Making Height Equal One
  }

  glViewport(0,0,newWidth,newHeight);			// Reset The Current Viewport

  glMatrixMode(GL_PROJECTION);				// Select The Projection Matrix
  glLoadIdentity();					// Reset The Projection Matrix

  // Calculate The Aspect Ratio Of The Window
  gluPerspective(45.0f,(GLfloat)newWidth/(GLfloat)newHeight,0.1f,1000.0f);
	//glOrtho (-5.0, 5.0, -5.0, 5.0, -30.0, 30.0);

  glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
  glLoadIdentity();					// Reset The Modelview Matrix
}

int main(int argc, char ** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB | GLUT_DEPTH);
  //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowPosition(50,50);
  glutInitWindowSize(winWidth,winHeight);
  glutCreateWindow("3d Shape");
  init();
  glutDisplayFunc(displayFcn);
  glutReshapeFunc(winReshapeFcn);
  glutMainLoop();
}
