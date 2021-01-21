// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: brazo.h
// -- declaraciones de clase Brazo que formará parte del personaje
//
// #############################################################################

#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "esfera.h"
#include "material.h"

class Brazo
{
    public:
        Brazo();
        void draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipoIluminacion);
        void modificarGiroAlphaHombro(float x);
        void modificarGiroBetaHombro(float x);
        void modificarGiroAlphaCodo(float x);
        void modificarGiroBetaCodo(float x);
        float getAlphaHombro();
        float getBetaHombro();
        float getAlphaCodo();
        float getBetaCodo();
        void setMaterialSeleccion ( Material *mat );
        void resetMaterialPersonaje();
    protected:
        Cilindro *antebrazo = nullptr; 
        Cilindro *brazo = nullptr; 
        Esfera *hombro = nullptr; 
        Esfera *codo = nullptr;
        Esfera *mano = nullptr;
        //Materiales
        Material * mat_camiseta = nullptr;
        Material * mat_azul = nullptr;
        Material * mat_piel = nullptr;
    private:
        int n_instancias;      // Numero de instancias para los objetos revolucion
        float alpha_hombro, beta_hombro;
        float alpha_codo, beta_codo;
} ;


#endif