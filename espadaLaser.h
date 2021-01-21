// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: brazo.h
// -- declaraciones de clase Espada que formará parte del personaje
//
// #############################################################################

#ifndef ESPADALASER_H_INCLUDED
#define ESPADALASER_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "luzPosicional.h"


class EspadaLaser
{
    public:
        EspadaLaser();
        void draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipoIluminacion);
        void modificarEscaladoLaser(float x);
        void modificarAlphaEspada(float x);
        float getEscaladoLaser();
        void setMaterialSeleccion ( Material *mat );
        void resetMaterialPersonaje();
    protected:
        Cilindro *empuniadura = nullptr; 
        Cilindro *laser = nullptr; 
        //Materiales
        Material * mat_negro = nullptr;
        Material * mat_morado = nullptr;
    private:
        int n_instancias;      // Numero de instancias para los objetos revolucion
        float escalado;
} ;


#endif