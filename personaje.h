// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: personaje.h
// -- declaraciones de clase Personaje
//
// #############################################################################

#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED

#include "aux.h"
#include "brazo.h"
#include "tronco.h"
#include "cabeza.h"
#include "pierna.h"
#include "espadaLaser.h"

class Personaje
{
    public:
        Personaje();
        void draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipo_iluminacion);
        void modificarGiroAlphaHombroDerecho(float x);
        void modificarGiroBetaHombroDerecho(float x);
        void modificarGiroAlphaHombroIzquierdo(float x);
        void modificarGiroBetaHombroIzquierdo(float x);
        void modificarGiroAlphaCodoDerecho(float x);
        void modificarGiroBetaCodoDerecho(float x);
        void modificarGiroAlphaCodoIzquierdo(float x);
        void modificarGiroBetaCodoIzquierdo(float x);
        void modificarGiroAlphaGluteoDerecho(float x);
        void modificarGiroBetaGluteoDerecho(float x);
        void modificarGiroAlphaGluteoIzquierdo(float x);
        void modificarGiroBetaGluteoIzquierdo(float x);
        void modificarGiroAlphaRodillaDerecho(float x);
        void modificarGiroBetaRodillaDerecho(float x);
        void modificarGiroAlphaRodillaIzquierdo(float x);
        void modificarGiroBetaRodillaIzquierdo(float x);
        void modificarEscaladoLaser(float x);
        void modificarAlphaEspada(float x);
        void modificarBetaEspada(float x);
        float getAlphaHombroDerecho();
        float getBetaHombroDerecho();
        float getAlphaHombroIzquierdo();
        float getBetaHombroIzquierdo();
        float getAlphaCodoDerecho();
        float getBetaCodoDerecho();
        float getAlphaCodoIzquierdo();
        float getBetaCodoIzquierdo();
        float getAlphaGluteoDerecho();
        float getBetaGluteoDerecho();
        float getAlphaGluteoIzquierdo();
        float getBetaGluteoIzquierdo();
        float getAlphaRodillaDerecho();
        float getBetaRodillaDerecho();
        float getAlphaRodillaIzquierdo();
        float getBetaRodillaIzquierdo();
        float getEscaladoLaser();
        float getAlphaEspada();
        float getBetaEspada();
        void setMaterialSeleccion ( Material *mat );
        void resetMaterialPersonaje();
    protected:
        Cabeza *cabeza = nullptr;
        Tronco *tronco = nullptr;
        Brazo *brazoIzq = nullptr, *brazoDch = nullptr;
        Pierna *piernaIzq  = nullptr, *piernaDch = nullptr;
        EspadaLaser *espadaLaser = nullptr;
    private:
        float alpha_espada, beta_espada;
} ;


#endif
