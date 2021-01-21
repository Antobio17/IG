#include "aux.h"
#include "luzPosicional.h"

// *****************************************************************************
//
// Clase LuzDireccional (Práctica 3)
//
// *****************************************************************************

LuzPosicional::LuzPosicional ( ) { }

LuzPosicional::LuzPosicional ( const Tupla3f & posicion, const GLenum & idLuzOpenGL, const Tupla4f & colorAmbiente, const Tupla4f & colorEspecular, const Tupla4f & colorDifuso ) {
    this->posicion = posicion;
    id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
}

void LuzPosicional::activar() {
    glEnable(id);
    glLightfv(id, GL_AMBIENT, colorAmbiente);
    glLightfv(id, GL_DIFFUSE, colorDifuso);
    glLightfv(id, GL_SPECULAR, colorEspecular);
    glLightfv(id, GL_POSITION, posicion);
}

Tupla3f LuzPosicional::getPosicion(){
    return posicion;
}

void LuzPosicional::modificarPosicionX(float x){
    this->posicion[X] += x;
    if(this->posicion[X] <= -250)
        this->posicion[X] = -250;
    if(this->posicion[X] >= 250)
        this->posicion[X] = 250;
}

void LuzPosicional::modificarPosicionY(float y){
    this->posicion[Y] += y;
    if(this->posicion[Y] <= 0)
        this->posicion[Y] = 0;
    if(this->posicion[Y] >= 500)
        this->posicion[Y] = 500;
}
