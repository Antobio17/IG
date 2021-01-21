// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: material.h
//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material {
    private :
        Tupla4f difuso ;
        Tupla4f especular ;
        Tupla4f ambiente ;
        float brillo ;
    public :
        Material ( );
        Material ( Tupla4f mambiente, Tupla4f mespecular, Tupla4f mdifuso , float mbrillo );
        void aplicar ();
        void cambiarMaterial ( Tupla4f mambiente, Tupla4f mespecular, Tupla4f mdifuso , float mbrillo );
        Tupla4f getAmbiente();
        Tupla4f getEspecular();
        Tupla4f getDifuso();
        float getBrillo();
        void asignar( Material * mat );
};

#endif