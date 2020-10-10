/// this code will need GLEW, GLFW libraries

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include <vector>


using namespace std;

const double pi = 3.14159265359;
float beige[3] = { 0.98, 0.949, 0.863 };
float negro[3] = { 0.0, 0.0, 0.0 };
float blanco[3] = { 1.0, 1.0, 1.0 };
float grisClaro[3] = { 0.9, 0.9, 0.9 };
float grisOsc[3] = { 0.2, 0.2, 0.2 };
float grisPalido[3] = { 0.878, 0.867, 0.729 };
float grisCopa[3] = { 0.467, 0.471, 0.443 };
float azulFuerte[3] = { 0.004, 0.588, 0.663 };
float azulOsc[3] = { 0, 0.224, 0.541 };
float azulMedio[3] = { 0.275, 0.569, 0.812 };
float azulClaro[3] = { 0.624, 0.859, 0.878 };
float azulArriba[3] = { 0.533, 0.714, 0.82 };
float azulVerdoso[3] = { 0.231, 0.38, 0.51 };
float azulPalido[3] = { 0.631, 0.776, 0.788 };
float cafeOsc[3] = { 0.478, 0.318, 0.086 };
float cafeClaro[3] = { 0.702, 0.478, 0.063 };
float amarilloDescolorido[3] = { 0.722, 0.616, 0.231 };
float amarillo[3] = { 0.91, 0.729, 0.075 };
float verdeAguaPalido[3] = { 0.616, 0.753, 0.761 };
/*
* The first line says which version of the shading language to use
* vertex shader has 1 input variable; a vec3 ,
which matches up to our VAO's attribute pointer.
The output has a reserved name gl_Position and expects a 4d float
 The 1 at the end just means "don't calculate any perspective".
 */
const int ww = 520, wh = 780;
const char* vertex_shader =
"#version 400\n"
"in vec3 vp;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"}";
/*
 fragment shader will run once per pixel-sized fragment
 that the surface of the shape covers. 
 */
const char* fragment_shader =
"#version 400\n"
"uniform vec3 my_color;"
"void main() {"
"gl_FragColor.rgb = my_color;"
"gl_FragColor.a = 1.0;"
"}";


const char* vertex_shaderBezierCubic =
"#version 400 core"
"in vec3 ini, ctrl1, ctrl2, fin;"
"vec3 toBezier(float t, vec3 P0, vec3 P1, vec3 P2, vec3 P3)"
"{"
    "float ax, bx, cx, ay, by, cy;"
    "float tSquared, tCubed;"
    "vec3 result = vec3(0.0, 0.0, 0.0);"
    "cx = 3.0 * (P1.x - P0.x);"
    "bx = 3.0 * (P2.x - P1.x) - cx;"
    "ax = P3.x - P0.x - cx - bx;"
    "cy = 3.0 * (P1.y - P0.y);"
    "by = 3.0 * (P2.y - P1.y) - cy;"
    "ay = P3.y - P0.y - cy - by;"
    "tSquared = t * t;"
    "tCubed = tSquared * t;"
    "result.x = (ax * tCubed) + (bx * tSquared) + (cx * t) + P0.x;"
    "result.y = (ay * tCubed) + (by * tSquared) + (cy * t) + P0.y;"
    "return result;"
"}"
"void main()"
"{"
    "float dt = 1 / 30.0;"
    "for (int t = 0; t < 30; t++) {"
        "gl_Position = vec4(vec3(toBezier(dt * t, ini, ctrl1, ctrl2, fin)), 1.0);"
    "}"
"}"
;
const char* vertex_shaderBezierCuadratic =
"#version 400 core"
"in vec3 ini, ctrl1, fin;"

"vec4 toBezier(float delta, int i, vec3 P0, vec3 P1, vec3 P2)"
"{"
"float t = delta * float(i);"
"float t2 = t * t;"
"float one_minus_t = 1.0 - t;"
"float one_minus_t2 = one_minus_t * one_minus_t;"
"return (P0 * one_minus_t2 + P1 * 2.0 * t * one_minus_t + P2 * t2 );"
"}"
"void main(){"
"float dt = 1/50.0"
"for(int t = 0; t < 50; t++){"
"gl_Position = vec4(vec3(toBezier(delta, t,ini, ctrl1, fin)), 1.0);"
"}"

"}"
;

float pGuitarUp1[21] = { -0.63, 0.58,0.0,   -0.575, 0.66,0.0,    -0.555, 0.75,0.0,    -0.57, 0.81,0.0,    -0.63, 0.85,0.0,   -0.71, 0.885,0.0,   -0.8, 0.9,0.0};
float pGuitarDown1[15] = { -0.63, 0.58,0.0,    -0.55, 0.53,0.0 ,   -0.5, 0.48,0.0, - 0.462, 0.425,0.0,   -0.445, 0.35,0.0 };
float pGuitarUp2[27] = {0.1, 0.48,0.0,0.16, 0.450,0.0,0.18, 0.43,0.0,0.2, 0.42,0.0,0.21, 0.39,0.0,0.22, 0.35,0.0,0.215, 0.27,0.0,0.2, 0.25,0.0,0.17, 0.18,0.0 };
float pGuitarDown2[36] = { 0.17, 0.18,0.0,0.235, 0.13,0.0 ,0.3, 0.05,0.0 ,0.335, -0.02,0.0,0.35, -0.1,0.0,0.34, -0.165,0.0 ,0.33, -0.19,0.0,0.31, -0.22,0.0,0.26, -0.25,0.0,0.235, -0.27,0.0	,0.17, -0.29,0.0,0.1, -0.3,0.0 };
float pGuitarUp3[21] = { -0.37, -0.09,0.0,    -0.45, 0.06,0.0,    -0.45, 0.13,0.0,   -0.425, 0.185,0.0,     -0.37, 0.21,0.0,    -0.31, 0.23,0.0,    - 0.25, 0.23,0.0};
float pGuitarDown3[18] = {    -0.37, -0.09,0.0,   -0.47, -0.175,0.0, -0.51, -0.22,0.0,   -0.55, -0.35,0.0, -0.25, -0.35,0.0, -0.25, -0.09,0.0 };
float rellenoGuitarAma1[18] = { -0.25, -0.35,0.0, -0.25, -0.09,0.0, -0.37, -0.09,0.0, -0.47, -0.175,0.0, -0.51, -0.22,0.0, -0.55, -0.35,0.0};
float rellenoGuitarAma2[24] = { -0.37, -0.09,0.0  ,-0.25, -0.09,0.0,-0.25, 0.23,0.0 ,-0.31, 0.23,0.0  ,-0.37, 0.21,0.0 ,-0.425, 0.185,0.0  ,-0.45, 0.13,0.0 ,-0.45, 0.06,0.0 };
float rellenoGuitarCafe1[12] = { -0.25, 0.23 ,0.0,   -0.25, 0.35, 0.0, -0.1, 0.35 ,0.0,  -0.1, 0.23, 0.0 };
float rellenoGuitarCafe2[12] = { 0.1, -0.29,0.0,-0.05, -0.29,0.0,-0.05, -0.15,0.0,0.1, -0.1,0.0 };
float rellenoGuitarCafe3[30] = { 0.1, 0.18,0.0,0.1, 0.48,0.0,0.16, 0.450,0.0,0.18, 0.43,0.0,0.2, 0.42,0.0,0.21, 0.39,0.0,0.22, 0.35,0.0,0.215, 0.27,0.0,0.2, 0.25,0.0,0.17, 0.18,0.0 };
float rellenoGuitarCafe4[42] = { 0.1, -0.29,0.0,0.1, 0.18,0.0,0.17, 0.18,0.0,0.235, 0.13,0.0 ,0.3, 0.05,0.0 ,0.335, -0.02,0.0,0.35, -0.1,0.0,0.34, -0.165,0.0 ,0.33, -0.19,0.0,0.31, -0.22,0.0,0.26, -0.25,0.0,0.235, -0.27,0.0	,0.17, -0.29,0.0,0.1, -0.3,0.0 };
float rectRellenarFig1[12] = { -0.75, -0.63,0.0, -0.25, -0.63,0.0, -0.25, -0.35,0.0, -0.75, -0.35, 0.0};
float rectRellenarFig2[12] = { -0.75, -0.63, 0.0, -0.1, -0.63,0.0, -0.1, -0.57, 0.0, -0.75, -0.57};
float rellGuitarIzq1[12] = { -0.8, 1.0, 0.0, -1.0, 1.0,0.0, -1.0, 0.9, 0.0,  -0.8, 0.9};
float rellGuitarIzq2[27] = { -0.63, 0.58,0.0,-0.575, 0.66,0.0,-0.555, 0.75,0.0,-0.57, 0.81,0.0,-0.63, 0.85,0.0,-0.71, 0.885,0.0,-0.8, 0.9,0.0,-1.0, 0.9,0.0,-1.0, 0.58,0.0 };
float rellGuitarIzq3[15] = { -1.0, 0.58,0.0 ,-0.63, 0.58,0.0,-0.55, 0.53,0.0 ,-0.5, 0.48,0.0  ,-1.0, 0.35,0.0 };
float punteado[51] = { -0.1, 0.48,0.0,0.25, 0.63,0.0,0.53, 0.2,0.0,0.15, 0.05,0.0,-0.05, 0.45,0.0,0.22, 0.6,0.0,0.48, 0.21,0.0,0.2, 0.08,0.0,0.0, 0.42,0.0,0.19, 0.56,0.0,0.43, 0.2,0.0,0.3, 0.11,0.0,0.1, 0.45,0.0,0.18, 0.52,0.0,0.38, 0.23,0.0,0.33, 0.21,0.0,0.16, 0.5,0.0 };
float romboideInfDer[12] = {0.1, -0.515,0.0,0.1, -0.08,0.0,0.62, -0.28,0.0,0.62, -0.77,0.0 };
float figAmarillaArriba[15] = { -0.25, 0.435,0.0,    -0.25, 0.56,0.0  ,-0.51, 0.485,0.0 ,   -0.462, 0.425,0.0  ,-0.445, 0.35,0.0 };
float triangAzulInfDer[9] = { 0.62, -0.28,0.0, 0.62, -0.77,0.0, 0.8 ,-0.35,0.0 };
float rectRight[12] = { 0.9, 1,0.0,   1.0, 1.0,0.0,   1.0, -1.0, 0.0,   0.9, -1.0, 0.0 };
float triangRightUp[9] = { 0.87, 0.84,0.0, 0.9, 0.24,0.0, 0.92, 0.84 ,0.0};
float fillPolygonRight[24] ={ 0.78, 0.64,0.0 ,0.8, 0.65,0.0 ,0.82, 0.66,0.0 ,0.9, 0.666,0.0 ,0.9, 0.24,0.0 ,0.82, 0.25,0.0 ,0.8, 0.25,0.0 ,0.78, 0.27,0.0 };
float triangSupDer[36] = { 0.87, 0.84 , 0.0, 0.8, 0.79 , 0.0, 0.715, 0.84 , 0.0, 0.64, 0.79, 0.0, 0.56, 0.83, 0.0, 0.50, 0.79, 0.0 , 0.445, 0.83,0.0, 0.38, 0.79, 0.0, 0.33, 0.83, 0.0, 0.26, 0.79 , 0.0, 0.185, 0.835, 0.0, 0.13, 0.79, 0.0};
float rectRellenoAzul1[12] = { 0.1, 0.35, 0.0,   0.4, 0.35, 0.0,   0.4, -0.35, 0.0,   0.1, -0.35, 0.0 };
float rectRellenoAzul2[12] = { -0.8, 0.35,0.0,  -0.25, 0.35, 0.0,  -0.25, -0.35, 0.0,   -0.8, -0.35, 0.0 };
float squareTriangs[3][9] = { {-0.8, 0.2,0.0, -0.8, 0.35,0.0, -0.44, 0.35,0.0},{0.4, -0.35, 0.0,  0.4, -0.22, 0.0,  0.28, -0.35, 0.0},{-0.25, 0.35, 0.0, -0.45, 0.35,0.0, -0.25, 0.435, 0.0} };
float verRect[12] = { -0.25, 0.345,0.0, -0.25,-0.57,0.0,  0.1, -0.57, 0.0,  0.1, 0.345, 0.0 };
float rectDown[12] = { -0.25, -0.35, 0.0,  -0.25, -0.29, 0.0,  0.1, -0.29, 0.0,   0.1, -0.35, 0.0 };
float midRect[12] = { -0.25, -0.16,0.0,   -0.25, 0.24,0.0,   -0.1, 0.24,0.0,   -0.1, -0.16, 0.0 };
float circRect[12] = { -0.25, -0.085,0.0,   -0.25,-0.25, 0.0,  0.1, -0.25, 0.0,    0.1, -0.085, 0.0 };
float lineasCuadro[4][12] = { {-0.25, 0.32,0.0,  -0.25, 0.35, 0.0,   -0.1, 0.35, 0.0,   -0.1,0.32, 0.0},{-0.25, 0.29,0.0,   -0.25, 0.32,0.0, -0.1, 0.32,0.0,   -0.1, 0.29, 0.0},{-0.25, 0.26, 0.0,  -0.25, 0.29,0.0,   -0.1, 0.29,0.0,    -0.1, 0.26,0.0}, {-0.25, 0.23,0.0,   -0.25, 0.26,0.0, -0.1, 0.26,0.0,  -0.1, 0.23, 0.0} };
float rellenoSupG[12] = { -.295, 0.545,0.0 ,-0.295, 0.885,0.0 ,-0.1, 0.9,0.0 ,-0.1, 0.595,0.0 };
float triangSupAzul[9] = { -0.25, 0.555, 0.0, -0.45, 0.5,0.0, -0.45, 0.555, 0.0};
float rectSupAzul[12] = { -0.45, 0.555,0.0,   -0.45, 1.0,0.0, -0.25, 1.0, 0.0,  -0.25, 0.555, 0.0};
float rectRellAzul[2][12] = { { -0.295, 0.89,0.0,  -0.295, 0.7, 0.0,  -0.25, 0.7, 0.0,   -0.25, 0.89, 0.0}, {-0.1, 0.9,0.0,  -0.1, 0.88,0.0,  -0.235, 0.88, 0.0,  -0.235, 0.9, 0.0} };
float triangRellAzul[4][9] = { {-0.295, 0.885,0.0, -0.235, 0.92,0.0, -0.22, 0.9, 0.0},{-0.295, 0.885, 0.0, -0.235, 0.92, 0.0, -0.2, 0.885, 0.0}, {-0.22, 0.9, 0.0, -0.18, 0.925, 0.0, -0.155, 0.9, 0.0} ,{-0.155, 0.9, 0.0, -0.135, 0.925,0.0, -0.1, 0.9, 0.0} };
float parteAjustador[12] = { -0.25, 0.695 , 0.0,-0.34, 0.76,0.0, -0.375, 0.68 ,0.0, -0.25, 0.66 ,0.0};
float triangAj[9] = { -.295, 0.7275,0.0, -0.295, 0.89,0.0, -0.34, 0.761, 0.0 };
float puntosAr[3][3] = { {-0.25, 0.755, 0.0},{ -0.25, 0.805 , 0.0},{ -0.25, 0.855 , 0.0 } };
float ajustadores[6][12] = { {-0.34, 0.745, 0.0, -0.333, 0.765, 0.0,-0.375, 0.765, 0.0, -0.39, 0.745, 0.0},{-0.365, 0.775, 0.0, -0.395, 0.735,0.0, -0.42, 0.735,0.0, -0.39, 0.775,0.0  },{-0.31, 0.795, 0.0, -0.303, 0.815, 0.0,-0.345, 0.815, 0.0, -0.36, 0.795,0.0 },{-0.335, 0.825, 0.0, -0.365, 0.785,0.0, -0.39, 0.785, 0.0, -0.36, 0.825, 0.0 },{-0.3, 0.845, 0.0, -0.295, 0.865, 0.0, -0.315, 0.865,0.0, -0.33, 0.845, 0.0},{-0.305, 0.875, 0.0, -0.335, 0.835, 0.0, -0.36, 0.835, 0.0,-0.33, 0.875, 0.0} };
float figNegra[21] = { -0.1, 0.5 , 0.0, -0.05, 0.5 , 0.0, 0.0, 0.5 , 0.0, 0.01, 0.5, 0.0, 0.1, 0.48,0.0, 0.1, 0.345, 0.0,  -0.1, 0.345, 0.0 };
float cuadroInfIzq[12] = { -0.9, -0.74,0.0,   -0.9, -0.63, 0.0,    -0.75, -0.63,0.0,  -0.75, -0.74, 0.0 };
float trapecios[2][12] = { {0.4, 0.15,0.0, 0.4, -0.2, 0.0,  0.53, -0.25, 0.0, 0.53, 0.185, 0.0 },{0.53, -0.25, 0.0, 0.53, -0.1, 0.0,0.58, -0.1, 0.0,0.58, -0.265, 0.0  } };
float triangCopa[9] = { 0.53, 0.19,0.0,   0.53, -0.01,0.0,   0.40, 0.0, 0.0 };
float poligonoCopa[12] = { 0.53, -0.01 , 0.0,  0.735, -0.03 ,0.0,  0.73, 0.15,0.0,  0.53, 0.15, 0.0 };
float triangAbD[9] = { 0.1, -0.515, 0.0,  0.1, -0.8,0.0,   0.8, -0.8, 0.0};
float rectInf[12] = { 0.2, -0.7,0.0,   0.2, -0.8, 0.0,   0.0, -0.8,0.0,   0.0, -0.7, 0.0 };
float triangCopaAb[9] = { 0.568, -0.32, 0.0,   0.45, -0.4, 0.0,   0.568, -0.26, 0.0};

float lineas[43][6] = { {0.9, 0.24,0.0, 0.9, -0.12, 0.0}, {0.87, 0.665,0.0, 0.87, 0.84, 0.0}, {-0.8, 1.0,0.0, -0.8, 0.9, 0.0}, {-0.8, 0.1, 0.0, -1.0, 0.095, 0.0} ,{-0.25, -0.45, 0.0, 0.1, -0.45, 0.0},{0.1, -0.35, 0.0, 0.1, -0.515, 0.0},{-0.8, 0.35,0.0, -0.1, 0.35, 0.0}, {-0.1, 0.345, 0.0, 0.1, 0.345, 0.0}, {0.22, 0.35, 0.0, 0.4, 0.35, 0.0}, {0.4, 0.345, 0.0, 0.4, -0.35, 0.0}, {0.4, -0.35,0.0, -0.8, -0.35, 0.0}, {-0.8, -0.35, 0.0, -0.8, 0.35, 0.0}, {-0.22, 0.23,0.0, -0.22, -0.1,0.0} , {-0.19, 0.23,0.0, -0.19, -0.1, 0.0}, {-0.16, 0.23,0.0, -0.16, -0.1,0.0}, {-0.13, 0.23,0.0, -0.13, -0.1, 0.0},{-0.215, -0.085,0.0, -0.215, -0.5, 0.0},{-0.17, -0.085,0.0, -0.17, -0.49, 0.0},{-0.13, -0.085, 0.0, -0.13, -0.48, 0.0},{-0.09, -0.085, 0.0, -0.09, -0.47, 0.0},{-0.45, 0.5, 0.0, -0.45, 1.0, 0.0},{-0.1, 0.35,0.0, -0.1, 0.9,0.0},{-0.25, 0.35, 0.0, -0.25, 0.7, 0.0},{-0.295, 0.88, 0.0, -0.235, 0.92, 0.0},{-0.235, 0.92, 0.0, -0.22, 0.9, 0.0}, {-0.22, 0.9,0.0, -0.18, 0.925, 0.0},{-0.18, 0.925, 0.0, -0.155, 0.9, 0.0},{-0.155, 0.9,0.0, -0.135, 0.925, 0.0},{-0.135, 0.925,0.0, -0.1, 0.9, 0.0},{-0.8, 0.2, 0.0, -0.1, 0.5, 0.0},{-0.1, 0.5,0.0, 0.3, 0.67, 0.0},{-0.92, 0.37, 0.0, 0.28, 0.7, 0.0},{0.6, 0.18, 0.0, 0.2, 0.73, 0.0},{0.6, 0.21, 0.0, 0.4, 0.12, 0.0},{-0.75, -0.35,0.0, -0.75, -0.63,0.0},{-0.75, -0.63, 0.0, -0.1, -0.63, 0.0},{-0.1, -0.63, 0.0, -0.1, -0.575, 0.0},{-0.1, -0.575, 0.0, -0.25, -0.57, 0.0},{0.43, 0.0, 0.0, 0.72, -0.03, 0.0}, {0.58, -0.03,0.0,  0.58, -0.35, 0.0}, {0.57, -0.34,0.0, 0.57, -0.17, 0.0},{0.59, -0.34, 0.0, 0.59, -0.17, 0.0}, {0.568, -0.32,0.0,  0.5, -0.365, 0.0} };

vector<float> auxPoints;
// retorna el id del VBO
GLuint VBO(float ptos[], int tam) {
    /* VBO
    We will copy this chunk of memory onto the graphics card in a unit
    called a vertex buffer object (VBO).
    To do this we "generate" an empty buffer,
    set it as the current buffer in OpenGL's state machine by "binding",
    then copy the points into the currently bound buffer:
    */
    GLuint vbo; // vertex buffer object
    glGenBuffers(1, &vbo); //we can generate one unique ID with a buffer ID using the glGenBuffers function
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, tam * sizeof(float), ptos, GL_STATIC_DRAW);
    return vbo;
}
// retorna el id del VAO
GLuint VAO(GLuint vbo) {
    GLuint vao = 0; // the vertex array object, It sets an unsigned integer to identify it with later
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); // We bind it, to bring it in to focus in the state machine
    //This lets us enable the first attribute; 0. 
    //We are only using a single vertex buffer, so we know that it will be attribute location 0.
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    return vao;
}
// retorna un id al vertex shader que se creo
GLuint createVertexShader() {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    return vs;
}
// retorna un id al fragment shader que se creo
GLuint createFragmentShader() {
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    return fs;
}
// retorna un id al vertex shader que se creo
GLuint createVertexShaderBezierCubic() {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shaderBezierCubic, NULL);
    glCompileShader(vs);
    return vs;
}
// retorna un id al vertex shader que se creo
GLuint createVertexShaderBezierCuadratic() {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shaderBezierCuadratic, NULL);
    glCompileShader(vs);
    return vs;
}
// retorna un id del programa que se creo con el fragment shader y el vertex shader
GLuint createShaderProgram(GLuint fs, GLuint vs) {
    //Now, these compiled shaders must be combined into a single,
    //executable GPU shader programme.
    //We create an empty "program", attach the shaders, 
    //then link them together.
    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    return shader_programme;
}
/*
    Recibe:
    -El arreglo de puntos que procesarán los shaders.
    -El color para el fragment shader
    -El número de datos en el arreglo de puntos
    -El número de puntos de la figura que se va a dibujar 
    -El tipo de figura de OpenGL
    -La opción del vertex shader
    1 - Shader normal
    2 - Shader para bezier cuadratico (no funcionó)
    3- Shader para bezier cúbico (no funcionó)

*/
void processArray(float *points, float *color, int numValues, int totalPts, GLenum tipo, int opcShader) {
    
    GLuint vbo = VBO(points, numValues);
    GLuint vao = VAO(vbo); // the vertex array object, It sets an unsigned integer to identify it with later
    GLuint vs, fs;
    if (opcShader == 1) { // vertex Shader normal
        vs = createVertexShader();
        fs = createFragmentShader();
    }
    else if (opcShader == 2) {
        vs = createVertexShaderBezierCuadratic();
        fs = createFragmentShader();
    }
    else { /// opc = 3
        vs = createVertexShaderBezierCubic();
        fs = createFragmentShader();
    }
    GLuint shader_program = createShaderProgram(fs, vs);
    glUseProgram(shader_program);
    GLint color_location = glGetUniformLocation(shader_program, "my_color");
    glUniform3fv(color_location, 1, color);
    glBindVertexArray(vao);
    glDrawArrays(tipo, 0, totalPts);  // draw points 0-3 from the currently bound VAO with current in-use shader
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);
}
/*
    Regresa un apuntador a un arreglo que tiene los puntos de una circunferencia
    con centro en (x,y) y radio r
*/
pair<float*, int> pointsOfFilledCircumference(float x, float y, float r) {
    auxPoints.clear();
    float i = 0.0f;    
    auxPoints.push_back(x);
    auxPoints.push_back(y);
    auxPoints.push_back(0.0);
    for (i = 0.0f; i <= 360; i++) {
        auxPoints.push_back((r * cos(pi * i / 180.0) + x));
        auxPoints.push_back((r * sin(pi * i / 180.0) + y));
        auxPoints.push_back(0.0);
    }
    float* ans = auxPoints.data();
    return make_pair(ans, auxPoints.size());
}
/*
    Regresa un apuntador a un arreglo que tiene los puntos de una circunferencia
    con centro en (x,y) y radio r con grosor thickness
*/
pair<float*, int> pointsOfCircumference(float x, float y, float r, float thickness) {
    auxPoints.clear();
    const int numOfPoints = 100;
    const float pi2 = 6.28318530718; // = 2.0*M_PI
    const float da = pi2 / numOfPoints;
    float a, r0 = r - 0.5 * thickness, r1 = r + 0.5 * thickness, c, s;
    int e;    
    for (e = 1, a = 0.0; e; a += da)
    {
        if (a >= pi2) { e = 0; a = pi2; }
        c = cos(a); s = sin(a);
        auxPoints.push_back(c * r0 + x);
        auxPoints.push_back(s * r0 + y);
        auxPoints.push_back(0.0);
        auxPoints.push_back(c*r1+x);
        auxPoints.push_back(s * r1 + y);        
        auxPoints.push_back(0.0);
    }
    float* ans = auxPoints.data();
    return make_pair(ans, auxPoints.size());
}

GLint factor = 1;
GLushort patron = 0x1818;

/*
    Método principal de dibujo
*/
void draw() {
    float* aux;
    pair<float*, int> ans;

    // Punteado
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(3);
    glLineStipple(factor, patron);
    processArray(punteado, negro, 51, 17, GL_LINE_STRIP,1);
    glDisable(GL_LINE_STIPPLE);
    glLineWidth(1);
    

    //rectangulos negro para simular parte inferior negra
    processArray(rectRellenarFig1, negro, 12, 4, GL_POLYGON,1);
    processArray(rectRellenarFig2, negro, 12, 4, GL_POLYGON,1);

    // Guitarra de la izquierda
    processArray(rellGuitarIzq1, verdeAguaPalido, 12, 4, GL_POLYGON,1);
    processArray(rellGuitarIzq2, verdeAguaPalido, 27, 9, GL_POLYGON,1);
    processArray(rellGuitarIzq3, verdeAguaPalido, 15, 5, GL_POLYGON,1);
    
    // circulos para simular 1/4 de circ de guitar inf izq
    ans = pointsOfFilledCircumference(-0.25, -0.35, 0.22);
    processArray(ans.first, azulFuerte, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN,1);
    ans = pointsOfFilledCircumference(-0.28, -0.35, 0.22);
    processArray(ans.first, azulFuerte, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN,1);
    ans = pointsOfFilledCircumference(-0.3, -0.35, 0.22);
    processArray(ans.first, azulFuerte, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN,1);
    ans = pointsOfFilledCircumference(-0.32, -0.34, 0.22);
    processArray(ans.first, azulFuerte, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN,1);
    ans = pointsOfFilledCircumference(-0.33, -0.34, 0.22);
    processArray(ans.first, azulFuerte, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN,1);
    ans = pointsOfFilledCircumference(-0.34, -0.34, 0.22);
    processArray(ans.first, azulFuerte, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN,1);

    //romboide de la parte inferior derecha
    processArray(romboideInfDer, amarilloDescolorido, 12, 4, GL_POLYGON,1);

    // figura amarilla arriba de triangulo negro del cuadro
    processArray(figAmarillaArriba, amarilloDescolorido, 15, 5, GL_POLYGON, 1);

    //triangulo azul inf der
    processArray(triangAzulInfDer, azulArriba, 9, 3, GL_POLYGON, 1);

    // nedio circulo gris derecha arriba
    ans = pointsOfFilledCircumference(0.87, 0.4525, 0.2325);
    processArray(ans.first, grisOsc, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN, 1);

    // medio circulo azul derecha arriba
    ans = pointsOfFilledCircumference(0.87, 0.4525, 0.21);
    processArray(ans.first, azulArriba, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN, 1);

    // rectangulo para tapar restos de circulo sup derecho
    processArray(rectRight, beige, 12, 4, GL_POLYGON, 1);

    //triangulo para cubrir restos
    processArray(triangRightUp, beige, 9, 3, GL_POLYGON, 1);

    //poligono para simular medio circulo azul sup
    processArray(fillPolygonRight, beige, 24, 8, GL_POLYGON, 1);

    // lineas de la parte sup der
    processArray(lineas[0], negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0]+6, negro, 6, 2, GL_LINES, 1);

    //lineas de los triangulos sup
    processArray(triangSupDer, negro, 36, 12, GL_LINE_STRIP, 1);

    // rectangulo azul de cuadro para rellenar
    processArray(rectRellenoAzul1, azulMedio, 12, 4, GL_POLYGON, 1);
    processArray(rectRellenoAzul2, azulClaro, 12, 4, GL_POLYGON, 1);

    // linea sup izq, guitarra
    processArray(lineas[0] + 12, negro, 6, 2, GL_LINES, 1);

    /// -------------------------------------------------------- AQUI ESTAN LOS SHADERS DE BEZIER --------------


    // guitarra sup mitad
    // parte sup
    processArray(pGuitarUp1, negro, 21, 7, GL_LINE_STRIP, 1);
    // parte inf
    // parte inferior guitarra izq superior
    processArray(pGuitarDown1, negro, 15, 5, GL_LINE_STRIP, 1);


    // --------------------------------------------- AQUI TERMINAN----------------------------------

    // linea que une guitar a izq
    processArray(lineas[0] + 18, negro, 6, 2, GL_LINES, 1);
    
    //triangulos del cuadro
    processArray(squareTriangs[0] , azulFuerte, 9, 3, GL_POLYGON, 1);
    processArray(squareTriangs[0]+9, azulOsc, 9, 3, GL_POLYGON, 1);
    processArray(squareTriangs[0]+18, negro, 9, 3, GL_POLYGON, 1);

    // Rectangulo vertical para rellenar
    processArray(verRect, beige, 12, 4, GL_POLYGON, 1);

    // rectangulo horizontal de abajo de guitarra 
    processArray(rectDown, negro, 12, 4, GL_POLYGON, 1);

    // linea abajo de rectangulo hor  
    glLineWidth(4);

    //checaaaaaaaar
    processArray(lineas[0] + 24, negro, 6, 2, GL_LINES, 1);

    // linea vertical que conecta con rectan hor de git 
    processArray(lineas[0] + 30, grisOsc, 6, 2, GL_LINES, 1);

    glLineWidth(1);
    // linea de cuadrado    
    processArray(lineas[0] + 36, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 42, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 48, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 54, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 60, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 66, negro, 6, 2, GL_LINES, 1);

    // media circunferencia negra arriba
    ans = pointsOfCircumference(-0.09, 0.12, 0.05, 0.005);
    processArray(ans.first, negro, ans.second, (int)ans.second / 3, GL_QUAD_STRIP, 1);

    // Rectangulo vertical negro que tiene cuerdas
    processArray(midRect, negro, 12, 4, GL_POLYGON, 1);

    //cuerdas
    processArray(lineas[0] + 72, beige, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 78, beige, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 84, beige, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 90, beige, 6, 2, GL_LINES, 1);

    // circulo negro para simular medio circ
    ans = pointsOfFilledCircumference(-0.147, -0.085, 0.09);
    processArray(ans.first, negro, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN, 1);

    // Rectangulo para simular media circ
    processArray(circRect, beige, 12, 4, GL_POLYGON, 1);
    
    //circ interna negra
    ans = pointsOfCircumference(-0.147, -0.09, .1, .01);
    processArray(ans.first, negro, ans.second, (int)ans.second / 3, GL_QUAD_STRIP, 1);

    // cir beige
    ans = pointsOfCircumference(-0.147, -0.09, 0.09, 0.01);
    processArray(ans.first, beige, ans.second, (int)ans.second / 3, GL_QUAD_STRIP, 1);
    
    // relleno guitarra cafe
    processArray(rellenoGuitarCafe1, cafeOsc, 12, 4, GL_POLYGON, 1);
    processArray(rellenoGuitarCafe2, cafeOsc, 12, 4, GL_POLYGON, 1);
    processArray(rellenoGuitarCafe3, cafeOsc, 30, 10, GL_POLYGON, 1);
    processArray(rellenoGuitarCafe4, cafeOsc, 42, 14, GL_POLYGON, 1);

    // relleno guitarra amarilla
    processArray(rellenoGuitarAma1, amarillo, 18, 6, GL_POLYGON, 1);
    processArray(rellenoGuitarAma2, amarillo, 24, 8, GL_POLYGON, 1);

    //lineas de la marca de la guitarra   
    processArray(lineasCuadro[0], negro, 12, 4, GL_LINE_STRIP, 1);
    processArray(lineasCuadro[0]+12, negro, 12, 4, GL_LINE_STRIP, 1);
    processArray(lineasCuadro[0]+24, negro, 12, 4, GL_LINE_STRIP, 1);
    processArray(lineasCuadro[0]+36, negro, 12, 4, GL_LINE_STRIP, 1);

    // lineas que llegan hasta abajo
    processArray(lineas[0] + 96, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 102, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 108, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 114, negro, 6, 2, GL_LINES, 1);

    // Linea antes del rectangulo azul para parte superior
    processArray(lineas[0] + 120, negro, 6, 2, GL_LINES, 1);

    // Relleno parte sup guitarra
    processArray(rellenoSupG, cafeClaro, 12, 4, GL_POLYGON, 1);

    // rectangulo para colorear de azul arriba
    processArray(triangSupAzul, azulArriba, 9, 3, GL_POLYGON, 1);
    processArray(rectSupAzul, azulArriba, 12, 4, GL_POLYGON, 1);

    // relleno para compensar azul
    processArray(rectRellAzul[0], cafeClaro, 12, 4, GL_POLYGON, 1);
    processArray(triangRellAzul[0] , cafeClaro, 9, 3, GL_POLYGON, 1);
    processArray(triangRellAzul[0] + 9, cafeClaro, 9, 3, GL_POLYGON, 1);
    processArray(triangRellAzul[0] + 18, cafeClaro, 9, 3, GL_POLYGON, 1);
    processArray(rectRellAzul[0]+12, cafeClaro, 12, 4, GL_POLYGON, 1);
    processArray(triangRellAzul[0] + 27, cafeClaro, 9, 3, GL_POLYGON, 1);


    // linea guitarra hacia arriba
    processArray(lineas[0] + 126, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 132, negro, 6, 2, GL_LINES, 1);

    // -------detalles guitarra arriba-----

    // parte que esta por los 3 ajustadores
    processArray(parteAjustador, negro, 12, 4, GL_POLYGON, 1);
    processArray(triangAj, negro, 9, 3, GL_POLYGON, 1);
    processArray(lineas[0] + 138, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 144, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 150, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 156, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 162, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 168, negro, 6, 2, GL_LINES, 1);

    // Puntos de la guitarra
    glPointSize(5);
    processArray(puntosAr[0], negro, 3, 1, GL_POINTS, 1);
    glPointSize(5);
    processArray(puntosAr[0] +3, negro, 3, 1, GL_POINTS, 1);
    glPointSize(5);
    processArray(puntosAr[0] + 6, negro, 3, 1, GL_POINTS, 1);

    // ---Ajustadores
 
    // ajustador 1
    // ajustador abajo
    processArray(ajustadores[0], negro, 12, 4, GL_POLYGON, 1);
    processArray(ajustadores[0]+12, negro, 12, 4, GL_POLYGON, 1);
    // ajustador en medio
    processArray(ajustadores[0]+24, negro, 12, 4, GL_POLYGON, 1);
    processArray(ajustadores[0]+36, negro, 12, 4, GL_POLYGON, 1);
    // ajustador arriba
    processArray(ajustadores[0]+48, negro, 12, 4, GL_POLYGON, 1);
    processArray(ajustadores[0]+60, negro, 12, 4, GL_POLYGON, 1);

    // lineas inclinadas que cruzan a la mitad del cuadro
    processArray(lineas[0] + 174, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 180, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 186, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 192, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 198, negro, 6, 2, GL_LINES, 1);

    // figura negra arriba de cuadro
    processArray(figNegra, negro, 21, 7, GL_POLYGON, 1);

    // guitarra medio der sup    
    processArray(pGuitarUp2, negro, 27, 9, GL_LINE_STRIP, 1);
        
    // guitarra medio der inf
    processArray(pGuitarDown2, negro, 36, 12, GL_LINE_STRIP, 1);    

    //guitarra medio izq sup
    processArray(pGuitarUp3, negro, 21, 8, GL_LINE_STRIP, 1);    

    // guitarra medio der inf
    processArray(pGuitarDown3, negro, 18, 6, GL_LINE_STRIP, 1);


    // rectangulo con circulo azul
    processArray(lineas[0] + 204, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 210, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 216, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 222, negro, 6, 2, GL_LINES, 1);

    // cuadro inf izq
    processArray(cuadroInfIzq, negro, 12, 4, GL_POLYGON, 1);

    //trapecio negro a lado de cuadro
    processArray(trapecios[0], negro, 12, 4, GL_POLYGON, 1);

    // trapecio negro para compensar copa
    processArray(trapecios[0]+12, negro, 12, 4, GL_POLYGON, 1);

    // Copa
    ans = pointsOfFilledCircumference(0.58, -0.03, 0.15);
    processArray(ans.first, grisCopa, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN, 1);
    
    //delineado de la copa
    ans = pointsOfCircumference(0.58, -0.03, 0.15, 0.005);
    processArray(ans.first, negro, ans.second, (int)ans.second / 3, GL_QUAD_STRIP, 1);

    processArray(lineas[0] + 228, negro, 6, 2, GL_LINES, 1);
    processArray(triangCopa, negro, 9, 3, GL_POLYGON, 1);

    // Poligono para compensar copa
    processArray(poligonoCopa, beige, 12, 4, GL_POLYGON, 1);
    
    // Copa parte baja
    ans = pointsOfFilledCircumference(0.57, -0.37, 0.065);
    processArray(ans.first, grisCopa, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN, 1);
    ans = pointsOfCircumference(0.57, -0.37, 0.065, 0.005);
    processArray(ans.first, negro, ans.second, (int)ans.second / 3, GL_QUAD_STRIP, 1);
    
    glLineWidth(5);
    processArray(lineas[0] + 234, grisCopa, 6, 2, GL_LINES, 1);
    
    glLineWidth(1);
    processArray(lineas[0] + 240, negro, 6, 2, GL_LINES, 1);
    processArray(lineas[0] + 246, negro, 6, 2, GL_LINES, 1);

    // triangulo para simular copa
    processArray(triangCopaAb, amarilloDescolorido, 9, 3, GL_POLYGON, 1);

    //Linea base copa
    processArray(lineas[0] + 252, negro, 6, 2, GL_LINES, 1);

    // triangulo de hasta abajo der
    processArray(triangAbD, negro, 9, 3, GL_POLYGON, 1);

    // para simular cruva hasta abajo
    ans = pointsOfFilledCircumference(0.2, -0.8, 0.1);
    processArray(ans.first, beige, ans.second, (int)ans.second / 3, GL_TRIANGLE_FAN, 1);
    processArray(rectInf, beige, 12, 4, GL_POLYGON, 1);

    

}
int main() {

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }


    GLFWwindow* window = glfwCreateWindow(ww, wh, "Tarea 3 Yosshua", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();
    

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LEQUAL); // depth-testing interprets a smaller value as "closer"




    // Dibujando
    while (!glfwWindowShouldClose(window)) {
        //First we clear the drawing surface, 
        //then set the shader programme that should be "in use" 
        //for all further drawing. We set our VAO(not the VBO) 
        //as the input variables that should be used for all 
        //further drawing(in our case just some vertex points).
        //Then we can draw
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.98, 0.949, 0.863,0.0);


        draw();


        // update other events like input handling 
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }



    glfwTerminate();
    return 0;
}
