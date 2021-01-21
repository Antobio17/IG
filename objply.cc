#include "aux.h"
#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );
   generarColoresBasicos();

   for(int i = 0; i < f.size(); i++){
      if(i % 2 == 0)
         f_pares.push_back(f[i]);
      else
         f_impares.push_back(f[i]);
   }

   for(int i = 0; i < v.size(); i++){
      v[i][X] *= 20;
      v[i][Y] *= 20;
      v[i][Z] *= 20;
   }

   calcular_normales();
   mat = new Material(Tupla4f(0.0, 0.2, 0.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(0.6, 1.0, 0.1, 1.0), 0.7);
   //mat = new Material();
}


