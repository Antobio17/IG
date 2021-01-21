// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

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

class Cuadro : public Malla3D
{
    public:
        Cuadro(float width=80, float height=40) ;
        void generarCoordenadasTextura();
} ;




#endif