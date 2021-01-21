#ifndef RUEDA_H_INCLUDED
#define RUEDA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Rueda : public ObjRevolucion
{
    public :
        Rueda (const int num_instancias_perf, const float radio, const float anchura, const bool tapa_inferior, const bool tapa_superior, const AnguloRotacion angulo_rotacion, const bool coor_texturas );
};

#endif