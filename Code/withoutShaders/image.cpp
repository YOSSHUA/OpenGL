/// this code will need Freeglut and glew libraries
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <utility>
#include <stdlib.h>
#include <vector>

// Colores

#define negro 0.0, 0.0, 0.0
#define blanco 1.0, 1.0, 1.0
#define grisClaro 0.9, 0.9, 0.9
#define grisOsc 0.2, 0.2, 0.2
#define grisPalido 0.878, 0.867, 0.729
#define grisCopa  0.467, 0.471, 0.443
#define azulFuerte 0.004, 0.588, 0.663
#define azulOsc 0, 0.224, 0.541
#define azulMedio 0.275, 0.569, 0.812
#define azulClaro 0.624, 0.859, 0.878
#define azulArriba 0.533, 0.714, 0.82
#define azulVerdoso 0.231, 0.38, 0.51
#define azulPalido 0.631, 0.776, 0.788
#define cafeOsc 0.478, 0.318, 0.086
#define cafeClaro 0.702, 0.478, 0.063
#define beige 0.98, 0.949, 0.863
#define amarilloDescolorido 0.722, 0.616, 0.231
#define amarillo 0.91, 0.729, 0.075
#define verdeAguaPalido 0.616, 0.753, 0.761





const int ww = 520, wh = 780;
const double pi = 3.14159265359;
using namespace std;

typedef vector<pair<double, double>> vpto;

//  Coordenadas para las curvas de Bezier

GLfloat pGuitarUp1[3][3] = { {-0.8,0.9,0.0}, {-0.42,0.85,0.0} , {-0.63,0.58,0.0} };
GLfloat pGuitarDown1[4][3] = { {-0.63,0.58,0.0} ,  {-0.34,0.42,0.0} ,{-0.36,0.1,0.0}, {-0.8,0.1,0.0} };
GLfloat pGuitarUp2[3][3] = { {-0.1,0.5,0.0}, {0.35,0.5,0.0} , {0.17,0.18,0.0} };
GLfloat pGuitarDown2[4][3] = { {0.17,0.18,0.0},  {0.41,0.02,0.0} ,{0.45,-0.3,0.0}, {0.05,-0.3,0.0} };
GLfloat pGuitarUp3[3][3] = { {-0.1, .23,0.0}, {-0.63,0.275,0.0} , {-0.37,-0.09, 0.0} };
GLfloat pGuitarDown3[4][3] = { {-0.37,-0.09,0.0},  {-0.61, -0.25,0.0} ,{-0.65,-0.57,0.0}, {-0.25,-0.57,0.0} };


/*
	Dadas las coordenadas de dos puntos los une con una línea
*/
void linea(float x0, float y0, float x1, float y1) {	

	glBegin(GL_LINES);
	glVertex2d(x0, y0);
	glVertex2d(x1, y1);
	glEnd();
}

/*
	Dadas las coordenadas de tres puntos dibuja un triángulo relleno
*/
void triangulo(float x0, float y0, float  x1, float y1, float x2, float y2) {
	glBegin(GL_TRIANGLES);
	glVertex2d(x0, y0);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}
/*
	Dado un vector de puntos une todos de dos en dos par formar una union continua de lineas
*/
void lineasUnidas(vpto puntos) {
	glBegin(GL_LINE_STRIP);
	int tam = puntos.size();
	for (int i = 0; i < tam; i++)
		glVertex2d(puntos[i].first, puntos[i].second);
	glEnd();
}
/*
	Dadas las coordenas de dos esquinas de un rectángulo(o cuadro) dibuja ese rectangulo relleno
*/
void cuadro(float x0, float y0, float  x1, float y1) {
	glBegin(GL_QUADS);
	glVertex2d(x0, y0);
	glVertex2d(x0, y1);
	glVertex2d(x1, y1);
	glVertex2d(x1, y0);
	glEnd();
}
/*
	Dadas las coordenas de dos esquinas de un rectángulo(o cuadro) dibuja los lados de ese rectangulo
*/
void lineasCuadro(float x0, float y0, float  x1, float y1) {
	
	glBegin(GL_LINE_STRIP);
	glVertex2d(x0, y0);
	glVertex2d(x0, y1);
	glVertex2d(x1, y1);
	glVertex2d(x1, y0);
	glEnd();
}

/*
	Dado el conjunto de puntos de 3 coordenadas y el número de puntos, dibuja la curva de bezier 
*/
void curva(int numPtos, GLfloat ptos[][3]) {
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, numPtos, &ptos[0][0]);
	glEnable(GL_MAP1_VERTEX_3);

	glBegin(GL_LINE_STRIP);
	int i;
	for (i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat)i / 30.0);
	glEnd();

	glDisable(GL_MAP1_VERTEX_3);
}

/*
	Dado un conjunto de puntos dibuj el poligoo convexo relleno que se forma. Los puntos deben darse en orden.
*/
void poligono(vpto ptos) {
	glBegin(GL_POLYGON);
	int tam = ptos.size();
	for (int i = 0; i < tam; i++)
		glVertex2d(ptos[i].first, ptos[i].second);
	glEnd();
}
/*
	Dado el centro, radio y grosor de una circunferencia la dibuja.
*/
void drawCircle(float x, float y, float radius, float thickness)
{
	const int numOfPoints = 100;
	const float pi2 = 6.28318530718; // = 2.0*M_PI
	const float da = pi2 / numOfPoints;
	float a, r0 = radius - 0.5 * thickness, r1 = radius + 0.5 * thickness, c, s;
	int e;
	glBegin(GL_QUAD_STRIP);
	for (e = 1, a = 0.0; e; a += da)
	{
		if (a >= pi2) { e = 0; a = pi2; }
		c = cos(a); s = sin(a);
		glVertex2f(c * r0 + x, s * r0 + y);
		glVertex2f(c * r1 + x, s * r1 + y);
	}
	glEnd();
}
/*
	Dado el centro y el radio de un círculo lo dibuja.
*/
void fillCircle(float r, float x, float y) {
	float i = 0.0f;

	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(x, y); // Center
	for (i = 0.0f; i <= 360; i++)
		glVertex2f(r * cos( pi* i / 180.0) + x, r * sin(pi * i / 180.0) + y);

	glEnd();
}

/*
	A falta de Boundary Fill se "Poligonizó" el área encerrada por curvas de Bezier de la guitarra cafe.
*/
void colorearGuitarCafe() {
	vpto ptos;
	// marcas de la guitarra
	glColor3f(cafeOsc);
	cuadro(-0.25, 0.23, -0.1, 0.35);
	// relleno guitarra cafe del cuadro
	ptos.clear();
	ptos.push_back(make_pair(0.1, -0.29));
	ptos.push_back(make_pair(-0.05, -0.29));
	ptos.push_back(make_pair(-0.05, -0.15));
	ptos.push_back(make_pair(0.1, -0.1));
	poligono(ptos);

	ptos.clear();	
	ptos.push_back(make_pair(0.1, 0.18)); // ab izq
	ptos.push_back(make_pair(0.1, 0.48)); // ar izq
	ptos.push_back(make_pair(0.16, 0.450));
	ptos.push_back(make_pair(0.18, 0.43));
	ptos.push_back(make_pair(0.2, 0.42));
	ptos.push_back(make_pair(0.21, 0.39));
	ptos.push_back(make_pair(0.22, 0.35)); // ar der/ intersec con linea cuadro
	ptos.push_back(make_pair(0.215, 0.27));
	ptos.push_back(make_pair(0.2, 0.25));
	ptos.push_back(make_pair(0.17, 0.18)); // intersec con ini curvaUp2
	poligono(ptos);

	ptos.clear();
	ptos.push_back(make_pair(0.1, -0.29)); // ab izq
	ptos.push_back(make_pair(0.1, 0.18)); // ar izq
	ptos.push_back(make_pair(0.17, 0.18)); // intersec con ini curvaUp2
	ptos.push_back(make_pair(0.235, 0.13)); // intermedio
	ptos.push_back(make_pair(0.3, 0.05)); 
	ptos.push_back(make_pair(0.335, -0.02)); // intermedio
	ptos.push_back(make_pair(0.35, -0.1));
	ptos.push_back(make_pair(0.34, -0.165)); // intermedio
	ptos.push_back(make_pair(0.33, -0.19)); // intermedio
	ptos.push_back(make_pair(0.31, -0.22));
	ptos.push_back(make_pair(0.26, -0.25)); // intermedio
	ptos.push_back(make_pair(0.235, -0.27)); // intermedio con el primero
	ptos.push_back(make_pair(0.17, -0.29)); // intermedio
	ptos.push_back(make_pair(0.1, -0.3));

	poligono(ptos);

}
/*
	A falta de Boundary Fill se "Poligonizó" el área encerrada por curvas de Bezier de la guitarra anarilla.
*/
void colorearGuitarAma() {
	vpto ptos;
	// marcas de la guitarra
	glColor3f(amarillo);
	ptos.push_back(make_pair(-0.25, -0.35)); // ab der
	ptos.push_back(make_pair(-0.25, -0.09)); // ar der
	ptos.push_back(make_pair(-0.37, -0.09));  // ar izq 	
	ptos.push_back(make_pair(-0.47, -0.175)); // inter ar- izq y ab-izq
	ptos.push_back(make_pair(-0.51, -0.22)); //inter ar- izq y ab-izq
	ptos.push_back(make_pair(-0.55, -0.35)); // ab izq
	poligono(ptos);

	ptos.clear();
	ptos.push_back(make_pair(-0.37, -0.09));  // ab izq 
	ptos.push_back(make_pair(-0.25, -0.09)); // ab der
	ptos.push_back(make_pair(-0.25, 0.23)); // ar der
	ptos.push_back(make_pair(-0.31, 0.23));  //inter ar-der, ar izq
	ptos.push_back(make_pair(-0.37, 0.21)); // ar izq
	ptos.push_back(make_pair(-0.425, 0.185));  
	ptos.push_back(make_pair(-0.45, 0.13)); 
	ptos.push_back(make_pair(-0.45, 0.06));  //inter ar izq , ab izq
	poligono(ptos);

}
/*
	Procedimiento para rellenar dos rectángulos
*/
void rellenarFig() {
	glColor3f(negro);
	glRectf(-0.75, -0.63, -0.25, -0.35); // ar
	glRectf(-0.75, -0.63, -0.1, -0.57); // ABAJO
	
}
/*
	Procedimiento para rellenar Guitarra azul de la izquiera a falta de Boundary Fill
*/
void rellenarGuitarIzq() {
	glColor3f(verdeAguaPalido);
	glRectf(-0.8, 1.0, -1.0, 0.9);
	vpto ptos;
	ptos.push_back(make_pair(-0.63, 0.58)); // ab der
	ptos.push_back(make_pair(-0.575, 0.66)); // INTER
	ptos.push_back(make_pair(-0.555, 0.75)); 
	ptos.push_back(make_pair(-0.57, 0.81)); // inter
	ptos.push_back(make_pair(-0.63, 0.85)); // ar  de ab-der
	ptos.push_back(make_pair(-0.71, 0.885)); // inter
	ptos.push_back(make_pair(-0.8, 0.9)); // ar der
	ptos.push_back(make_pair(-1.0, 0.9)); //ar izq 
	ptos.push_back(make_pair(-1.0, 0.58)); //ab izq 
	poligono(ptos);

	ptos.clear();
	ptos.push_back(make_pair(-1.0, 0.58)); //ar izq 
	ptos.push_back(make_pair(-0.63, 0.58)); // ar der
	ptos.push_back(make_pair(-0.55, 0.53)); // inter
	ptos.push_back(make_pair(-0.5, 0.48)); // ab der
	ptos.push_back(make_pair(-1.0, 0.35)); // ab izq
	poligono(ptos);

}

/*
	Procedimiento que dibuja los puntos en medio del cuadro por medio de un patrón y de lineas.
*/
GLint factor = 1;
GLushort patron = 0x1818;
void dibujarPuntos() {
	glColor3f(negro);
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(3);
	glLineStipple(factor, patron);

	glBegin(GL_LINE_STRIP); // G
	glVertex2f(-0.1, 0.48); // ar izq
	glVertex2f(0.25, 0.63); // ar der
	glVertex2f(0.53, 0.2); // ab der
	glVertex2f(0.15, 0.05); // ab izq
	glVertex2f(-0.05, 0.45); // ar izq
	glVertex2f(0.22, 0.6); // ar der
	glVertex2f(0.48, 0.21); // ab der
	glVertex2f(0.2, 0.08); // ab izq
	glVertex2f(0.0, 0.42); // ar izq
	glVertex2f(0.19, 0.56); // ar der
	glVertex2f(0.43, 0.2); // ab der
	glVertex2f(0.3, 0.11); // ab izq
	glVertex2f(0.1, 0.45); // ar izq
	glVertex2f(0.18, 0.52); // ar der
	glVertex2f(0.38, 0.23); // ab der
	glVertex2f(0.33, 0.21); // ab izq
	glVertex2f(0.16, 0.5); // ar izq
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1);
}

/*
	Procedimiento principal de pintado.
	El coloreado está ordenado de tal forma que hay figuras que se sobreponen( y otras que no) para poder simular las figuras que se presentan en la imagen original.
	La mayor parte está comentada según la figura que pinta.
*/
void display(void) {
	glClearColor(beige, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	rellenarFig();
	rellenarGuitarIzq();

	// circulos para simular 1/4 de circ de guitar inf izq
	glColor3f(azulFuerte);
	fillCircle(.22, -0.25, -0.35);
	fillCircle(.22, -0.28, -0.35);
	fillCircle(.22, -0.3, -0.35);
	fillCircle(.22, -0.32, -0.34);
	fillCircle(.22, -0.33, -0.34);
	fillCircle(.22, -0.34, -0.34);

	//romboide de la parte inferior derecha
	vpto ptos;
	glColor3f(amarilloDescolorido);
	ptos.push_back(make_pair(0.1, -0.515)); // izq ab
	ptos.push_back(make_pair(0.1, -0.08)); // izq ar
	ptos.push_back(make_pair(0.62, -0.28)); // der ar 
	ptos.push_back(make_pair(0.62, -0.77)); // der ab
	poligono(ptos);
	
	// figura amarilla arriba de triangulo negro del cuadro
	ptos.clear();
	ptos.push_back(make_pair(-0.25, 0.435)); // der ab
	ptos.push_back(make_pair(-0.25, 0.56)); // der ar
	ptos.push_back(make_pair(-0.51, 0.485)); // izq ar
	ptos.push_back(make_pair(-0.462, 0.425)); // inter
	ptos.push_back(make_pair(-0.445, 0.35)); // izq ab
	poligono(ptos);


	glColor3f(azulArriba);
	triangulo(0.62, -0.28, 0.62, -0.77, 0.8 ,-0.35);

	glColor3f(grisOsc);
	// medio circulo derecha arriba 1
	fillCircle(0.2325, 0.87, 0.4525);

	glColor3f(azulArriba);
	// media circunferencia derecha arriba 1
	fillCircle(0.21, 0.87, 0.4525);


	glColor3f(beige);
	glRectf(0.9, 1, 1, -1);
	triangulo(0.87, 0.84, 0.9, 0.24, 0.92, 0.84);
	// poligono para simular parte de circunferencia azul sup der
	ptos.clear();			
	ptos.push_back(make_pair(0.78, 0.64));
	ptos.push_back(make_pair(0.8, 0.65));
	ptos.push_back(make_pair(0.82, 0.66));
	ptos.push_back(make_pair(0.9, 0.666));
	ptos.push_back(make_pair(0.9, 0.24));
	ptos.push_back(make_pair(0.82, 0.25));
	ptos.push_back(make_pair(0.8, 0.25));
	ptos.push_back(make_pair(0.78, 0.27));	
	poligono(ptos);

	glColor3f(negro);
	dibujarPuntos();

	// linea de abajo del circ derecho
	linea(0.9, 0.24, 0.9, -0.12);

	// linea de arriba del circ derecho
	linea(0.87, 0.665, 0.87, 0.84);

	// Lineas triangulos
	ptos.clear();
	ptos.push_back(make_pair(0.87, 0.84)); // ar
	ptos.push_back(make_pair(0.8, 0.79)); // ab
	ptos.push_back(make_pair(0.715, 0.84)); // ar
	ptos.push_back(make_pair(0.64, 0.79)); // ab
	ptos.push_back(make_pair(0.56, 0.83)); // ar
	ptos.push_back(make_pair(0.50, 0.79)); // ab
	ptos.push_back(make_pair(0.445, 0.83)); // ar
	ptos.push_back(make_pair(0.38, 0.79)); // ab
	ptos.push_back(make_pair(0.33, 0.83)); // ar
	ptos.push_back(make_pair(0.26, 0.79)); // ab
	ptos.push_back(make_pair(0.185, 0.835)); // ar
	ptos.push_back(make_pair(0.13, 0.79)); // ab
	lineasUnidas(ptos);


	// Rectangulo azul der dentro de cuadro 
	glColor3f(azulMedio);
	glRectf(0.1, 0.35, 0.4, -0.35);	

	// rect azul izq dentro de cuadro
	glColor3f(azulClaro);
	glRectf(-0.8, 0.35, -0.25, -0.35);

	glColor3f(negro);
	// linea sup izq guitarra
	linea(-0.8, 1.0, -0.8, 0.9);

	// guitarra sup sup izq mitad
	curva(3, pGuitarUp1);

	// guitarra sup inf izq mitad
	curva(4, pGuitarDown1);

	//linea que une guitarrra a izq
	linea(-0.8, 0.1, -1.0, 0.095);

	// triangulos del cuadro 
	glColor3f(azulFuerte);
	triangulo(-0.8, 0.2, -0.8, 0.35, -0.44, 0.35); // triang sup izq
	glColor3f(azulOsc);
	triangulo(0.4, -0.35, 0.4, -0.22, 0.28, -0.35);// triangulo inf der
	glColor3f(negro);
	triangulo(-0.25, 0.35, -0.45, 0.35, -0.25, 0.435); // triangulo negro que esta arriba del cuadro		
	
	// rectangulo vertical medio del cuadro
	glColor3f(beige);
	glRectd(-0.25, 0.345, 0.1, -0.57);


	glColor3f(negro);

	// rectangulo horizontal de abajo de guitarra 
	glRectd(-0.25, -0.35, 0.1, -0.29);	

	

	// linea abajo de rectangulo hor 
	glLineWidth(4);
	linea(-0.25, -0.45, 0.1, -0.45);

	// linea vertical que conecta con rectan hor de git
	glColor3f(grisOsc);
	linea(0.1, -0.35, 0.1, -0.515);
	
	glColor3f(negro);
	glLineWidth(1);
	// linea de cuadrado	
	linea(-0.8, 0.35, -0.1, 0.35); // ar izq
	linea(-0.1, 0.345, 0.1, 0.345); // ar en medio
	linea(0.22, 0.35, 0.4, 0.35); // ar der
	linea(0.4, 0.345, 0.4, -0.35); // der
	linea(0.4, -0.35, -0.8, -0.35); // ab
	linea(-0.8, -0.35, -0.8, 0.35); // izq
	 
	// media circunferencia negra arriba
	drawCircle(-0.09, 0.12, 0.05,0.005);

	// Rectangulo vertical negro que tiene cuerdas
	glRectd(-0.25, -0.16, -0.1, 0.24);

	//cuerdas
	glColor3f(beige);
	linea(-0.22, 0.23, -0.22, -0.1);	
	linea(-0.19, 0.23, -0.19, -0.1);
	linea(-0.16, 0.23, -0.16, -0.1);
	linea(-0.13, 0.23, -0.13, -0.1);


	glColor3f(negro);
	// circulo negro para simular medio circ
	fillCircle(0.09, -0.147, -0.085);
	
	// Rectangulo para simular media circ
	glColor3f(beige);
	glRectd(-0.25, -0.085, 0.1, -0.25);

	//circ interna negra
	glColor3f(negro);
	drawCircle(-0.147, -0.09, .1, .01);
	// cir beige
	glColor3f(beige);
	drawCircle(-0.147, -0.09, 0.09, 0.01);

	colorearGuitarCafe();
	colorearGuitarAma();

	//lineas de la marca de la guitarra
	glColor3f(negro);
	lineasCuadro(-0.25, 0.32, -0.1, 0.35);
	lineasCuadro(-0.25, 0.29, -0.1, 0.32);
	lineasCuadro(-0.25, 0.26, -0.1, 0.29);
	lineasCuadro(-0.25, 0.23, -0.1, 0.26);
	
	// lineas que llegan hasta abajo
	linea(-0.215, -0.085, -0.215, -0.5);
	linea(-0.17, -0.085, -0.17, -0.49);
	linea(-0.13, -0.085, -0.13, -0.48);
	linea(-0.09, -0.085, -0.09, -0.47);
	
	// Linea antes del rectangulo azul para parte superior
	linea(-0.45, 0.5, -0.45, 1.0);

	// Poligono para colorear parte superior de guitarra
	vpto ptosG;
	glColor3f(cafeClaro);
	ptosG.push_back(make_pair(-.295, 0.545));
	ptosG.push_back(make_pair(-0.295, 0.885));
	ptosG.push_back(make_pair(-0.1, 0.9));
	ptosG.push_back(make_pair(-0.1, 0.595));
	poligono(ptosG);
	

	// rectangulo para colorear de azul arriba
	glColor3f(azulArriba);
	triangulo(-0.25, 0.555, -0.45, 0.5, -0.45, 0.555);
	glRectf(-0.45, 0.555, -0.25, 1.0);
	

	// para compensar azul
	glColor3f(cafeClaro);
	glRectf(-0.295, 0.89, -0.25, 0.7);
	triangulo(-0.295, 0.885, -0.235, 0.92, -0.22, 0.9);
	triangulo(-0.295, 0.885, -0.235, 0.92, -0.2, 0.885);
	triangulo(-0.22, 0.9, -0.18, 0.925, -0.155, 0.9);
	glRectf(-0.1, 0.9, -0.235, 0.88);
	triangulo(-0.155, 0.9, -0.135, 0.925, -0.1, 0.9);

	// linea guitarra hacia arriba
	glColor3f(negro);
	linea(-0.1, 0.35, -0.1, 0.9);
	linea(-0.25, 0.35, -0.25, 0.7);
	
	glColor3f(negro);
	// detalles guitarra arriba
	/// parte que esta por los 3 ajustadores
	ptosG.clear();
	ptosG.push_back(make_pair(-0.25, 0.695)); // ar der
	ptosG.push_back(make_pair(-0.34, 0.76)); // arr izq
	ptosG.push_back(make_pair(-0.375, 0.68)); // ab izq
	ptosG.push_back(make_pair(-0.25, 0.66)); // ab der
	poligono(ptosG);

	triangulo(-.295, 0.7275, -0.295, 0.89, -0.34, 0.761);

	// lineas de los triangulos de la parte sup de la gitarra
	linea(-0.295, 0.88, -0.235, 0.92);
	linea(-0.235, 0.92, -0.22, 0.9);
	linea(-0.22, 0.9, -0.18, 0.925);
	linea(-0.18, 0.925, -0.155, 0.9);
	linea(-0.155, 0.9, -0.135, 0.925);
	linea(-0.135, 0.925, -0.1, 0.9);

	// puntos de la guitarra

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(-0.25, 0.755);
	glEnd();
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(-0.25, 0.805);
	glEnd();
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(-0.25, 0.855);
	glEnd();


	// ajustador abajo
	//parte derecha
	ptosG.clear();
	ptosG.push_back(make_pair(-0.34, 0.745)); // ab der
	ptosG.push_back(make_pair(-0.333, 0.765)); // ar der
	ptosG.push_back(make_pair(-0.375, 0.765)); // ar izq
	ptosG.push_back(make_pair(-0.39, 0.745)); // ab izq
	poligono(ptosG);
	//parte izquierda
	ptosG.clear();
	ptosG.push_back(make_pair(-0.365, 0.775)); // ar der
	ptosG.push_back(make_pair(-0.395, 0.735)); // ab der
	ptosG.push_back(make_pair(-0.42, 0.735)); // ab izq
	ptosG.push_back(make_pair(-0.39, 0.775)); // ar izq
	poligono(ptosG);

	//ajustador medio
	//parte derecha
	ptosG.clear();
	ptosG.push_back(make_pair(-0.31, 0.795)); // ab der
	ptosG.push_back(make_pair(-0.303, 0.815)); // ar der
	ptosG.push_back(make_pair(-0.345, 0.815)); // ar izq
	ptosG.push_back(make_pair(-0.36, 0.795)); // ab izq
	poligono(ptosG);
	//parte izquierda
	ptosG.clear();
	ptosG.push_back(make_pair(-0.335, 0.825)); // ar der
	ptosG.push_back(make_pair(-0.365, 0.785)); // ab der
	ptosG.push_back(make_pair(-0.39, 0.785)); // ab izq
	ptosG.push_back(make_pair(-0.36, 0.825)); // ar izq
	poligono(ptosG);

	//ajustador arriba
	//parte derecha
	ptosG.clear();
	ptosG.push_back(make_pair(-0.3, 0.845)); // ab der
	ptosG.push_back(make_pair(-0.295, 0.865)); // ar der
	ptosG.push_back(make_pair(-0.315, 0.865)); // ar izq
	ptosG.push_back(make_pair(-0.33, 0.845)); // ab izq
	poligono(ptosG);
	//parte izquierda
	ptosG.clear();
	ptosG.push_back(make_pair(-0.305, 0.875)); // ar der
	ptosG.push_back(make_pair(-0.335, 0.835)); // ab der
	ptosG.push_back(make_pair(-0.36, 0.835)); // ab izq
	ptosG.push_back(make_pair(-0.33, 0.875)); // ar izq
	poligono(ptosG);


	// lineas inclinadas que cruzan a la mitad del cuadro
	linea(-0.8, 0.2, -0.1, 0.5); // m > 0 abajo
	linea(-0.1, 0.5, 0.3, 0.67); // m> 0 abajo
	linea(-0.92, 0.37, 0.28, 0.7); // m > 0 arriba
	linea(0.6, 0.18, 0.2, 0.73);// m < 0 derecha
	linea(0.6, 0.21, 0.4, 0.12); // intersecta con la de arriba y el cuadro
	
	// figura negra arriba de cuadro
	ptos.clear();
	ptos.push_back(make_pair(-0.1, 0.5));  // izq ar
	ptos.push_back(make_pair(-0.05, 0.5));  // ar
	ptos.push_back(make_pair(0.0, 0.5)); // en medio ar
	ptos.push_back(make_pair(0.01, 0.5));  // izq ar
	ptos.push_back(make_pair(0.1, 0.48)); // der ar
	ptos.push_back(make_pair(0.1, 0.345)); // der ab	
	ptos.push_back(make_pair(-0.1, 0.345)); // izq ab
	poligono(ptos);

	


	// guitarra medio der sup
	curva(3, pGuitarUp2);

	// guitarra medio der inf
	curva(4, pGuitarDown2);

	//guitarra medio izq sup
	curva(3, pGuitarUp3);

	// guitarra medio der inf
	curva(4, pGuitarDown3);

	// rectangulo con circulo azul

	//linea vertical izq inf
	linea(-0.75, -0.35, -0.75, -0.63);
	//linea abajo
	linea(-0.75, -0.63, -0.1, -0.63);
	// linea vertical der inf
	linea(-0.1, -0.63, -0.1, -0.575);
	// linea que conecta con guitarra
	linea(-0.1, -0.575, -0.25, -0.57);	

	

	//cuadro inf izq
	cuadro(-0.9, -0.74, -0.75, -0.63);

	// trapecio negro a lado de cuadro 
	ptos.clear();
	ptos.push_back(make_pair(0.4, 0.15)); // izq ar
	ptos.push_back(make_pair(0.4, -0.2)); // izq ab
	ptos.push_back(make_pair(0.53, -0.25)); // der ab
	ptos.push_back(make_pair(0.53, 0.185)); // der ar
	poligono(ptos);

	// trapecio negro para completar
	ptos.clear();
	ptos.push_back(make_pair(0.53, -0.25)); // izq ab
	ptos.push_back(make_pair(0.53, -0.1)); // izq ar
	ptos.push_back(make_pair(0.58, -0.1)); //der ar
	ptos.push_back(make_pair(0.58, -0.265)); // der ab
	poligono(ptos);
	
	
	// copa
	glColor3f(grisCopa);
	fillCircle(0.15, 0.58, -0.03);

	

	glColor3f(negro);
	// delineado copa

	drawCircle(0.58, -0.03, 0.15, 0.01);

	linea(0.43, 0.0, 0.72, -0.03);
	triangulo(0.53, 0.19, 0.53, -0.01, 0.40, 0.0);

	// Poligono para compensar copa
	glColor3f(beige);
	ptos.clear();
	ptos.push_back(make_pair(0.53, -0.01)); //  izq ab
	ptos.push_back(make_pair(0.735, -0.03)); //  der ab
	ptos.push_back(make_pair(0.73, 0.15)); // der ar
	ptos.push_back(make_pair(0.53, 0.15)); //  izq ar
	poligono(ptos);


	// triangulo de hasta abajo der
	glColor3f(negro);
	triangulo(0.1, -0.515, 0.1, -0.8, 0.8, -0.8);
	
	glColor3f(beige);
	fillCircle(0.1, 0.2, -0.8);
	glRectf(0.2, -0.7, 0.0, -0.8);

	//copa parte 2
	glColor3f(grisCopa);
	fillCircle(0.065, 0.57, -0.37);

	glColor3f(negro);
	drawCircle(0.57, -0.37, 0.065, 0.005);

	glColor3f(grisCopa);
	glLineWidth(5);
	//boundaryFill4(95, 473,fillCol, borderCol );
	linea(0.58, -0.03, 0.58, -0.35);

	glColor3f(negro);
	glLineWidth(1);
	linea(0.57, -0.34, 0.57, -0.17);
	linea(0.59, -0.34, 0.59, -0.17);

	glColor3f(amarilloDescolorido);
	triangulo(0.568, -0.32, 0.45, -0.4, 0.568, -0.26);

	glColor3f(negro);
	linea(0.568, -0.32, 0.5, -0.365);
	glFlush();
}

void myinit()
{
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
	glMatrixMode(GL_MODELVIEW);
}

/*
	Programa principal que inicia la ventana y el ciclo de pintado.
*/
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(100, 100);
	myinit();
	glutCreateWindow("Tarea 3 Yosshua");
	glutDisplayFunc(display);	
	glutMainLoop();
	return 0;
}
