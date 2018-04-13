
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
  //gluLookAt(0.0, 0.0, 350.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Camara mirando hacie eje -z
  gluLookAt(0.0, 600.0, -270.0, 0.0, 0.0, -270.0, 0.0, 0.0,-1.0); // Camara mirando de arriba hacia abajo
  glTranslatef(0.0f,0.0f,-500.0f);
  //glRotatef(rquad,0.0f,1.0f,0.0f);			// Rotate The Triangle On The Y axis ( NEW )
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
  //glLoadIdentity();
  //glTranslatef(0.0f,0.0f,-700.0f);
  //glRotatef(rquad,0.0f,1.0f,0.0f);			// Rotate The Triangle On The Y axis ( NEW )
  //gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); // Camara mirando hacie eje -z

  glBegin(GL_QUADS);
    glColor3f(0.216f, 0.467f, 0.482f);  //Cambio de color otro
    glVertex3f(l, l, 0.0f);  //Vertice arriba derecha
    glVertex3f(l, -l, 0.0f);  //Vertice abajo derecha
    glVertex3f(l, -l, d); //Vertice abajo derecha Punto
    glVertex3f(l, l, d); //Vertice abajo izquierda punto
  glEnd();
  //PARALELEPIPEDO LADO ARRIBA SIN RELLENO
  //glLoadIdentity();
  //glTranslatef(0.0f,0.0f,-700.0f);
  //glRotatef(rquad,0.0f,1.0f,0.0f);			// Rotate The Triangle On The Y axis ( NEW )
  //gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); // Camara mirando hacie eje -z
  glBegin(GL_LINE_LOOP);
    glColor3f(0.0f,1.0f,0.0f); //Cambio de color verde
    glVertex3f(l, l, 0.0f);  //Vertice arriba derecha
    glVertex3f(-l, l, 0.0f); //Vertice arriba izquieda
    glVertex3f(-l, l, d);  //Vertice arriba izquierda punto
    glVertex3f(l, l, d); //Vertice abajo derecha Punto
  glEnd();
  //PARALELEPIPEDO IZQUIEDA SIN RELLENO
  //glLoadIdentity();
  //glTranslatef(0.0f,0.0f,-700.0f);
  //glRotatef(rquad,0.0f,1.0f,0.0f);			// Rotate The Triangle On The Y axis ( NEW )
  //gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); // Camara mirando hacie eje -z
  glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0f, 0.0f);  //Cambio de color verde
    glVertex3f(-l, l, 0.0f);  //Vertice arriba izquieda
    glVertex3f(-l, -l, 0.0f);  //Vertice abajo izquierda
    glVertex3f(-l, -l, d); //Vertice abajo izquierda Punto
    glVertex3f(-l, l, d); //Vertice arriba izquierda punto
  glEnd();
  //PARALELEPIPEDO ABAJO
  //glLoadIdentity();
  //glTranslatef(0.0f,0.0f,-700.0f);
  //glRotatef(rquad,0.0f,1.0f,0.0f);			// Rotate The Triangle On The Y axis ( NEW )
  //gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); // Camara mirando hacie eje -z
  glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0f, 0.0f);  //Cambio de color verde
    glVertex3f(-l, -l, 0.0f);  //Vertice abajo izquierda
    glVertex3f(l, -l, 0.0f);  //Vertice abajo derecha
    glVertex3f(l, -l, d); //Vertice abajo derecha punto
    glVertex3f(-l, -l, d); //Vertice abajo izquierda punto
  glEnd();
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
