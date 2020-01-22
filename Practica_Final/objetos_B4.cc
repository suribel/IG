//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
	b_normales_caras = false;
    b_normales_vertices = false;

    ambiente_difusa = _vertex4f(1,1,1,1);
    especular = _vertex4f(1,1,1,1);
	brillo = 100;
	seleccionado = 0;
	r=0.9;g=0.6;b=0.2;
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

glBegin(GL_TRIANGLES);

if(pinto_cara)
{
	

	for (i=0;i<caras.size();i++){
		if (seleccionado_cara[i])
		{
			glColor3f(0.1,0.1,0.1);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
		else
		{
			glColor3f(r,g,b);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
		

	}
	glEnd();

}
else
{
	glColor3f(r,g,b);
	for (i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
}


glEnd();
}



void _triangulos3D::seleccion(int r, int g, int b)
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glColor3ub(r+i,g,b);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana();break;
	case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave();break;
	case SELECCION:seleccion(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************
_cubo::_cubo(float tam)
{

pinto_cara=true;

//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
seleccionado_cara.resize(12);
for (int i = 0; i < 12; i++)
{
	seleccionado_cara[i]=0;
}


caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;  
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
//vertices 
vertices.resize(5);
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
   
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
	}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
	}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;


/////
//LOS PERFILES SE EMPIEZAN DESDE ABAJO
////


// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);
      
      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }
     
 // tapa inferior
if (fabs(perfil[0].x)>0.0 && tapa==1)
  {
	//creamos el vertice que sera el pico en y
	vertice_aux.x = 0.0; 
	vertice_aux.y = perfil[0].y;  
	vertice_aux.z = 0.0;  
	vertices.push_back(vertice_aux); 

	for (i = 0; i < num; i++)
	{
	    cara_aux._0 = vertices.size() - 1;  //eje
	    cara_aux._1 = i * num_aux;    
	    cara_aux._2 = ((i + 1) % num) * num_aux;  
		
	    caras.push_back(cara_aux);
	}	 
  }
 
 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0 && tapa==1)
  {
	//creamos el vertice que sera el pico en y
	vertice_aux.x = 0.0;  
	vertice_aux.y = perfil[num_aux - 1].y;    
	vertice_aux.z = 0.0;
	vertices.push_back(vertice_aux);  

	for (i = 0; i < num; i++)
	{
		cara_aux._0 = vertices.size() - 1;  //eje 
		cara_aux._1 = (i * num_aux) + (num_aux - 1);   
		cara_aux._2 = (((i + 1) % num) * num_aux) + (num_aux - 1); 

		caras.push_back(cara_aux); 
	}
  }
}

void _rotacion::parametros_ply(char *archivo, int num){
	int n_ver;

	vector<float> ver_ply ;
	vector<int>   car_ply ;

	vector<_vertex3f> perfil;
	
	_file_ply::read(archivo, ver_ply, car_ply );

	n_ver=ver_ply.size()/3;

	printf("Number of vertices=%d\n", n_ver);

	perfil.resize(n_ver);

	_vertex3f ver_aux;

	for (int i = 0; i < n_ver; i++)
	{
  		ver_aux.x = ver_ply[i*3];
  		ver_aux.y = ver_ply[i*3+1];
  		ver_aux.z = ver_ply[i*3+2];

  		perfil[i] = ver_aux;
	}

	parametros(perfil, num, 1);
}


_cono::_cono()
{
		//LOS PERFILES SE EMPIEZAN DESDE ABAJO
	vector<_vertex3f> perfilcono;
	_vertex3f aux;
	
	aux.x = 1.0; aux.y = -1.0; aux.z = 0.0;
	perfilcono.push_back(aux);
	aux.x = 0.0; aux.y = 1.0; aux.z = 0.0;
	perfilcono.push_back(aux);

	cono.parametros(perfilcono,20,1);
}

void _cono::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	cono.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

_esfera::_esfera()
{
		//LOS PERFILES SE EMPIEZAN DESDE ABAJO
	vector<_vertex3f> perfilesfera;
	_vertex3f aux;
   	for (int i = 0; i < 10; i++)
   	{
		aux.x = 1.2 * sin(M_PI*i / (10-1)); 
    	aux.y = 1.2 * cos(M_PI*i / (10-1)); 
      	aux.z = 0.0;
		perfilesfera.push_back(aux);
	}

   	esfera.parametros(perfilesfera,10,0);
}

void _esfera::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	esfera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}




//************************************************************************
// objeto articulado
//************************************************************************

_extension::_extension()
{
	// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x=0.20;aux.y=-0.06;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.20;aux.y=0.06;aux.z=0.0;
	perfil.push_back(aux);
	rodamiento.parametros(perfil,12,1);
	altura=0.4;
};

void _extension::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glRotatef(90.0,0,1,0);

	glPushMatrix();
	glTranslatef(0,0.5,0.0);
	glScalef(0.3,1.0,0.075);
	base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,1.0,0.0);
	glRotatef(90.0,1,0,0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();


	glPushMatrix();
	glRotatef(90.0,1,0,0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}



_tubo::_tubo()
{
	// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x=0.12;aux.y=-0.4;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.12;aux.y=0.4;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.06;aux.y=0.35;aux.z=0.0;
	perfil.push_back(aux);
	tubo_abierto.parametros(perfil,12,0);
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glRotatef(90.0,1,0,0);
	tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}




_tubo_cerrado::_tubo_cerrado()
{
		// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x=0.20;aux.y=-0.8;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.20;aux.y=0.8;aux.z=0.0;
	perfil.push_back(aux);
	tubo_cerrado.parametros(perfil,12,1);
	
};

void _tubo_cerrado::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glRotatef(90.0,1,0,0);
	tubo_cerrado.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}




_cuerpo::_cuerpo()
{
	// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	//aux.x=0.60;aux.y=-0.3;aux.z=0.0;
	//perfil.push_back(aux);

	aux.x=0.80;aux.y=-0.45;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.80;aux.y=-0.25;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.0;aux.y=-0.15;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=1.1;aux.y=-0.05;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.0;aux.y=0.05;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=1.2;aux.y=0.15;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=1.1;aux.y=0.25;aux.z=0.0;
	perfil.push_back(aux);
	forma.parametros(perfil,8,1);
};

void _cuerpo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	forma.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,-0.45,0.0);
	glRotatef(90.0,0,1,0);
	tubo_cerrado.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

}



_semiesfera::_semiesfera()
{
	float radio = 1;
	int latitud = 10;
	int longitud = 20;

	giro_tubo=0.0;
	giro_tubo_min=-5;
	giro_tubo_max=5;
	translacion_tubo=1.3;
	translacion_tubo_min=1.3;	
	translacion_tubo_max=1.5;	


	//LOS PERFILES SE EMPIEZAN DESDE ABAJO
	vector<_vertex3f> perfilesfera;
	_vertex3f aux;
   	for (int i = 0; i < latitud-3; i++)
   	{
		aux.x = radio * sin(M_PI*i / ((latitud-1)*2)); 
    	aux.y = radio * cos(M_PI*i / ((latitud-1)*2)); 
      	aux.z = 0.0;
		perfilesfera.push_back(aux);
	}
	printf("%f", aux.y);
	aux.y = aux.y - 0.4; 
	perfilesfera.push_back(aux);

	aux.y = aux.y - 0.1; 
	aux.x = aux.x + 0.1;
	perfilesfera.push_back(aux);

	semi_esfera.parametros(perfilesfera, longitud, 0);

};

void _semiesfera::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{	
	glPushMatrix();
	semi_esfera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
	
	//TUBO CENTRAL
	glPushMatrix();
	glRotatef(giro_tubo,1,0,0);

	glPushMatrix();
	glTranslatef(0,0.3,1.0);
	tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);	
	glPopMatrix();
	glPushMatrix();	
	glTranslatef(0,0.3,translacion_tubo);
	glScalef(0.50,0.50,0.50);
	tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);	
	glPopMatrix();
	glPopMatrix();

	//TUBO IZQUIERDO
	glPushMatrix();
	glRotatef(-45.0,0,1,0);
	glRotatef(giro_tubo,1,0,0);
	
	glPushMatrix();
	glTranslatef(0.0,0.3,1.0);	
	tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);	
	glPopMatrix();
	glPushMatrix();	
	glTranslatef(0.0,0.3,translacion_tubo); //XyZ + 0.2121	
	glScalef(0.50,0.50,0.50);
	tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);	
	glPopMatrix();
	glPopMatrix();

	//TUBO DERECHO
	glPushMatrix();
	glRotatef(45.0,0,1,0);
	glRotatef(giro_tubo,1,0,0);

	glPushMatrix();
	glTranslatef(0.0,0.3,1.0);	
	tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);	
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0,0.3,translacion_tubo); //XyZ + 0.2121
	glScalef(0.50,0.50,0.50);
	tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);	
	glPopMatrix();
	glPopMatrix();

		
}



_pie::_pie()
{
	// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x=1.8;aux.y=-0.20;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.8;aux.y=0.0;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.8;aux.y=0.20;aux.z=0.0;
	perfil.push_back(aux);
	rodamiento.parametros(perfil,8,1);
	altura=0.4;
};

void _pie::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

	glPushMatrix();
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();	
	glTranslatef(0.0,0.20,0.0);
	glRotatef(90.0,0,1,0);
	tubo_cerr.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

}


_torreta::_torreta()
{
		rot_y = 0.0;
	rot_z = 0.0;
	giro = 0.0;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glTranslatef(0.0,-1.4035,-0.7035);
	glTranslatef(0.0,-0.20,0.0); 
	pie.draw(modo, r1, g1, b1, r2, g2, b2, grosor);	
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,-0.5,0.0);
	glTranslatef(0.0,-1.20,0.0);
	bisagra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);	
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,rot_y,rot_z);
	
	glPushMatrix();
	glTranslatef(0,-0.25,0.0);
	cuerpo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);	
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(giro,0,1,0);
	semiesfera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);	
	glPopMatrix();
	glPopMatrix();	
}


_bisagra::_bisagra()
{
	angulo = 45;
	giro_bisagra_max = 80;
	giro_bisagra_min = -80;
};

void _bisagra::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	
	glPushMatrix();	
	
	glTranslatef(0.0,1.0-(sin(45*3.1416/180)),-cos(45*3.1416/180));

	glPushMatrix();	
	glTranslatef(-0.86,0,0.0);
	glRotatef(angulo,1,0,0);
	extension.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();	
	glTranslatef(0.86,0,0.0); //+ lo de la rotacion(sin 45 * tamdecubo y  no esfera/2)
	glRotatef(angulo,1,0,0);
	extension.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
	glPopMatrix();

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ILUMINACION
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void _triangulos3D::draw_iluminacion_plana( )
{
	//Comprobacion para calcular normales
	if (!b_normales_caras)
	{
		calcular_normales_caras();
	}
	
	//angulos de reflexion especular de la vista
  	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	//Aplicar sombreado plano	
  	glShadeModel(GL_FLAT);
	
	//Para poder asignar los datos correctamente habilitamos normales e iluminacion
	//glEnable(GL_NORMALIZE);
	glEnable(GL_RESCALE_NORMAL);
  	glEnable(GL_LIGHTING);
	
  	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
  	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
  	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat) brillo);
	
  	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
  	glBegin(GL_TRIANGLES);
	
  	for (int i = 0; i < caras.size(); i++)
	{
		glNormal3fv((GLfloat *) &normales_caras[i]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  	}

  	glEnd();

  	glDisable(GL_LIGHTING);
}

void _triangulos3D::draw_iluminacion_suave( )
{
	//Comprobacion para calcular normales
	if (!b_normales_vertices)
	{
		calcular_normales_vertices();
	}
	
	//angulos de reflexion especular de la vista
  	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	//Aplicar sombreado Gouraud	
  	glShadeModel(GL_SMOOTH);
	
	//Para poder asignar los datos correctamente habilitamos normales e iluminacion
	//glEnable(GL_NORMALIZE);
	glEnable(GL_RESCALE_NORMAL);
  	glEnable(GL_LIGHTING);
	
  	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
  	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
  	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat) brillo);
	
  	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
  	glBegin(GL_TRIANGLES);

  	for (int i = 0; i < caras.size(); i++)
	{
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  	}

  	glEnd();
	
  	glDisable(GL_LIGHTING);
}

void _triangulos3D::calcular_normales_caras()
{
	normales_caras.resize(caras.size());

	for (int i = 0; i < caras.size(); i++)
	{
    	_vertex3f a = vertices[caras[i]._1] - vertices[caras[i]._0];
        _vertex3f b = vertices[caras[i]._2] - vertices[caras[i]._0];
        _vertex3f normal_cara = a.cross_product(b); // producto vectorial

    	normales_caras[i] = normal_cara;
		normales_caras[i].normalize(); // normalizacion
  	}

  	b_normales_caras = true;
}

void _triangulos3D::calcular_normales_vertices()
{

	if (!b_normales_caras)
	{
		calcular_normales_caras();
	}

	normales_vertices.resize(vertices.size());

	for (int i = 0; i < vertices.size(); i++)
	{
		normales_vertices[i].x = 0.0;
		normales_vertices[i].y = 0.0;
		normales_vertices[i].z = 0.0;
	}
	
	for (int i = 0; i < caras.size(); i++)
	{
		normales_vertices[caras[i]._0] += normales_caras[i];
		normales_vertices[caras[i]._1] += normales_caras[i];
		normales_vertices[caras[i]._2] += normales_caras[i];
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		normales_vertices[i].normalize(); // normalizacion
	}

	b_normales_vertices = true;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//LUCES
//////////////////////////////////////////////////////////////////////////////////////////////////////////

_luces::_luces(GLenum l, _vertex4f lAmbiente, _vertex4f lDifusa, _vertex4f lEspecular, GLfloat lBrillo, _vertex4f lPosicion){
	luz = l;
	ambiente = lAmbiente;
	difusa = lDifusa;
	especular = lEspecular;
	brillo = lBrillo;
	posicion = lPosicion;
	cont = 0;
}

void _luces::habilitar()
{
	//habilitar iluminacion y luces
	glEnable(GL_LIGHTING);
	glEnable(luz);
	
	glLightfv(luz, GL_AMBIENT, (GLfloat*) &ambiente);
	glLightfv(luz, GL_DIFFUSE, (GLfloat*) &difusa);
	glLightfv(luz, GL_SPECULAR, (GLfloat*) &especular);
	glLightf(luz, GL_SHININESS, (GLfloat) brillo);
	glLightfv(luz, GL_POSITION, (GLfloat*) &posicion);
}

void _luces::deshabilitar()
{
	//deshabilitar iluminacion y luces
	glDisable(luz);
	glDisable(GL_LIGHTING);	
}

void _luces::giro_auto()
{

	posicion[0] = 10 * sin(M_PI*cont / (100-1)); 
	posicion[2] = 10 * cos(M_PI*cont / (100-1));

	cont++;

	glLightfv(luz, GL_POSITION, (GLfloat*) &posicion);
}

