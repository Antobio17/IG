// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzDireccional.h

//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

// *****************************************************************************
//
// clases derivadas de Luz (definen constructores específicos)
//
// *****************************************************************************


class LuzPosicional : public Luz
{
        protected:
                Tupla3f posicion;
        public:
                LuzPosicional ( );
                LuzPosicional ( const Tupla3f & posicion, const GLenum & idLuzOpenGL, const Tupla4f & colorAmbiente, const Tupla4f & colorEspecular, const Tupla4f & colorDifuso ) ;
                Tupla3f getPosicion();
                void modificarPosicionX(float x);
                void modificarPosicionY(float y);
                // Sobreescribir activar
                void activar();
};


#endif