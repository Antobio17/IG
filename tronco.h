// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: tronco.h
// -- declaraciones de clase Tronco que formará parte del personaje
//
// #############################################################################

#ifndef TRONCO_H_INCLUDED
#define TRONCO_H_INCLUDED

#include "aux.h"
#include "cubo.h"
#include "cilindro.h"
#include "material.h"

class Tronco
{
    public:
        Tronco();
        void draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipoIluminacion);
        void setMaterialSeleccion ( Material *mat );
        void resetMaterialPersonaje();
    protected:
        Cubo *tronco = nullptr; 
        Cubo *ingle = nullptr;
        Cilindro *cuello = nullptr;
        //Materiales
        Material * mat_camiseta = nullptr;
        Material * mat_azul = nullptr;
        Material * mat_piel = nullptr;
    private:
        int n_instancias;      // Numero de instancias para los objetos revolucion
} ;


#endif