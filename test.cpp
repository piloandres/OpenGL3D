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
int windowHeight = 1000;     // Windowed mode's height
int windowPosX   = 50;      // Windowed mode's top-left corner x
int windowPosY   = 50;      // Windowed mode's top-left corner y

int momento = 0;
int frameNumber;
float radioPiernas = 30.0f;
bool activo = true;
float anguloActual = 0.0f;

float l = 700.0f; // Longitud media de los lados del cuadrado
float d = 2000.0f; //Logitud de la profundidad en z del paralelogramo

float baseX =500.0;
float baseY =-380.0;
float baseZ =-1500.0;
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
/*float CamaraP1X = 0.0f;
float CamaraP1Y = 0.0f;
float CamaraP1Z = 1000.0f;
float CamaraP2X = 0.0f;
float CamaraP2Y = 0.0f;
float CamaraP2Z = -1000.0f;
float CamaraEjeX = 0.0f;
float CamaraEjeY = 1.0f;
float CamaraEjeZ = 0.0f;*/
//Camara
float CamaraP1X = 1000.0f;
float CamaraP1Y = 0.0f;
float CamaraP1Z = 0.0f;
float CamaraP2X = -1000.0f;
float CamaraP2Y = 0.0f;
float CamaraP2Z = 0.0f;
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

void actualizarCamara(int signo){
  if (signo >0) {
    anguloActual += PI/12.0;
  }else{
    anguloActual -= PI/12.0;
  }

  CamaraP2X = 900.0*cos(anguloActual) + 1100.0;
  CamaraP2Z = -900.0*sin(anguloActual) - 1100.0;
  CamaraP1X = 900.0*cos(anguloActual+PI) + 1100.0;
  CamaraP1Z = -900.0*sin(anguloActual+PI) -1100.0;
}

bool esLetra(char linea[]) {
  if ((linea[0] > 'A' && linea[0] < 'Z') || (linea[0]> 'a' && linea[0] < 'z')) {
    return true;
  }else{
    return false;
  }
}

void leerArchivo(char nombre[]) {
//  std::ifstream archivo(nombre);
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
        if (esLetra(linea) || archivo.eof()) {
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
// clindro 2 puntos
void renderCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions,GLUquadricObj *quadric)
{
   float vx = x2-x1;
   float vy = y2-y1;
   float vz = z2-z1;

   //handle the degenerate case of z1 == z2 with an approximation
   if(vz == 0)
       vz = .00000001;

   float v = sqrt( vx*vx + vy*vy + vz*vz );
   float ax = 57.2957795*acos( vz/v );
   if ( vz < 0.0 )
       ax = -ax;
   float rx = -vy*vz;
   float ry = vx*vz;
   glPushMatrix();

   //draw the cylinder body
   glTranslatef( x1,y1,z1 );
   glRotatef(ax, rx, ry, 0.0);
   gluQuadricOrientation(quadric,GLU_OUTSIDE);
   gluCylinder(quadric, radius, radius, v, subdivisions, 1);

   //draw the first cap
   gluQuadricOrientation(quadric,GLU_INSIDE);
   gluDisk( quadric, 0.0, radius, subdivisions, 1);
   glTranslatef( 0,0,v );

   //draw the second cap
   gluQuadricOrientation(quadric,GLU_OUTSIDE);
   gluDisk( quadric, 0.0, radius, subdivisions, 1);
   glPopMatrix();
}
void renderCylinder_convenient(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions)
{
   //the same quadric can be re-used for drawing many cylinders
   GLUquadricObj *quadric=gluNewQuadric();
   gluQuadricNormals(quadric, GLU_SMOOTH);
   renderCylinder(x1,y1,z1,x2,y2,z2,radius,subdivisions,quadric);
   gluDeleteQuadric(quadric);
}

void display() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the color buffer
  glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  glTranslatef(baseX-400.0,350.0f,baseZ+200.0);
	glRotatef(90.0f,0.0f,1.0f,0.0f);
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

	/*glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	float raa = -550.0f;
	int i = 0;
	float nc = 0.0;
	glColor3f(0.0, 1.0f, 0.0f);
	glTranslatef(raa,-300.0f,-700.0f);
	glutSolidSphere(40,100,100);
	for (i=0;i<13;i++){
		glColor3f(nc, 1.0f, 0.0f);
		glTranslatef(130.0f,0.0f,0.0f);
		glutSolidSphere(40,100,100);
		nc += 0.076f;
	}

	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	nc = 1.0;
	glTranslatef(raa,-300.0f,200.0f);
	glutSolidSphere(40,100,100);
	for (i=0;i<13;i++){
		glTranslatef(130.0f,0.0f,0.0f);
		glColor3f(nc, 1.0f, 0.0f);
		nc -= 0.076f;
		glutSolidSphere(40,100,100);
	}*/
	// SACRO
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glPointSize(10.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	Punto p0 = puntos[SACR][momento];

	glTranslatef(baseX,baseY,baseZ);
	glBegin(GL_POINTS);
	glVertex3f((p0.x/3.62), p0.z/2.5, p0.y/1.9);
	glEnd();

// CADERA IZQUIEDA
  glLoadIdentity();
  gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  glPointSize(3.0f);

  glColor3f(0.0f, 1.0f, 1.0f);
  Punto p = puntos[LASI][momento];
  glTranslatef(baseX,-380, baseZ);
  glBegin(GL_POINTS);
  glVertex3f((p.x/3.62), p.z/2.5, p.y/1.9);
  glEnd();
//CADERA DERECHA

	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glPointSize(3.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	Punto p1 = puntos[RASI][momento];
	glTranslatef(baseX,-380, baseZ);
	glBegin(GL_POINTS);
	glVertex3f((p1.x/3.62), p1.z/2.5, p1.y/1.9);
	glEnd();
	//Muslo IZQUIEDO
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glPointSize(3.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	Punto p2 = puntos[LTHI][momento];
	glTranslatef(baseX,-380, baseZ);
	glBegin(GL_POINTS);
	glVertex3f((p2.x/3.62), p2.z/2.5, p2.y/1.9);
	glEnd();
	//Union muslo y cadera Izquierda
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glColor3f(0.0f, 0.2f, 0.8f);
	glTranslatef(baseX,-380, baseZ);
	renderCylinder_convenient(p.x/3.62, p.z/2.5, p.y/1.9,p2.x/3.62, p2.z/2.5, p2.y/1.9, radioPiernas,50);
	//Muslo DERECHO

	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glPointSize(3.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	Punto p3 = puntos[RTHI][momento];
	glTranslatef(baseX,-380, baseZ);
	glBegin(GL_POINTS);
	glVertex3f((p3.x/3.62), p3.z/2.5, p3.y/1.9);
	glEnd();
	//Union muslo y cadera derecha
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glLineWidth(10.0f);
	glColor3f(0.0f, 0.2f, 0.8f);
	glTranslatef(baseX,-380, baseZ);
	renderCylinder_convenient(p1.x/3.62, p1.z/2.5, p1.y/1.9,p3.x/3.62, p3.z/2.5, p3.y/1.9, radioPiernas,50);

	//PINTA TORSO
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-350.0,-100, -500.0);
  glTranslatef(baseX+50.0,-100, baseZ);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
	glRotatef (90.0, 1.0f, 0.0f, 0.0f);
	glColor3f(0.0f,1.0f,0.0f);
	GLUquadricObj *cylind1 = gluNewQuadric();
	gluQuadricDrawStyle (cylind1, GLU_LINE);
	gluCylinder (cylind1,90, 90,300, 500, 500);

	//PINTA CABEZA
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-350.0,70, -500.0); ///////////////////////////////////////////////////////////ACA
  glTranslatef(baseX+50.0,70, baseZ);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
	glColor3f(1.0f,0.863f,0.8f);
	glutSolidSphere(140, 50, 50);
  //glutSolidSphere(70, 50, 50);
	//Corbata
  glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  //glTranslatef(-250.0f, -100.0f,-500.0f);
  glTranslatef(baseX+150.0f, -100.0f,baseZ);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
  glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f,1.0f); //color azul
    glVertex3f(0.0f,0.0f, 0.0f);
    glVertex3f(0.0f,-250.0f, -20.0f);
    glVertex3f(0.0f, -260.0f, 0.0f);
    glVertex3f(0.0f, -250.0f, 20.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
  glEnd();
	// Cuello
	glLoadIdentity();
	glColor3f(1.0f,0.863f,0.8f);
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-350.0,-40, -500.0);
  glTranslatef(baseX+50.0,-40.0, baseZ);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
	glRotatef(90.0,1.0,0.0,0.0);
	glutSolidCone(90, 100, 50, 50);


//OJOS y GAFAS
	float prof = -300.0f;
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-200.0f,70.0f,-470.0);
  glTranslatef(baseX+200.0f,70.0f,baseZ+30.0);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
  glRotatef (90.0, 0.0f, 0.0f, 1.0f);
	glRotatef (-60.0, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f,0.25f,2.0f);
  glColor3f(1.0f,1.0f,1.0f);
  glutSolidSphere(20, 50, 50);

	glColor3f(0.0f,0.0f,0.0f);
	glRotatef (90.0, 1.0f, 0.0f, .0f);
	glutSolidTorus(3,20.5, 150, 100);
//
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-200.0f,70.0f,-540.0);
  glTranslatef(baseX+200.0f,70.0f,baseZ-40.0);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
  glRotatef (90.0, 0.0f, 0.0f, 1.0f);
	glRotatef (60.0, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f,0.25f,2.0f);
  glColor3f(1.0f,1.0f,1.0f);
  glutSolidSphere(20, 50, 50);

	glColor3f(0.0f,0.0f,0.0f);
	glRotatef (90.0, 1.0f, 0.0f, .0f);
	glutSolidTorus(3,20.5, 150, 100);
//
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-250.0f,70.0f,-470.0);
  glTranslatef(baseX+150.0,70.0f,baseZ+30.0);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
	glColor3f(0.0f,0.0f,0.0f);
	glutSolidSphere(5.0f, 50, 50);

	glTranslatef(0.0f,0.0f,-70.0f);
	glColor3f(0.0f,0.0f,0.0f);
	glutSolidSphere(5.0f, 50, 50);

//PALOS GAFAS
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
		//glTranslatef(-250.0f, 70.0f,-450.0);
    glTranslatef(baseX+150.0f, 70.0f,baseZ-50.0);
		glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
		glLineWidth(4.0);
		glBegin(GL_LINES);
		  glColor3f(0.0f,0.0f,0.0f); //color negro
		  glVertex3f(0.0f,0.0f, 0.0f);
		  glVertex3f(-3.0f,3.0f, 80.0f);
		glEnd();

		glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
		//glTranslatef(-250.0f, 70.0f,-560.0);
    glTranslatef(baseX+150.0f, 70.0f,baseZ-60.0);
		glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
		glLineWidth(4.0);
		glBegin(GL_LINES);
		  glColor3f(0.0f,0.0f,0.0f); //color negro
		  glVertex3f(0.0f,0.0f, 0.0f);
		  glVertex3f(-3.0f,3.0f, -60.0f);
		glEnd();
		glLineWidth(1.0);

 // Nariz y boca
  glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  //glTranslatef(-250.0f, 20.0f,-500.0);
  glTranslatef(baseX+150.0f, 20.0f,baseZ);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
  glLineWidth(2.5);
  glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,0.0f); //color negro
    glVertex3f(0.0f,0.0f, 20.0f);
    glVertex3f(0.0f,-30.0f, 0.0f);
  glEnd();

  glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  //glTranslatef(-250.0f, 20.0f,-500.0);
  glTranslatef(baseX+150.0f, 20.0f,baseZ);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
  glLineWidth(2.5);
  glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,0.0f); //color negro
    glVertex3f(0.0f,0.0f, -20.0f);
    glVertex3f(0.0f,-30.0f, 0.0f);
  glEnd();

  glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  //glTranslatef(-250.0f, -40.0f,-520.0);
  glTranslatef(baseX+150.0f, -40.0f,baseZ-20.0);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
  glLineWidth(2.5);
  glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,0.0f); //color negro
    glVertex3f(0.0f,0.0f, -5.0f);
    glVertex3f(0.0f,-1.0f, 40.0f);
  glEnd();

//Cejas
  glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  //glTranslatef(-250.0f, 120.0f,-500.0);
  glTranslatef(baseX+150.0f, 120.0f,baseZ);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
  glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f,0.0f); //color azul
    glVertex3f(0.0f,0.0f, 3.0f);
    glVertex3f(0.0f,10.0f, 55.0f);
    glVertex3f(0.0f, 0.0f, 60.0f);
  glEnd();

  glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  //glTranslatef(-250.0f, 120.0f,-510.0);
  glTranslatef(baseX+150.0f, 120.0f,baseZ-10.0);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
  glRotatef(-180, 1.0, 0.0,0.0);
  glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f,0.0f); //color negro
    glVertex3f(0.0f,0.0f, 3.0f);
    glVertex3f(0.0f,10.0f, 55.0f);
    glVertex3f(0.0f, 0.0f, 60.0f);
  glEnd();
//CINTURON
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-350.0f,-395.0f,-500);
  glTranslatef(baseX+50.0f,-395.0f,baseZ);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
  glRotatef (90.0, 1.0f, 0.0f, 0.0f);
  glColor3f(0.4f,0.2f,0.0f);
	glutSolidTorus(15,92, 150, 100);

	//PINTA BRAZOS izquierdo ARRIBA
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-350.0,-120, -390.0);
  glTranslatef(baseX+50.0,-120, baseZ+110.0);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
	glRotatef (85.0, 1.0f, 0.0f, 0.0f);
	glRotatef (-20.0, 0.0f, 1.0f, 0.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glColor3f(1.0f,0.0f,0.0f);
	GLUquadricObj *cylind2 = gluNewQuadric();
	gluQuadricDrawStyle (cylind2, GLU_LINE);
	gluCylinder (cylind2, 15, 15,100, 100, 100);
	//Brazo izquierdo ABAJO
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-350.0,-235, -380.0);
  glTranslatef(baseX+50.0,-235, baseZ+120.0);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
	glRotatef (90.0, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f,0.0f,0.0f);
	GLUquadricObj *cylind4 = gluNewQuadric();
	gluQuadricDrawStyle (cylind4, GLU_LINE);
	gluCylinder (cylind4, 15, 15,100, 100, 100);
	//Brazo derecha ARRIBA
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-350.0,-120, -620.0);
  glTranslatef(baseX+50.0,-120, baseZ-120.0);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
	glRotatef (95.0, 1.0f, 0.0f, 0.0f);
	glRotatef (5.0, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f,0.0f,0.0f);
	GLUquadricObj *cylind3 = gluNewQuadric();
	gluQuadricDrawStyle (cylind3, GLU_LINE);
	gluCylinder (cylind3, 15, 15,100, 100, 100);
	// Brazo derecho ABAJO
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	//glTranslatef(-350.0,-235, -630.0);
  glTranslatef(baseX+50.0,-235, baseZ-130.0);
	glTranslatef(p0.x/3.62, p0.z/2.5, p0.y/1.9);
	glRotatef (90.0, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f,0.0f,0.0f);
	GLUquadricObj *cylind5 = gluNewQuadric();
	gluQuadricDrawStyle (cylind5, GLU_LINE);
	gluCylinder (cylind5, 15, 15,100, 100, 100);
	//Rodilla Izquierda
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glPointSize(3.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	Punto p4 = puntos[LKNE][momento];
	glTranslatef(baseX,-380, baseZ);
	glBegin(GL_POINTS);
	glVertex3f((p4.x/3.62), p4.z/2.5, p4.y/1.9);
	glEnd();
	//Rodilla DERECHO

	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glPointSize(3.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	Punto p5 = puntos[RKNE][momento];
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	glBegin(GL_POINTS);
	glVertex3f((p5.x/3.62), p5.z/2.5, p5.y/1.9);
	glEnd();
	//Union muslo y rodilla Izquierda
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glLineWidth(10.0f);
	glColor3f(0.0f, 0.2f, 0.8f);
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	renderCylinder_convenient(p2.x/3.62, p2.z/2.5, p2.y/1.9,p4.x/3.62, p4.z/2.5, p4.y/1.9, radioPiernas,50);
	//Union muslo y rodilla derecha
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glLineWidth(10.0f);
	glColor3f(0.0f, 0.2f, 0.8f);
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	renderCylinder_convenient(p3.x/3.62, p3.z/2.5, p3.y/1.9,p5.x/3.62, p5.z/2.5, p5.y/1.9, radioPiernas,50);
	//Canilla IZQUIEDA

	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glPointSize(3.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	Punto p6 = puntos[LTIB][momento];
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	glBegin(GL_POINTS);
	glVertex3f((p6.x/3.62), p6.z/2.5, p6.y/1.9);
	glEnd();
	//Canilla DERECHA

	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glPointSize(3.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	Punto p7 = puntos[RTIB][momento];
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	glBegin(GL_POINTS);
	glVertex3f((p7.x/3.62), p7.z/2.5, p7.y/1.9);
	glEnd();
	//Union rodilla y canilla Izquierda
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glLineWidth(10.0f);
	glColor3f(0.0f, 0.2f, 0.8f);
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	renderCylinder_convenient(p4.x/3.62, p4.z/2.5, p4.y/1.9,p6.x/3.62, p6.z/2.5, p6.y/1.9, radioPiernas,50);
	//Union rodilla y canilla derecha
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glLineWidth(10.0f);
	glColor3f(0.0f, 0.2f, 0.8f);
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	renderCylinder_convenient(p5.x/3.62, p5.z/2.5, p5.y/1.9,p7.x/3.62, p7.z/2.5, p7.y/1.9, radioPiernas,50);
	//Tobillo IZQUIEDO

	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glPointSize(3.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	Punto p8 = puntos[LANK][momento];
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	glBegin(GL_POINTS);
	glVertex3f((p8.x/3.62), p8.z/2.5, p8.y/1.9);
	glEnd();
	//Tobillo DERECHO

	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glPointSize(3.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	Punto p9 = puntos[RANK][momento];
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	glBegin(GL_POINTS);
	glVertex3f((p9.x/3.62), p9.z/2.5, p9.y/1.9);
	glEnd();
	//Union canilla y tobillo Izquierda
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glLineWidth(10.0f);
	glColor3f(0.0f, 0.2f, 0.8f);
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	renderCylinder_convenient(p6.x/3.62, p6.z/2.5, p6.y/1.9,p8.x/3.62, p8.z/2.5, p8.y/1.9, radioPiernas,50);
	//
	//Union canilla y tobillo DERECHO
	glLoadIdentity();
	gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
	glLineWidth(10.0f);
	glColor3f(0.0f, 0.2f, 0.8f);
	//glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
	renderCylinder_convenient(p7.x/3.62, p7.z/2.5, p7.y/1.9,p9.x/3.62, p9.z/2.5, p9.y/1.9, radioPiernas,50);
  // TOE IZQUIEDo
  glLoadIdentity();
  gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  glPointSize(3.0f);

  glColor3f(0.0f, 1.0f, 1.0f);
  Punto p10 = puntos[LTOE][momento];
  //glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
  glBegin(GL_POINTS);
  glVertex3f((p10.x/3.62), p10.z/2.5, p10.y/1.9);
  glEnd();
  // TOE DERECHO
  glLoadIdentity();
  gluLookAt(CamaraP1X, CamaraP1Y, CamaraP1Z, CamaraP2X , CamaraP2Y, CamaraP2Z, CamaraEjeX, CamaraEjeY, CamaraEjeZ);
  glPointSize(3.0f);

  glColor3f(0.0f, 1.0f, 1.0f);
  Punto p11 = puntos[RTOE][momento];
  //glTranslatef(-400.0,-380, -500);
  glTranslatef(baseX,-380, baseZ);
  glBegin(GL_POINTS);
  glVertex3f((p11.x/3.62), p11.z/2.5, p11.y/1.9);
  glEnd();
  if (momento <= 112 && activo) {
    ++momento;

  }
  gluDeleteQuadric (cylind1);
  gluDeleteQuadric (cylind2);
  gluDeleteQuadric (cylind3);
  gluDeleteQuadric (cylind4);
  gluDeleteQuadric (cylind5);
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
               // Reset the projection matrix
   glLoadIdentity();
   /*gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);*/
	gluPerspective(80.0f,(GLfloat)width/(GLfloat)height,0.1,2500.0f);
  //glMatrixMode(GL_MODELVIEW);

}

int caminando = 0;
void updateFrame() {
      // this is called before each frame of the animation.
   frameNumber++;
}

void timerFunction(int timerID) {
    //if (caminando) {
      //  updateFrame();
        glutPostRedisplay();
        glutTimerFunc(30, timerFunction, 0);
    //}
}

void comenzarAnimacion() {
   if (!caminando) {
       caminando = 1;
       glutTimerFunc(30, timerFunction, 0);
   }
}

void pausarAnimacion() {
    caminando = 0;
}

void key(unsigned char ch, int x, int y) {
			switch (ch){
				case ' ':
					if ( activo )
		   			activo = false;
					else
		   			activo = true;
				break;
				case 'R': case 'r':
						momento =0;
				break;
				case 'A': case 'a':
	   			actualizarCamara(-1);
					//CamaraP1Z += 100;
					display();
					//momento--;
				break;
				case 'D': case 'd':
	   			actualizarCamara(1);
					//CamaraP1Z -= 100;
					display();
					//momento--;
				break;
				case 'W': case 'w':
	   			pausarAnimacion();
					CamaraP1Y += 10;
					display();
					momento--;
				break;
				case 'S': case 's':
	   			pausarAnimacion();
					CamaraP1Y -= 10;
					display();
					momento--;
				break;
			}
}


void idle() {
    display();
}


int main(int argc, char ** argv) {
	char nombre[50];
	std::cout<<"Nombre del archivo: ";
	//std::cin>>nombre;

  leerArchivo(nombre);
  glutInit(&argc, argv);            // Initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
  //glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
  glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
  glutCreateWindow(title);      // Create window with given title
  glutDisplayFunc(display);     // Register callback handler for window re-paint
	glutKeyboardFunc(key);
  glutReshapeFunc(reshape);     // Register callback handler for window re-shape
	frameNumber = 0;
  initGL();
	glutTimerFunc(0,timerFunction,0);
	//glutIdleFunc(idle);
  //initGL();                     // Our own OpenGL initialization
  glutMainLoop();               // Enter event-processing loop
  return 0;
}
