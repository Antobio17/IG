// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: objetorevolucion.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

typedef enum {ROTACIONX, ROTACIONY, ROTACIONZ} AnguloRotacion;

class ObjRevolucion : public Malla3D
{
    public:
        ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, const bool tapa_inferior, const bool tapa_superior, const AnguloRotacion angulo_rotacion, const bool coor_texturas, modoGenTextura modoTexturas);
        ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, const bool tapa_inferior, const bool tapa_superior, const AnguloRotacion angulo_rotacion, const bool coor_texturas, modoGenTextura modoTexturas);

        // Funcion que genera las coordenadas de textura
        void generarCoordenadasTextura(modoGenTextura modoTexturas, int num_instancias);
        // Función sobrecargada de Malla.h que redibuja el objeto
        // está función llama a 'draw_ModoInmediato' (modo inmediato)
        // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
        void draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipoIluminacion) ;
    protected:
        void crearMalla(const std::vector<Tupla3f> perfil_original, const int num_instancias, const bool tapa_inferior, const bool tapa_superior, const AnguloRotacion angulo_rotacion);
} ;




#endif
