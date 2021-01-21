// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzDireccional.h

//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

// *****************************************************************************
//
// clases derivadas de Luz (definen constructores específicos)
//
// *****************************************************************************


class LuzDireccional : public Luz
{
    protected :
        float alpha ;
        float beta ;
        void calcularPosicion(float a, float b);

    public :
        // inicializar la fuente de luz
        LuzDireccional ( );
        LuzDireccional ( const Tupla2f & orientacion, const GLenum & idLuzOpenGL, const Tupla4f & colorAmbiente, const Tupla4f & colorEspecular, const Tupla4f & colorDifuso ) ;

        // Sobreescribimos activar
        void activar();

        // Cambiar ángulo:
        void incrementarAlpha();
        void decrementarAlpha();

        void incrementarBeta( float valor );
        void decrementarBeta( float valor );

        void decrementarColorLuz();
        void incrementarColorLuz();
};

#endif