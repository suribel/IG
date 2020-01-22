//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILLUMINATED_FLAT,
             SOLID_ILLUMINATED_GOURAUD, SELECCION} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

       int seleccionado;
       float r;
       float g;
       float b;

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw_iluminacion_plana( );
void 	draw_iluminacion_suave( );
void   seleccion(int r, int g, int b);

void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void	calcular_normales_caras();
void 	calcular_normales_vertices();

vector<_vertex3i> caras;

vector<_vertex3f> normales_caras;

vector<int> seleccionado_cara;
bool pinto_cara;

vector<_vertex3f> normales_vertices;

bool b_normales_caras;
bool b_normales_vertices;

_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
_vertex4f especular;           //coeficiente especular
GLfloat brillo;                  //exponente del brillo 

};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);
void  parametros_ply(char *archivo, int num);
vector<_vertex3f> perfil; 
int num;
};


//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _cono: public _triangulos3D
{
public:
       _cono();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion cono; 
};

class _esfera: public _triangulos3D
{
public:
       _esfera();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion esfera; 
};



class _extension: public _triangulos3D
{
public:
       _extension();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  rodamiento;
_cubo  base;

};







//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion tubo_abierto; // caña del cañón
};

class _tubo_cerrado: public _triangulos3D
{
public:
       _tubo_cerrado();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion tubo_cerrado; // caña del cañón
};


class _cuerpo: public _triangulos3D
{
public:
       _cuerpo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion forma;
_tubo_cerrado tubo_cerrado;
};


class _pie: public _triangulos3D
{
public:
       _pie();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  rodamiento;
_tubo_cerrado tubo_cerr;
};


//************************************************************************




class _semiesfera: public _triangulos3D
{
public:
       _semiesfera();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_tubo;
float translacion_tubo;

float giro_tubo_min;
float giro_tubo_max;
float translacion_tubo_min;	
float translacion_tubo_max;



protected:
_rotacion semi_esfera;
_tubo     tubo;
};

class _bisagra: public _triangulos3D
{
public:
float angulo;
float giro_bisagra_max;
float giro_bisagra_min;
       _bisagra();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_extension  extension;
};

class _torreta: public _triangulos3D
{
public:
float rot_y;
float rot_z;
float giro;
       _torreta();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
_bisagra bisagra;
_semiesfera semiesfera;

protected:
_pie pie;
_cuerpo cuerpo;
};


class _luces
{
public:
       _luces(GLenum l, _vertex4f lAmbiente, _vertex4f lDifusa, _vertex4f lEspecular, GLfloat lBrillo, _vertex4f lPosicion);

void habilitar();
void deshabilitar();
void giro_auto();

protected:
int cont;
GLenum luz;
_vertex4f ambiente;
_vertex4f difusa;
_vertex4f especular;
GLfloat brillo;
_vertex4f posicion;
};
