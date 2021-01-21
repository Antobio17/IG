#include "aux.h"
#include "luzDireccional.h"

// *****************************************************************************
//
// Clase LuzDireccional (Práctica 3)
//
// *****************************************************************************

LuzDireccional::LuzDireccional ( ) { }

LuzDireccional::LuzDireccional ( const Tupla2f & orientacion, const GLenum & idLuzOpenGL, const Tupla4f & colorAmbiente, const Tupla4f & colorEspecular, const Tupla4f & colorDifuso ) {
    alpha = orientacion[0];     // Asignamos el valor de alpha
    beta = orientacion[1];      // Asignamos el valor de beta

    id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;

    calcularPosicion(alpha, beta);
}

void LuzDireccional::activar() {
    calcularPosicion(alpha, beta);
    glEnable(id);
    glLightfv(id, GL_AMBIENT, colorAmbiente);
    glLightfv(id, GL_DIFFUSE, colorDifuso);
    glLightfv(id, GL_SPECULAR, colorEspecular);
    glLightfv(id, GL_POSITION, posicion);
}

void LuzDireccional::incrementarAlpha() {
    alpha += 5;
}

void LuzDireccional::decrementarAlpha() { 
    alpha -= 5;
}

void LuzDireccional::incrementarBeta( float valor ) {
    beta += valor;
}

void LuzDireccional::decrementarBeta( float valor ) {
    beta -= valor;
}

void LuzDireccional::calcularPosicion(float a, float b) {
    Tupla4f posicion_orig = posicion;
    posicion[X] = sin(M_PI*a/180) * cos(M_PI*b/180);
    posicion[Y] = sin(M_PI*b/180);
    posicion[Z] = cos(M_PI*a/180) * cos(M_PI*b/180);
    posicion[3] = 0.0;
}

void LuzDireccional::decrementarColorLuz(){
    float modificacion = 0.00002;

    if( colorAmbiente[X] <= 0 )
        colorAmbiente[X] = 0;
    else
        colorAmbiente[X] -= modificacion;
    
    if( colorAmbiente[Y] <= 0 )
        colorAmbiente[Y] = 0;
    else
        colorAmbiente[Y] -= modificacion;

    if( colorAmbiente[Z] <= 0 )
        colorAmbiente[Z] = 0;
    else
        colorAmbiente[Z] -= modificacion;

    if( colorEspecular[X] <= 0 )
        colorEspecular[X] = 0;
    else
        colorEspecular[X] -= modificacion;

    if( colorEspecular[Y] <= 0 )
        colorEspecular[Y] = 0;
    else
        colorEspecular[Y] -= modificacion;

    if( colorEspecular[Z] <= 0 )
        colorEspecular[Z] = 0;
    else
        colorEspecular[Z] -= modificacion;

    if( colorDifuso[X] <= 0 )
        colorDifuso[X] = 0;
    else
        colorDifuso[X] -= modificacion;

    if( colorDifuso[Y] <= 0 )
        colorDifuso[Y] = 0;
    else
        colorDifuso[Y] -= modificacion;

    if( colorDifuso[Z] <= 0 )
        colorDifuso[Z] = 0;
    else
        colorDifuso[Z] -= modificacion;
}

void LuzDireccional::incrementarColorLuz(){
    float modificacion = 0.00002;

    if( colorAmbiente[X] >= 0.8 )
        colorAmbiente[X] = 0.8;
    else
        colorAmbiente[X] += modificacion;
    
    if( colorAmbiente[Y] >= 0.8 )
        colorAmbiente[Y] = 0.8;
    else
        colorAmbiente[Y] += modificacion;

    if( colorAmbiente[Z] >= 0.8 )
        colorAmbiente[Z] = 0.8;
    else
        colorAmbiente[Z] += modificacion;

    if( colorEspecular[X] >= 0.8 )
        colorEspecular[X] = 0.8;
    else
        colorEspecular[X] += modificacion;

    if( colorEspecular[Y] >= 0.8 )
        colorEspecular[Y] = 0.8;
    else
        colorEspecular[Y] += modificacion;

    if( colorEspecular[Z] >= 0.8 )
        colorEspecular[Z] = 0.8;
    else
        colorEspecular[Z] += modificacion;

    if( colorDifuso[X] >= 0.8 )
        colorDifuso[X] = 0.8;
    else
        colorDifuso[X] += modificacion;

    if( colorDifuso[Y] >= 0.8 )
        colorDifuso[Y] = 0.8;
    else
        colorDifuso[Y] += modificacion;

    if( colorDifuso[Z] >= 0.8 )
        colorDifuso[Z] = 0.8;
    else
        colorDifuso[Z] += modificacion;
}