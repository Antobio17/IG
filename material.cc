#include "aux.h"
#include "material.h"

// *****************************************************************************
//
// Clase Material (Práctica 3)
//
// *****************************************************************************

Material::Material( ) { 
   // Material por defecto :
   ambiente  = {0.2, 0.2, 0.2, 1.0f};
   difuso    = {0.8, 0.8, 0.8, 1.0f};
   especular = {0.0, 0.0, 0.0, 1.0f};
   brillo    = 0;
}

Material::Material( Tupla4f mambiente, Tupla4f mespecular, Tupla4f mdifuso , float mbrillo ) {
    difuso = mdifuso;
    especular = mespecular;
    ambiente = mambiente;
    brillo = mbrillo;
}

void Material::aplicar() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
}

void Material::cambiarMaterial ( Tupla4f mambiente, Tupla4f mespecular, Tupla4f mdifuso , float mbrillo ){
    difuso = mdifuso;
    especular = mespecular;
    ambiente = mambiente;
    brillo = mbrillo;
}

Tupla4f Material::getAmbiente(){
    return ambiente;
}

Tupla4f Material::getEspecular(){
    return especular;
}

Tupla4f Material::getDifuso(){
    return difuso;
}

float Material::getBrillo(){
    return brillo;
}

void Material::asignar( Material * mat ){
    difuso = mat->getDifuso();
    especular = mat->getEspecular(); 
    ambiente = mat->getAmbiente();
    brillo = mat->getBrillo();
}