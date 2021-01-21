// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: textura.h
// -- declaraciones de clase Textura
//
// #############################################################################

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"
#include <string>

class Textura
{
    public:
        Textura(std::string archivo);
        void activar();
    protected:
        GLuint textura_id = 0;
        std::vector<unsigned char> data;
        int width, height;
} ;


#endif