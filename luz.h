// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h
//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para las luces de la escena
//
// *****************************************************************************

class Luz
{
   public:
      Luz();
      Luz(GLenum idLuz);
      
      void activar();
      void desactivar();
   protected:
      GLenum id;
      Tupla4f posicion;
      Tupla4f colorAmbiente, colorDifuso, colorEspecular;
} ;


#endif