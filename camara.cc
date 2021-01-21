#include "aux.h"
#include "camara.h"

// *****************************************************************************
//
// Clase Camara
//
// *****************************************************************************

// -----------------------------------------------------------------------------
// Constructor

Camara::Camara ( const Tupla3f & eye, const Tupla3f & at, const Tupla3f & up, const int & tipo, const float near, const float far ){
    this->eye   = eye;
	this->at    = at;
	this->up    = up;

	this->tipo  = tipo;

	this->near  = near;
	this->far   = far;
}

void Camara::rotarXExaminar ( float angle ){
    Tupla3f vector = eye - at;  // Vector entre el at y el eye
	float modulo = sqrt(vector.lengthSq());  //lengthSq devuelve el cuadrado de la longitud del vector

	//vector[X] = sin(angle) * vector[X] + cos(angle) * vector[Z];
	vector[Y] = cos(angle) * vector[Y] - sin(angle) * vector[Z];   // Formula para la rotación del vector componente Y
	vector[Z] = sin(angle) * vector[Y] + cos(angle) * vector[Z];   // Formula para la rotación del vector componente Z

	vector = vector.normalized() * modulo;    // Lo convertmios a punto

	eye = vector + at;
	// if(eye[Z] <= 0)
	// 	up[Y] = -1;
	// else
	// 	up[Y] = 1;
}

void Camara::rotarYExaminar ( float angle ){
    Tupla3f vector = eye - at;   // Vector entre el at y el eye
	float modulo = sqrt(vector.lengthSq());  //lengthSq devuelve el cuadrado de la longitud del vector

	vector[X] = cos(angle)*vector[X] + sin(angle) * vector[Z];      // Formula para la rotación del vector componente X
    vector[Z] = -sin(angle) * vector[X] + cos(angle) * vector[Z];   // Formula para la rotación del vector componente Z

	vector = vector.normalized() * modulo;    // Lo convertmios a punto

	eye = vector + at;
}

void Camara::rotarZExaminar ( float angle ){
	Tupla3f vector = eye - at;   // Vector entre el at y el eye
	float modulo = sqrt(vector.lengthSq());   //lengthSq devuelve el cuadrado de la longitud del vector

	vector[X] = cos(angle) * vector[X] - sin(angle) * vector[Y];      // Formula para la rotación del vector componente X
    vector[Y] = sin(angle) * vector[X] + cos(angle) * vector[Y];   // Formula para la rotación del vector componente Z

	vector = vector.normalized() * modulo;    // Lo convertmios a punto

	eye = vector + at;       // Inicio mas el vector direccion
}

// Mismo razonamiento que en el rotarExaminar pero ahora movemos el at (donde esta mirando)
void Camara::rotarXFirstPerson ( float angle ){
	Tupla3f vector = at - eye;   // Vector entre el at y el eye
	float modulo = sqrt(vector.lengthSq());   //lengthSq devuelve el cuadrado de la longitud del vector


	vector[Y] = cos(angle)*vector[Y] - sin(angle) * vector[Z];     // Formula para la rotación del vector componente Y
   	vector[Z] = sin(angle) * vector[Y] + cos(angle) * vector[Z];   // Formula para la rotación del vector componente Z

	vector = vector.normalized() * modulo;    // Lo convertmios a punto


	at = vector + eye;       // Inicio mas el vector direccion
}

void Camara::rotarYFirstPerson ( float angle ){
	Tupla3f vector = at - eye;   // Vector entre el at y el eye
	float modulo = sqrt(vector.lengthSq());   //lengthSq devuelve el cuadrado de la longitud del vector

	vector[X] = cos(angle) * vector[X] + sin(angle) * vector[Z];     // Formula para la rotación del vector componente X
    vector[Z] = -sin(angle) * vector[X] + cos(angle) * vector[Z];    // Formula para la rotación del vector componente Z

	vector = vector.normalized() * modulo;    // Lo convertmios a punto

	at = vector + eye;       // Inicio mas el vector direccion
}

void Camara::rotarZFirstPerson ( float angle ){
	Tupla3f vector = at - eye;   // Vector entre el at y el eye
	float modulo = sqrt(vector.lengthSq());   //lengthSq devuelve el cuadrado de la longitud del vector

	vector[X] = cos(angle) * vector[X] - sin(angle) * vector[Y];    // Formula para la rotación del vector componente X
    vector[Y] = sin(angle) * vector[X] + cos(angle) * vector[Y];    // Formula para la rotación del vector componente Z

	vector = vector.normalized() * modulo;    // Lo convertmios a punto

	at = vector + eye;       // Inicio mas el vector direccion
}

void Camara::girar (int x, int y){
	Tupla3f vector_direccion = at - eye;
	if(vector_direccion[Z] > 0)      // Corregir el invertir vista
		rotarXFirstPerson(y * 0.01);
	else
		rotarXFirstPerson(-y * 0.01);

	rotarYFirstPerson(-x * 0.01);
	//rotarZFirstPerson(-y * x * 0.02);
}

void Camara::girarSeleccionado (int x, int y){
	Tupla3f vector_direccion = eye - at;
	rotarXExaminar(-y * 0.01);
	//rotarZExaminar(y * 0.02);
	//rotarXExaminar(-y * 0.02);
	rotarYExaminar(-x * 0.01);
	// if(vector_direccion[X] > 0 && vector_direccion[Z] > 0)      // Corregir el invertir vista
	// 	rotarZExaminar(y * 0.02);
	// else if(vector_direccion[X] < 0 && vector_direccion[Z] < 0)
	// 	rotarZExaminar(y * 0.02);
	// else if(vector_direccion[X] < 0 && vector_direccion[Z] > 0)
	// 	rotarZExaminar(-y * 0.02);
	// else if(vector_direccion[X] > 0 && vector_direccion[Z] < 0)
	// 	rotarZExaminar(-y * 0.02);
}

void Camara::mover ( float direccion ){
	if( direccion == 0 ){
		Tupla3f vector = at - eye;   // Vector entre el at y el eye
		at = {at[X]+vector[X]/100, at[Y] + vector[Y]/100, at[Z] + vector[Z]/100};
		eye = {eye[X]+vector[X]/100, eye[Y] + vector[Y]/100, eye[Z] + vector[Z]/100};
	}else if( direccion == 1 ){
		Tupla3f vector = eye - at;   // Vector entre el at y el eye
		at = {at[X]+vector[X]/100, at[Y] + vector[Y]/100, at[Z] + vector[Z]/100};
		eye = {eye[X]+vector[X]/100, eye[Y] + vector[Y]/100, eye[Z] + vector[Z]/100};
	}else if( direccion == 2 ){
		Tupla3f vector = eye - at;   // Vector entre el at y el eye
		Tupla3f vector_perpendicular = {vector[Y]*up[Z]-vector[Z]*up[Y], vector[Z]*up[X]-vector[X]*up[Z], vector[X]*up[Y]-vector[Y]*up[X]};
		at = {at[X]+vector_perpendicular[X]/80, at[Y] + vector_perpendicular[Y]/80, at[Z] + vector_perpendicular[Z]/80};
		eye = {eye[X]+vector_perpendicular[X]/80, eye[Y] + vector_perpendicular[Y]/80, eye[Z] + vector_perpendicular[Z]/80};
	}else if( direccion == 3 ){
		Tupla3f vector = eye - at;   // Vector entre el at y el eye
		Tupla3f vector_perpendicular = {up[Y]*vector[Z]-up[Z]*vector[Y], up[Z]*vector[X]-up[X]*vector[Z], up[X]*vector[Y]-up[Y]*vector[X]};
		at = {at[X]+vector_perpendicular[X]/80, at[Y] + vector_perpendicular[Y]/80, at[Z] + vector_perpendicular[Z]/80};
		eye = {eye[X]+vector_perpendicular[X]/80, eye[Y] + vector_perpendicular[Y]/80, eye[Z] + vector_perpendicular[Z]/80};
	}
}

void Camara::zoom ( float factor ){
    left *= factor;
	right *= factor;
	bottom *= factor;
	top *= factor;
}

void Camara::setObserver () { 
    gluLookAt(eye[X], eye[Y], eye[Z], at[X], at[Y], at[Z], up[X], up[Y], up[Z] );
}

void Camara::setProyeccion (){
    if (tipo == 0){
		glOrtho( left, right, bottom, top, near, far );
	} else if (tipo == 1) {
		glFrustum( left, right, bottom, top, near, far );
	}
}

void Camara::setLeft( float valor ){
    left = valor;
}

void Camara::setRight( float valor ){
    right = valor;
}

void Camara::setTop( float valor ){
    top = valor;
}

void Camara::setBottom( float valor ){
    bottom = valor;
}

void Camara::setAt( Tupla3f coor ){
	at = coor;
}