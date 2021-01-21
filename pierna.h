// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: pierna.h
// -- declaraciones de clase Pierna que formará parte del personaje
//
// #############################################################################

#ifndef PIERNA_H_INCLUDED
#define PIERNA_H_INCLUDED

#include "aux.h"
#include "cubo.h"
#include "esfera.h"
#include "objply.h"

class Pierna
{
    public:
        Pierna();
        void draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipoIluminacion);
        void modificarGiroAlphaGluteo(float x);
        void modificarGiroBetaGluteo(float x);
        void modificarGiroAlphaRodilla(float x);
        void modificarGiroBetaRodilla(float x);
        float getAlphaGluteo();
        float getBetaGluteo();
        float getAlphaRodilla();
        float getBetaRodilla();
        void setMaterialSeleccion ( Material *mat );
        void resetMaterialPersonaje();
    protected:
        Esfera *gluteo = nullptr; 
        Esfera *rodilla = nullptr; 
        Cubo *cuadricep = nullptr; 
        Cubo *gemelo = nullptr;
        ObjPLY *pie = nullptr;
        //Materiales
        Material * mat_negro = nullptr;
        Material * mat_azul = nullptr;
        Material * mat_piel = nullptr;
    private:
        int n_instancias;      // Numero de instancias para los objetos revolucion
        float alpha_gluteo, beta_gluteo;
        float alpha_rodilla, beta_rodilla;
} ;


#endif