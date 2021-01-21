// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.h
// -- declaraciones de clase Camara
//
// #############################################################################

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

//typedef enum {ORTOGONAL, PERSPECTIVA} TipoCamara;

class Camara {
    private:
        Tupla3f eye ;
        Tupla3f at ;
        Tupla3f up ;
        int tipo ; // 0: ORTOGONAL o 1: PERSPECTIVA
        float top, bottom, left , right , near , far ; // o bien aspect, fov, near, far;
    public:
        Camara ( const Tupla3f & eye, const Tupla3f & at, const Tupla3f & up, const int & tipo, const float near, const float far ) ; // con los parametros necesarios
        
        void rotarXExaminar ( float angle );
        void rotarYExaminar ( float angle );
        void rotarZExaminar ( float angle );

        void rotarXFirstPerson ( float angle );
        void rotarYFirstPerson ( float angle );
        void rotarZFirstPerson ( float angle );

        void girar (int x, int y);
        void girarSeleccionado (int x, int y);
        void mover ( float direccion );
        void zoom ( float factor );
        void setObserver ();
        void setProyeccion ();
        void setLeft( float valor );
        void setRight( float valor );
        void setTop( float valor );
        void setBottom( float valor );
        void setAt( Tupla3f coor );
};

#endif