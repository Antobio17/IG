// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef SKYBOX_H_INCLUDED
#define SKYBOX_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class SkyBox : public Malla3D
{
    public:
        SkyBox(float lado=1000) ;
        void generarCoordenadasTextura();
} ;




#endif