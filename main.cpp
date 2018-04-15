#include <GL/freeglut.h>
#include <GL/gl.h>
//#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLsizei winWidth=1200, winHeight=900;
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
  //PARALELEPIPEDO FONDO
  float l = 150.0f; // Longitud media de los lados del cuadrado
  float d = 450.0f; //Logitud de la profundidad en z del paralelogramo
  glLoadIdentity();
  //gluLookAt(-600.0, 0.0, -270.0f, 0.0f, 0.0, -270.0f, 0.0, 1.0f, 0.0); // Camara mirando del lado izquiedo
  gluLookAt(0.0, 0.0, 350.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Camara mirando hacie eje -z
  //gluLookAt(0.0, 600.0, -270.0, 0.0, 0.0, -270.0, 0.0, 0.0,-1.0); // Camara mirando de arriba hacia abajo
  glTranslatef(0.0f,0.0f,-500.0f);
  //Rampa
  glBegin(GL_QUADS);
    glColor3f(0.789f, 0.0, 0.831f); //color violeta
    glVertex3f(l/2, -l, 0.0f); //Vertice abajo derecha
    glVertex3f(-l/2, -l, 0.0f); //Vertice abajo izquierda
    glVertex3f(-l/2, -l, d); // Vertice abajo izquieda Punto
    glVertex3f(l/2, -l, d); //Vertice abajo derecha punto
  glEnd();
  glBegin(GL_QUADS);
    glColor3f(0.133f, 0.447f, 0.855f);  //Cambio de color azul
    glVertex3f(l, l, 0.0f);  //Vertice arriba derecha
    glVertex3f(-l, l, 0.0f); //Vertice arriba izquieda
    glVertex3f(-l, -l, 0.0f); //Vertice abajo izquierda
    glVertex3f(l, -l, 0.0f);  //Vertice abajo derecha
  glEnd();
  //PARALELEPIPEDO LADO DERECHA
  glBegin(GL_QUADS);
    glColor3f(0.216f, 0.467f, 0.482f);  //Cambio de color otro
    glVertex3f(l, l, 0.0f);  //Vertice arriba derecha
    glVertex3f(l, -l, 0.0f);  //Vertice abajo derecha
    glVertex3f(l, -l, d); //Vertice abajo derecha Punto
    glVertex3f(l, l, d); //Vertice abajo izquierda punto
  glEnd();
  //PARALELEPIPEDO LADO ARRIBA SIN RELLENO
  glBegin(GL_LINE_LOOP);
    glColor3f(0.0f,1.0f,0.0f); //Cambio de color verde
    glVertex3f(l, l, 0.0f);  //Vertice arriba derecha
    glVertex3f(-l, l, 0.0f); //Vertice arriba izquieda
    glVertex3f(-l, l, d);  //Vertice arriba izquierda punto
    glVertex3f(l, l, d); //Vertice abajo derecha Punto
  glEnd();
  //PARALELEPIPEDO IZQUIEDA SIN RELLENO
  glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0f, 0.0f);  //Cambio de color verde
    glVertex3f(-l, l, 0.0f);  //Vertice arriba izquieda
    glVertex3f(-l, -l, 0.0f);  //Vertice abajo izquierda
    glVertex3f(-l, -l, d); //Vertice abajo izquierda Punto
    glVertex3f(-l, l, d); //Vertice arriba izquierda punto
  glEnd();
  //PARALELEPIPEDO ABAJO
  glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0f, 0.0f);  //Cambio de color verde
    glVertex3f(-l, -l, 0.0f);  //Vertice abajo izquierda
    glVertex3f(l, -l, 0.0f);  //Vertice abajo derecha
    glVertex3f(l, -l, d); //Vertice abajo derecha punto
    glVertex3f(-l, -l, d); //Vertice abajo izquierda punto
  glEnd();

 //PINTA CABEZA
  glTranslatef(0.0f,120.0f,200.0f); ///////////////////////////////////////////////////////////ACA
  glColor3f(1.0f,0.863f,0.8f);
  glutSolidSphere(30, 50, 50);
 //PINTA TORSO
  glTranslatef(0.0f,-20.0f,0.0f);
  glRotatef (90.0, 1.0f, 0.0f, 0.0f);
  glColor3f(0.0f,1.0f,0.0f);
  GLUquadricObj *cylind1 = gluNewQuadric();
  gluQuadricDrawStyle (cylind1, GLU_LINE);
  gluCylinder (cylind1, 10, 10,100, 500, 500);
 //PINTA BRAZOS
  glTranslatef(-10.0f,0.0f,10.0f); //XZY
  glRotatef (-20.0, 0.0f, 1.0f, 0.0f);
  glColor3f(1.0f,0.0f,0.0f);
  GLUquadricObj *cylind2 = gluNewQuadric();
  gluQuadricDrawStyle (cylind2, GLU_LINE);
  gluCylinder (cylind2, 3, 3,40, 100, 100);

  glRotatef (20.0, 0.0f, 1.0f, 0.0f);
  glTranslatef(10.0f,0.0f,-10.0f);

  glTranslatef(10.0f,0.0f,10.0f); //XZY
  glRotatef (20.0, 0.0f, 1.0f, 0.0f);
  glColor3f(1.0f,1.0f,0.0f);
  GLUquadricObj *cylind3 = gluNewQuadric();
  gluQuadricDrawStyle (cylind3, GLU_LINE);
  gluCylinder (cylind3, 3, 3,40, 100, 100);

  glRotatef (-20.0, 0.0f, 1.0f, 0.0f);
  glTranslatef(-10.0f,0.0f,-10.0f);
//PINTA BOLAS CADERA
  //BOLA 1
  glTranslatef(5.0f,0.0f,102.0f);
  glColor3f(0.0f,0.0f,0.0f);
  glutSolidSphere(3, 50, 50);
  //BOLA 2
  glTranslatef(-10.0f,0.0f,0.0f);
  glColor3f(0.0f,0.0f,0.0f);
  glutSolidSphere(3, 50, 50);

  glTranslatef(10.0f,0.0f,0.0f);
  glTranslatef(-5.0f,0.0f,-102.0f);
//BOLAS BRAZOS
  //BOLA 1
  glTranslatef(24.8f,0.0f,49.2f);
  glColor3f(0.0f,0.0f,0.0f);
  glutSolidSphere(3, 50, 50);
  //BOLA 2
  glTranslatef(-49.6f,0.0f,0.0f);
  glColor3f(0.0f,0.0f,0.0f);
  glutSolidSphere(3, 50, 50);
  glTranslatef(49.6f,0.0f,0.0f);
  glTranslatef(-24.8f,0.0f,-49.2f);
//RESTO DE LOS BRAZOS
	glTranslatef(-25.0f,0.0f,52.0f); //XZY
  glColor3f(1.0f,0.0f,0.0f);
  GLUquadricObj *cylind4 = gluNewQuadric();
  gluQuadricDrawStyle (cylind4, GLU_LINE);
  gluCylinder (cylind4, 3, 3,40, 100, 100);

	glTranslatef(25.0f,0.0f,-52.0f);

  glTranslatef(25.0f,0.0f,52.0f); //XZY
  glColor3f(1.0f,1.0f,0.0f);
  GLUquadricObj *cylind5 = gluNewQuadric();
  gluQuadricDrawStyle (cylind5, GLU_LINE);
  gluCylinder (cylind5, 3, 3,40, 100, 100);

  glTranslatef(-25.0f,0.0f,52.0f);
//MUSLOS
	glTranslatef(-5.0f,0.0f,-1.0f); //XZY
  glRotatef (-2.0, 0.0f, 1.0f, 0.0f);
  glColor3f(0.0f,0.0f,1.0f);
  GLUquadricObj *cylind6 = gluNewQuadric();
  gluQuadricDrawStyle (cylind6, GLU_LINE);
  gluCylinder (cylind6, 5, 5,60, 100, 100);

  glRotatef (2.0, 0.0f, 1.0f, 0.0f);
  glTranslatef(5.0f,0.0f,1.0f);

  glTranslatef(5.0f,0.0f,-1.0f); //XZY
  glRotatef (2.0, 0.0f, 1.0f, 0.0f);
  glColor3f(0.0f,0.0f,1.0f);
  GLUquadricObj *cylind7 = gluNewQuadric();
  gluQuadricDrawStyle (cylind7, GLU_LINE);
  gluCylinder (cylind7, 5, 5,60, 100, 100);

  glRotatef (-2.0, 0.0f, 1.0f, 0.0f);
  glTranslatef(-5.0f,0.0f,1.0f);
//CINTURON
	glTranslatef(0.0f,0.0f,-2.0f);
  glColor3f(0.4f,0.2f,0.0f);
	glutSolidTorus(2,10, 150, 100);
	glTranslatef(0.0f,0.0f,2.0f);
//PINTA BOLAS RODILLAS
  //BOLA 1
  glTranslatef(7.0f,0.0f,60.0f);
  glColor3f(0.0f,0.0f,0.0f);
  glutSolidSphere(3, 50, 50);
  //BOLA 2
  glTranslatef(-14.0f,0.0f,0.0f);
  glColor3f(0.0f,0.0f,0.0f);
  glutSolidSphere(3, 50, 50);

  glTranslatef(14.0f,0.0f,0.0f);
  glTranslatef(-7.0f,0.0f,-60.0f);
//RESTO DE LAS PIERNAS
	glTranslatef(-7.0f,0.0f,63.0f); //XZY
  glColor3f(0.0f,0.0f,1.0f);
  GLUquadricObj *cylind8 = gluNewQuadric();
  gluQuadricDrawStyle (cylind8, GLU_LINE);
  gluCylinder (cylind8, 5, 3,55, 100, 100);

	glTranslatef(7.0f,0.0f,0.0f);

  glTranslatef(7.0f,0.0f,0.0f); //XZY
  glColor3f(0.0f,0.0f,1.0f);
  GLUquadricObj *cylind9 = gluNewQuadric();
  gluQuadricDrawStyle (cylind9, GLU_LINE);
  gluCylinder (cylind9, 5, 3,55, 100, 100);

  glTranslatef(-7.0f,0.0f,0.0f);
//PINTA BOLAS TOBILLOS
  //BOLA 1
  glTranslatef(7.0f,0.0f,56.0f);
  glColor3f(0.0f,0.0f,0.0f);
  glutSolidSphere(3, 50, 50);
  //BOLA 2
  glTranslatef(-14.0f,0.0f,0.0f);
  glColor3f(0.0f,0.0f,0.0f);
  glutSolidSphere(3, 50, 50);

  glTranslatef(14.0f,0.0f,0.0f);
  glTranslatef(-7.0f,0.0f,0.0f);
//ZAPATOS
	glTranslatef(7.0f,-3.0f,8.0f); //XZY
  glRotatef (90.0, 0.0f, 1.0f, 0.0f);
	glRotatef (-5.0, 0.0f, 1.0f, 0.0f);
	glRotatef (-90.0, 1.0f, 0.0f, 0.0f);
  glColor3f(0.0f,0.0f,1.0f);
  GLUquadricObj *cylind10 = gluNewQuadric();
  gluQuadricDrawStyle (cylind10, GLU_LINE);
  gluCylinder (cylind10, 7, 3,30, 100, 100);
	glRotatef (90.0, 1.0f, 0.0f, 0.0f);
	glRotatef (5.0, 0.0f, 1.0f, 0.0f);
	glRotatef (-90.0, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f,29.0f,0.0f);
  glutSolidSphere(3, 50, 50);
	glTranslatef(0.0f,-29.0f,0.0f);
	glTranslatef(-7.0f,3.0f,-8.0f);
//2
	glTranslatef(-7.0f,-3.0f,8.0f); //XZY
  glRotatef (90.0, 0.0f, 1.0f, 0.0f);
	glRotatef (-5.0, 0.0f, 1.0f, 0.0f);
	glRotatef (-90.0, 1.0f, 0.0f, 0.0f);
  glColor3f(0.0f,0.0f,1.0f);
  GLUquadricObj *cylind11 = gluNewQuadric();
  gluQuadricDrawStyle (cylind11, GLU_LINE);
  gluCylinder (cylind11, 7, 3,30, 100, 100);
	glRotatef (90.0, 1.0f, 0.0f, 0.0f);
	glRotatef (5.0, 0.0f, 1.0f, 0.0f);
	glRotatef (-90.0, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f,29.0f,0.0f);
  glutSolidSphere(3, 50, 50);
	glTranslatef(0.0f,-29.0f,0.0f);
	glTranslatef(7.0f,3.0f,-8.0f);
//MANOS
  //MANO 1
  glTranslatef(25.0f,0.0f,-130.0f);
  glColor3f(1.0f,0.863f,0.8f);
  glutSolidSphere(4, 50, 50);
  //MANO 2
	glTranslatef(-50.0f,0.0f,0.0f);
  glColor3f(1.0f,0.863f,0.8f);
  glutSolidSphere(4, 50, 50);

	glTranslatef(50.0f,0.0f,0.0f);
  glTranslatef(-25.0f,0.0f,0.0f);
//OJOS y GAFAS
	glTranslatef(-9.0f,30.0f,-110.0f);
	glRotatef (-30.0, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f,0.25f,2.0f);
  glColor3f(1.0f,1.0f,1.0f);
  glutSolidSphere(4, 50, 50);

	glColor3f(0.0f,0.0f,0.0f);
	glRotatef (90.0, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(1,4.5, 150, 100);
	glRotatef (-90.0, 1.0f, 0.0f, 0.0f);
	glScalef(1.0f,4.0f,0.5f);
	glRotatef (30.0, 0.0f, 1.0f, 0.0f);
//

	glTranslatef(17.0f,0.0f,0.0f);
	glRotatef (30.0, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f,0.25f,2.0f);
	glColor3f(1.0f,1.0f,1.0f);
	glutSolidSphere(4, 50, 50);

	glColor3f(0.0f,0.0f,0.0f);
	glRotatef (90.0, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(1,4.5, 150, 100);
	glRotatef (-90.0, 1.0f, 0.0f, 0.0f);
  glScalef(1.0f,4.0f,0.5f);
	glRotatef (-30.0, 0.0f, 1.0f, 0.0f);
//
	glColor3f(0.0f,0.0f,0.0f);
	glutSolidSphere(1.5f, 50, 50);

	glTranslatef(-15.0f,0.0f,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
	glutSolidSphere(1.5f, 50, 50);



  glFlush();
  gluDeleteQuadric (cylind1);
  gluDeleteQuadric (cylind2);
  gluDeleteQuadric (cylind3);
  gluDeleteQuadric (cylind4);
  gluDeleteQuadric (cylind5);
  gluDeleteQuadric (cylind6);
  gluDeleteQuadric (cylind7);
  gluDeleteQuadric (cylind8);
  gluDeleteQuadric (cylind9);
  gluDeleteQuadric (cylind10);
  gluDeleteQuadric (cylind11);
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
