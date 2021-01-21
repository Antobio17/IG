// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cabeza.h
// -- declaraciones de clase Cabeza que formará parte del personaje
//
// #############################################################################

#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "aux.h"
#include "esfera.h"
#include "material.h"

class Cabeza
{
    public:
        Cabeza();
        void draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipoIluminacion);
        void setMaterialSeleccion ( Material *mat );
        void resetMaterialPersonaje();
    protected:
        Esfera *cabeza = nullptr;
        Esfera *ojoIzq = nullptr;
        Esfera *ojoDch = nullptr;
        //Materiales
        Material * mat_piel = nullptr;
        Material * mat_blanco = nullptr;
        
    private:
        int n_instancias;      // Numero de instancias para los objetos revolucion
} ;


#endif