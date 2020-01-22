//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, CONO, CILINDRO, ESFERA, ARTICULADO, TODO} _tipo_objeto;
_tipo_objeto t_objeto=ARTICULADO;
_modo   modo=POINTS;

typedef enum{ALZADO, PERFIL, PLANTA, PERSPECTIVA} _tipo_camara;
_tipo_camara camara = PERSPECTIVA;


// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_distance2;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo;
_piramide piramide;
_tubo_cerrado cilindro;
_cono cono;
_esfera esfera;
_objeto_ply  ply; 
_rotacion rotacion; 
_torreta torreta;

// _objeto_ply *ply1;


float velocidad1 = 0.5;
float velocidad2 = 0.05;
float velocidad3 = 0.5;

bool animacion = false;
bool animacion_luz = false;

bool luz1_activada = false;
bool luz0_activada = false;

_luces luz0(GL_LIGHT0, _vertex4f(0.0, 0.0, 0.0, 1), _vertex4f(1.0, 1.0, 1.0, 1), _vertex4f(1.0, 1.0, 1.0, 1), 0.5, _vertex4f(0, 10, 10, 0));
_luces luz1(GL_LIGHT1, _vertex4f(1.0, 0.0, 1.0, 1), _vertex4f(0.5, 0.5, 0.5, 1), _vertex4f(0.5, 0.5, 0.5, 1), 0.5, _vertex4f(0, 10, 10, 1));

bool valido = false;
int xc, yc, modoo[5], cambio=0;
bool perspectiva = true, multi_cam = false;


void pick_color(int x, int y);

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
if(perspectiva)
{
        glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}
else
{
        
        glOrtho(-Size_x*2.5*Observer_distance2,Size_x*2.5*Observer_distance2,-Size_y*2.5*Observer_distance2,Size_y*2.5*Observer_distance2,-100,100);

        
}

}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();



if(perspectiva)
{
        glTranslatef(0,0,-Observer_distance);
        glRotatef(Observer_angle_x,1,0,0);
        glRotatef(Observer_angle_y,0,1,0);

}


}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

        switch (t_objeto)
        {
                case CUBO: cubo.draw(modo,cubo.r,cubo.g,cubo.b,0.0,1.0,0.0,2);break;
                case PIRAMIDE: piramide.draw(modo,piramide.r,piramide.g,piramide.b,0.0,1.0,0.0,2);break;
                case OBJETO_PLY: ply.draw(modo,ply.r,ply.g,ply.b,0.0,1.0,0.0,2);break;
                case ROTACION: rotacion.draw(modo,rotacion.r,rotacion.g,rotacion.b,0.0,1.0,0.0,2);break;
                case CONO: cono.draw(modo,cono.r,cono.g,cono.b,0.0,1.0,0.0,2);break;
                case CILINDRO: cilindro.draw(modo,cilindro.r,cilindro.g,cilindro.b,0.0,1.0,0.0,2);break;
                case ESFERA: esfera.draw(modo,esfera.r,esfera.g,esfera.b,0.0,1.0,0.0,2);break;
                case ARTICULADO: torreta.draw(modo,torreta.r,torreta.g,torreta.b,0.3,0.6,0.3,2);break;
                case TODO: 
                        glPushMatrix(); 
                        cubo.draw(modo,cubo.r,cubo.g,cubo.b,0.0,1.0,0.0,2);
                        glTranslatef(2.5,0.0,0.0); piramide.draw(modo,piramide.r,piramide.g,piramide.b,0.0,1.0,0.0,2);
                        glTranslatef(2.5,0.0,0.0); rotacion.draw(modo,rotacion.r,rotacion.g,rotacion.b,0.0,1.0,0.0,2);
                        glTranslatef(2.5,0.0,0.0); cono.draw(modo,cono.r,cono.g,cono.b,0.0,1.0,0.0,2);
                        glTranslatef(-9,0.0,0.0); cilindro.draw(modo,cilindro.r,cilindro.g,cilindro.b,0.0,1.0,0.0,2);
                        glTranslatef(-2.5,0.0,0.0); esfera.draw(modo,esfera.r,esfera.g,esfera.b,0.0,1.0,0.0,2);
                        glTranslatef(-2.5,0.0,0.0); torreta.draw(modo,torreta.r,torreta.g,torreta.b,0.3,0.6,0.3,2);
                        glPopMatrix(); break;
        }

}


void draw_objects_seleccion()
{
        switch (t_objeto)
        {

                case CUBO: cubo.draw(SELECCION,0,100,100,0.0,1.0,0.0,2);break;
                case PIRAMIDE: piramide.draw(SELECCION,100,100,110,0.0,1.0,0.0,2);break;
                case OBJETO_PLY: ply.draw(SELECCION,100,100,120,0.0,1.0,0.0,2);break;
                case CONO: cono.draw(SELECCION,100,100,130,0.0,1.0,0.0,2);break;
                case CILINDRO: cilindro.draw(SELECCION,100,100,140,0.0,1.0,0.0,2);break;
                case ESFERA: esfera.draw(SELECCION,100,100,150,0.0,1.0,0.0,2);break;
                case ARTICULADO: torreta.draw(SELECCION,100,100,160,0.0,1.0,0.0,2);break;                
                case TODO: 
                        glPushMatrix(); 
                        cubo.draw(SELECCION,0,100,100,0.0,1.0,0.0,2);
                        glTranslatef(2.5,0.0,0.0); piramide.draw(SELECCION,100,100,110,0.0,1.0,0.0,2);
                        glTranslatef(2.5,0.0,0.0); ply.draw(SELECCION,100,100,120,0.0,1.0,0.0,2);
                        glTranslatef(2.5,0.0,0.0); cono.draw(SELECCION,100,100,130,0.0,1.0,0.0,2);
                        glTranslatef(-9,0.0,0.0); cilindro.draw(SELECCION,100,100,140,0.0,1.0,0.0,2);
                        glTranslatef(-2.5,0.0,0.0); esfera.draw(SELECCION,100,100,150,0.0,1.0,0.0,2);
                        glTranslatef(-2.5,0.0,0.0); torreta.draw(SELECCION,100,100,160,0.0,1.0,0.0,2);
                        glPopMatrix(); break;

	}        
        
}




//**************************************************************************
//
//***************************************************************************


void funcion_animacion_luz()
{
        luz1.giro_auto();
        glutPostRedisplay();
}


bool atras = false;
bool arriba = false;
bool choque_atras = false;

void funcion_animacion()
{
        //luz rotacion
        luz1.giro_auto();
        glutPostRedisplay();
        
        //giro cabeza
        torreta.giro+=velocidad3;

        //bisagra
        if (choque_atras)
        {
                torreta.bisagra.angulo-=velocidad3;
        }
        else
        {
                torreta.bisagra.angulo+=velocidad3;
        }

        torreta.rot_y = 0.292891+cos((torreta.bisagra.angulo)*3.1416/180)-1;  //1.0-(sin(45*3.1416/180)) = 0.292891
        torreta.rot_z = 0.292891+sin((torreta.bisagra.angulo)*3.1416/180)-1;  //1.0-(sin(45*3.1416/180)) = 0.292891
        
        if (torreta.bisagra.angulo>torreta.bisagra.giro_bisagra_max){
                choque_atras = true;
                torreta.bisagra.angulo=torreta.bisagra.giro_bisagra_max;                         
        }

        
        if (torreta.bisagra.angulo<torreta.bisagra.giro_bisagra_min){
                choque_atras = false;
                torreta.bisagra.angulo=torreta.bisagra.giro_bisagra_min; 
        }

        //giro mete-saca tubillo de tubo
        if (atras)
        {
                torreta.semiesfera.translacion_tubo-=velocidad2;
        }
        else
        {
                torreta.semiesfera.translacion_tubo+=velocidad2;
        }         

        if (torreta.semiesfera.translacion_tubo>torreta.semiesfera.translacion_tubo_max)
        {
               atras = true;
               torreta.semiesfera.translacion_tubo=torreta.semiesfera.translacion_tubo_max;
        }
        if (torreta.semiesfera.translacion_tubo<torreta.semiesfera.translacion_tubo_min)
        {
                atras = false;
                torreta.semiesfera.translacion_tubo=torreta.semiesfera.translacion_tubo_min;
        }

        //giro arriba-abajo de tubo
        if (arriba)
        {
                torreta.semiesfera.giro_tubo-=velocidad1;
        }
        else
        {
                torreta.semiesfera.giro_tubo+=velocidad1;
        }         

        if (torreta.semiesfera.giro_tubo>torreta.semiesfera.giro_tubo_max){
                arriba = true;
                torreta.semiesfera.giro_tubo=torreta.semiesfera.giro_tubo_max;
        }


        if (torreta.semiesfera.giro_tubo<torreta.semiesfera.giro_tubo_min){
                arriba = false;
                torreta.semiesfera.giro_tubo=torreta.semiesfera.giro_tubo_min;
        }
        
        glutPostRedisplay();
}





void draw(void)
{

if (multi_cam)
{
        glDrawBuffer(GL_FRONT);
        clean_window();
        
        //alzado        
        change_projection();
        glTranslatef(-2.5,-2.0,0);
        change_observer(); 
        draw_objects();
        //planta
        change_projection();
        glTranslatef(2.5,2.0,0);
        glRotatef(90,1,0,0);
        change_observer(); 
        draw_objects();
        //perfil
        change_projection();
        glTranslatef(2.5,-2.0,0); 
        glRotatef(90,0,1,0);  
        change_observer(); 
        draw_objects();

        glFlush();
}
else
{

        glDrawBuffer(GL_FRONT);
        clean_window();
        change_projection();
        change_observer();
        draw_axis();
        draw_objects();

        glDrawBuffer(GL_BACK);
        clean_window();
        change_projection();
        change_observer();
        draw_objects_seleccion();

        glFlush();

}



}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{ 


switch (toupper(Tecla1)){
	case 'P':modo=POINTS;break;
	case 'L':modo=EDGES;break;
	case 'F':modo=SOLID;break;	
        case '1':t_objeto=PIRAMIDE;break;
        case '2':t_objeto=CUBO;break;
        case '3':t_objeto=CONO;break;
	case '4':t_objeto=CILINDRO;break;
	case '5':t_objeto=ESFERA;break;
        case '6':t_objeto=OBJETO_PLY;break;	
        case '7':t_objeto=ARTICULADO;break;
        case '8':t_objeto=TODO;break;
        //case '8': ;break;       TABLERO NO SE HACE
        //case 'R':t_objeto=ROTACION;break;
        case 'M':if (animacion_luz){glutIdleFunc(NULL);animacion_luz = false;}else{glutIdleFunc(funcion_animacion_luz);animacion_luz = true;}break;

        case 'A':if (animacion){glutIdleFunc(NULL);animacion = false;}else{glutIdleFunc(funcion_animacion);animacion = true;}break;

        case 'J':if (luz0_activada){luz0.deshabilitar();luz0_activada = false;}else{luz0.habilitar();luz0_activada = true;}break;                  
        case 'K':if (luz1_activada){luz1.deshabilitar();luz1_activada = false;}else{luz1.habilitar();luz1_activada = true;}break;                       

        //GIRO VERTICAL DE LOS CAÑONES
        case 'Q':torreta.semiesfera.giro_tubo+=velocidad1;
                         if (torreta.semiesfera.giro_tubo>torreta.semiesfera.giro_tubo_max) torreta.semiesfera.giro_tubo=torreta.semiesfera.giro_tubo_max;
                         break;
        case 'W':torreta.semiesfera.giro_tubo-=velocidad1;
                         if (torreta.semiesfera.giro_tubo<torreta.semiesfera.giro_tubo_min) torreta.semiesfera.giro_tubo=torreta.semiesfera.giro_tubo_min;
                         break;

        //TRASLADAR TUBO DE DENTRO DEL CAÑON
        case 'S':torreta.semiesfera.translacion_tubo+=velocidad2;
                         if (torreta.semiesfera.translacion_tubo>torreta.semiesfera.translacion_tubo_max) torreta.semiesfera.translacion_tubo=torreta.semiesfera.translacion_tubo_max;
                         break;
        case 'D':torreta.semiesfera.translacion_tubo-=velocidad2;
                         if (torreta.semiesfera.translacion_tubo<torreta.semiesfera.translacion_tubo_min) torreta.semiesfera.translacion_tubo=torreta.semiesfera.translacion_tubo_min;
                         break;

        //MOVIMIENTO CON BISAGRA
        case 'Z':torreta.bisagra.angulo+=velocidad3;
                         torreta.rot_y = 0.292891+cos((torreta.bisagra.angulo)*3.1416/180)-1;  //1.0-(sin(45*3.1416/180)) = 0.292891
                         torreta.rot_z = 0.292891+sin((torreta.bisagra.angulo)*3.1416/180)-1;  //1.0-(sin(45*3.1416/180)) = 0.292891
                         if (torreta.bisagra.angulo>torreta.bisagra.giro_bisagra_max) torreta.bisagra.angulo=torreta.bisagra.giro_bisagra_max;                         
                         break;
        case 'X':torreta.bisagra.angulo-=velocidad3;
                         torreta.rot_y = 0.292891+cos((torreta.bisagra.angulo)*3.1416/180)-1;  //1.0-(sin(45*3.1416/180)) = 0.292891
                         torreta.rot_z = 0.292891+sin((torreta.bisagra.angulo)*3.1416/180)-1;  //1.0-(sin(45*3.1416/180)) = 0.292891
                         if (torreta.bisagra.angulo<torreta.bisagra.giro_bisagra_min) torreta.bisagra.angulo=torreta.bisagra.giro_bisagra_min; 
                         break;

        //GIRO semiesfera
        // case 'V':torreta.giro+=velocidad3;
        //                  break;
        // case 'B':torreta.giro-=velocidad3;
        //                  break;

        //VELOCIDADES
        case 'E':velocidad1 += 0.1;
                cout << "velocidad vertical cañones: "<< velocidad1 << endl;
                 break;
        case 'R':velocidad1 -= 0.1;
                cout << "velocidad vertical cañones: "<< velocidad1 << endl;
                 if(velocidad1<0.1) velocidad1 = 0.1;
                 break;

        case 'T':velocidad2 += 0.001;
                cout << "velocidad tubo cañon: "<< velocidad2 << endl;
                 break;
        case 'Y':velocidad2 -= 0.001;
                 if(velocidad2<0.001){ velocidad2 = 0.001;}
                 cout << "velocidad tubo cañon: "<< velocidad2 << endl;
                 break;

        case 'U':velocidad3 += 0.1;
                cout << "velocidad bisagra y giro cabeza: "<< velocidad3 << endl;
                 break;
        case 'I':velocidad3 -= 0.1;
                 if(velocidad3<0.1) velocidad3 = 0.1;
                 cout << "velocidad bisagra y giro cabeza: "<< velocidad3 << endl;
                 break;
        
        //CAMARAS
        case 'C':perspectiva = true;
                 multi_cam = false;
                 break;
        case 'V':perspectiva = false;
                 multi_cam = false;
                 break;
        case 'B':multi_cam = true;
                 break;


	}
glutPostRedisplay();
}


//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************


void special_key(int Tecla1,int x,int y)
{
float ant_ang;
switch (Tecla1){
	case GLUT_KEY_LEFT:if (perspectiva){Observer_angle_y--;}break;
	case GLUT_KEY_RIGHT:if (perspectiva){Observer_angle_y++;}break;
	case GLUT_KEY_UP:if (perspectiva){Observer_angle_x--;}break;
	case GLUT_KEY_DOWN:if (perspectiva){Observer_angle_x++;}break;
	case GLUT_KEY_PAGE_UP:if (perspectiva){Observer_distance*=1.2;}else{Observer_distance2*=1.2;}break;
	case GLUT_KEY_PAGE_DOWN:if (perspectiva){Observer_distance/=1.2;}else{Observer_distance2/=1.2;}break;

        case GLUT_KEY_F1:modo=SOLID;break;
        case GLUT_KEY_F2:modo=SOLID_CHESS;break;
        case GLUT_KEY_F3:modo=SOLID_ILLUMINATED_FLAT;break;
        case GLUT_KEY_F4:modo=SOLID_ILLUMINATED_GOURAUD;break;

	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_distance2=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);

for (int i=0;i<5;i++) modoo[i]=0;

}



//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


void clickRaton( int boton, int estado, int x, int y )
{       
        
	
	//Rueda
	if (boton == 3)
        {       
                if (perspectiva)
                {Observer_distance/=1.2;}
                else
                {Observer_distance2/=1.2;}
                
                
                
        }
        //Rueda		
	else if (boton == 4)
        {
                if (perspectiva)
                {Observer_distance*=1.2;}
                else
                {Observer_distance2*=1.2;}
        }

        else if (perspectiva)
        {
                if (boton == GLUT_RIGHT_BUTTON) {
                        //presionar o soltar boton
                        if( estado == GLUT_DOWN) {
                                valido = 1;
                                xc=x;
                                yc=y;
                        } 
                        else valido = 0;
                }
                                
                else if (boton == GLUT_LEFT_BUTTON) {
                        if( estado == GLUT_DOWN) {
                                
                                if (modo==SOLID)
                                {
                                        valido = 0;
                                        xc=x;
                                        yc=y;
                                        pick_color(xc, yc);
                                }                                
                        } 
                }
        }               
                
       
	glutPostRedisplay();
}

void RatonMovido( int x, int y )
{
	float xn, yn; 
	if(valido){
		
		yn=Observer_angle_y+(x-xc);
		xn=Observer_angle_x+(y-yc);
		
                Observer_angle_x=xn;
	        Observer_angle_y=yn;

                
		xc=x;
		yc=y;

		glutPostRedisplay();
	}
}


template <typename T>
void cambiar_color(T & obj)
{
        
        if (obj.seleccionado) 
        {
                obj.r=0.3;
                obj.g=0.9;
                obj.b=0.3;
        }
                  //color de piramide original
        else
        {
                obj.r=0.9;
                obj.g=0.6;
                obj.b=0.2;
        }
}

void procesar_color(unsigned char color[3])
{
        int i;
 
bool salir = false;
 switch (color[2])
      {

        case 100: 
                
                for (int i = 0; i < cubo.caras.size() && !salir; i++)
                {
                        if (color[0] == i)
                        {                                
                                if (cubo.seleccionado_cara[i]) 
                                {
                                        cubo.seleccionado_cara[i]=0;                                  
                                }
                                else 
                                {
                                        cubo.seleccionado_cara[i]=1;                                                                            
                                }

                                salir = true;
                                
                        }
                        
                }
                
                
                break;
                 
        case 110: 
                if (piramide.seleccionado) 
                {
                        piramide.seleccionado=0;                                        
                }
                else 
                {
                        piramide.seleccionado=1;                        
                }
                cambiar_color(piramide);
                break;

        case 120: 
                if (ply.seleccionado) 
                {
                        ply.seleccionado=0;                                  
                }
                else 
                {
                        ply.seleccionado=1;                                        
                }
                cambiar_color(ply);
                break;
                 
        case 130: 
                if (cono.seleccionado) 
                {
                        cono.seleccionado=0;                                        
                }
                else 
                {
                        cono.seleccionado=1;                        
                }
                cambiar_color(cono);
                break;
        
        case 140: 
                if (cilindro.seleccionado) 
                {
                        cilindro.seleccionado=0;                                  
                }
                else 
                {
                        cilindro.seleccionado=1;                                        
                }
                cambiar_color(cilindro);
                break;
                 
        case 150: 
                if (esfera.seleccionado) 
                {
                        esfera.seleccionado=0;                                        
                }
                else 
                {
                        esfera.seleccionado=1;                        
                }
                cambiar_color(esfera);
                break;

        case 160: 
                if (torreta.seleccionado) 
                {
                        torreta.seleccionado=0;                                        
                }
                else 
                {
                        torreta.seleccionado=1;                        
                }
                cambiar_color(torreta);
                break;

      }
        
                //color de seleccion
        
       
}

void pick_color(int x, int y)
{
        GLint viewport[4];
        unsigned char pixel[3];

        glGetIntegerv(GL_VIEWPORT, viewport);
        glReadBuffer(GL_BACK);
        glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
        printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

        procesar_color(pixel);
        glutPostRedisplay();
}


int main(int argc, char **argv)
{
 

// creación del objeto ply

ply.parametros(argv[1]);


// perfil 

vector<_vertex3f> perfil2;
_vertex3f aux;
aux.x=1.0;aux.y=-1.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0;aux.y=-1.1;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=-0.7;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=-0.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=0.5;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.8;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.55;aux.y=1.0;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=1.2;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=1.4;aux.z=0.0;
perfil2.push_back(aux);
rotacion.parametros(perfil2,6,1);


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 5");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// eventos ratón
glutMouseFunc( clickRaton );
glutMotionFunc( RatonMovido );


// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}




