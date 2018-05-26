#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include <map>
#include <vector>

#define PI 3.141592654f

// Global variables
char title[] = "Lab marcha";  // Windowed mode's title
int windowWidth  = 1200;     // Windowed mode's width
int windowHeight = 900;     // Windowed mode's height
int windowPosX   = 50;      // Windowed mode's top-left corner x
int windowPosY   = 50;      // Windowed mode's top-left corner y

int momento = 0;

//Llaves de partes
std::string SACR = "SACR";
std::string LASI = "LASI";
std::string LTHI = "LTHI";
std::string LKNE = "LKNE";
std::string LTIB = "LTIB";
std::string LANK = "LANK";
std::string LTOE = "LTOE";
std::string RASI = "RASI";
std::string RTHI = "RTHI";
std::string RKNE = "RKNE";
std::string RTIB = "RTIB";
std::string RANK = "RANK";
std::string RTOE = "RTOE";

//Camara
float CamaraP1X = 0.0f;
float CamaraP1Y = 0.0f;
float CamaraP1Z = 1000.0f;
float CamaraP2X = 0.0f;
float CamaraP2Y = 0.0f;
float CamaraP2Z = -1000.0f;
float CamaraEjeX = 0.0f;
float CamaraEjeY = 1.0f;
float CamaraEjeZ = 0.0f;

class Punto {
  public:
    GLfloat x,y,z;
};

std::map< std::string, std::vector<Punto> > puntos;

void initGL() {
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}

bool esLetra(char linea[]) {
  if ((linea[0] > 'A' && linea[0] < 'Z') || (linea[0]> 'a' && linea[0] < 'z')) {
    return true;
  }else{
    return false;
  }
}

void leerArchivo() {
  std::ifstream archivo("entrada.in");
  char linea[128];
  int i,j;
  j=0;
  if(archivo.fail())
    std::cerr << "Error al abrir el archivo" << std::endl;
  else{
    bool sigue = true;
    while(!archivo.eof()) {
      char * pch;
      std::vector<Punto> v;
      if (j == 0) {
        archivo.getline(linea, sizeof(linea));
        ++j;
      }
      std::string llave(linea);
      sigue = true;
      archivo.getline(linea, sizeof(linea));
      while (!archivo.eof() && sigue) {
        Punto punto;
        i = 0;
        pch = strtok (linea," ");
        while (pch != NULL)
        {
          if(i == 0){
            punto.x = atof(pch);
          }else if(i == 1){
            punto.y = atof(pch);
          }else if(i == 2) {
            punto.z = atof(pch);
          }
          pch = strtok (NULL, " ");
          ++i;
        }
        v.push_back(punto);
        archivo.getline(linea, sizeof(linea));
        if (esLetra(linea)) {
          sigue = false;
          std::pair< std::string, std::vector<Punto> > pareja(llave, v);
          puntos.insert(pareja);
        }else{
          sigue = true;
        }
      }
    }

}
    archivo.close();
}

void display() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the color buffer
  glMatrixMode(GL_MODELVIEW);

// CADERA IZQUIEDA
  glLoadIdentity();
  gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  glPointSize(3.0f);

  glColor3f(0.0f, 1.0f, 1.0f);
  Punto p = puntos[LASI][momento];
  glTranslatef(-400.0,-380, -500);
  glBegin(GL_POINTS);
  glVertex3f((p.x/3.62), p.z/2.5, p.y/1.9);
  glEnd();
//CADERA DERECHA

glLoadIdentity();
gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
glPointSize(3.0f);

glColor3f(0.0f, 1.0f, 1.0f);
Punto p1 = puntos[RASI][momento];
glTranslatef(-400.0,-380, -500);
glBegin(GL_POINTS);
glVertex3f((p1.x/3.62), p1.z/2.5, p1.y/1.9);
glEnd();
//Muslo IZQUIEDO
glLoadIdentity();
gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
glPointSize(3.0f);

glColor3f(0.0f, 1.0f, 1.0f);
Punto p2 = puntos[LTHI][momento];
glTranslatef(-400.0,-380, -500);
glBegin(GL_POINTS);
glVertex3f((p2.x/3.62), p2.z/2.5, p2.y/1.9);
glEnd();
//Muslo DERECHO

glLoadIdentity();
gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
glPointSize(3.0f);

glColor3f(0.0f, 1.0f, 1.0f);
Punto p3 = puntos[RTHI][momento];
glTranslatef(-400.0,-380, -500);
glBegin(GL_POINTS);
glVertex3f((p3.x/3.62), p3.z/2.5, p3.y/1.9);
glEnd();
//Rodilla Izquierda

glLoadIdentity();
gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
glPointSize(3.0f);

glColor3f(0.0f, 1.0f, 1.0f);
Punto p4 = puntos[LKNE][momento];
glTranslatef(-400.0,-380, -500);
glBegin(GL_POINTS);
glVertex3f((p4.x/3.62), p4.z/2.5, p4.y/1.9);
glEnd();
//Rodilla DERECHO

glLoadIdentity();
gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
glPointSize(3.0f);

glColor3f(0.0f, 1.0f, 1.0f);
Punto p5 = puntos[RKNE][momento];
glTranslatef(-400.0,-380, -500);
glBegin(GL_POINTS);
glVertex3f((p5.x/3.62), p5.z/2.5, p5.y/1.9);
glEnd();
//Canilla IZQUIEDA

glLoadIdentity();
gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
glPointSize(3.0f);

glColor3f(0.0f, 1.0f, 1.0f);
Punto p6 = puntos[LTIB][momento];
glTranslatef(-400.0,-380, -500);
glBegin(GL_POINTS);
glVertex3f((p6.x/3.62), p6.z/2.5, p6.y/1.9);
glEnd();
//Canilla DERECHA

glLoadIdentity();
gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
glPointSize(3.0f);

glColor3f(0.0f, 1.0f, 1.0f);
Punto p7 = puntos[RTIB][momento];
glTranslatef(-400.0,-380, -500);
glBegin(GL_POINTS);
glVertex3f((p7.x/3.62), p7.z/2.5, p7.y/1.9);
glEnd();
//Tobillo IZQUIEDO

glLoadIdentity();
gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
glPointSize(3.0f);

glColor3f(0.0f, 1.0f, 1.0f);
Punto p8 = puntos[LANK][momento];
glTranslatef(-400.0,-380, -500);
glBegin(GL_POINTS);
glVertex3f((p8.x/3.62), p8.z/2.5, p8.y/1.9);
glEnd();
//Tobillo DERECHO

glLoadIdentity();
gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
glPointSize(3.0f);

glColor3f(0.0f, 1.0f, 1.0f);
Punto p9 = puntos[RANK][momento];
glTranslatef(-400.0,-380, -500);
glBegin(GL_POINTS);
glVertex3f((p9.x/3.62), p9.z/2.5, p9.y/1.9);
glEnd();
  if (momento <= 142) {
    ++momento;

  }else {
    std::cout << "fin" << '\n';
  }

  glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
}

/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix

   /*gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);*/
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,-500.0f,500.0f);
}

void Timer(int a) {
	glutPostRedisplay();
	glutTimerFunc(100,Timer,0);
}

void idle() {
    display();
}


int main(int argc, char ** argv) {
  leerArchivo();
  glutInit(&argc, argv);            // Initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
  glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
  glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
  glutCreateWindow(title);      // Create window with given title
  glutDisplayFunc(display);     // Register callback handler for window re-paint
  glutReshapeFunc(reshape);     // Register callback handler for window re-shape
	glutTimerFunc(0,Timer,0);
	//glutIdleFunc(idle);
  initGL();                     // Our own OpenGL initialization
  glutMainLoop();               // Enter event-processing loop
  return 0;
}
