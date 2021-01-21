// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {GLDRAW, VBO} modoDibujado;
typedef enum {ACTIVADO, DESACTIVADO} carasOcultas;
typedef enum {ESFERICAS, CILINDRICAS} modoGenTextura;

class Malla3D
{
   public:

      // dibuja el objeto en modo inmediato
      void draw_ModoInmediato(bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez);
      // dibuja el objeto en modo inmediato cuando la luz está activada
      void draw_ModoInmediato(GLenum tipoIluminacion);

      // dibuja el objeto en modo diferido (usando VBOs)
      void draw_ModoDiferido(bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez);
      // dibuja el objeto en modo diferido (usando VBOs) cuando la luz está activada
      void draw_ModoDiferido(GLenum tipoIluminacion);

      // función que redibuja el objeto
      // está función llama a 'draw_ModoInmediato' (modo inmediato)
      // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
      void draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, GLenum tipoIluminacion) ;
      
      // Generar los 3 colores básicos RGB
      void generarColoresBasicos();

      // Creación de VBOs para el modo diferido
      GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

      // Aplicar
      void cambiarMaterial ( Material *mat );

      // Crear textura
      void setTextura(const std::string archivo);

      // Modificar TAM para tapas activadas o desactivadas
      void modificarTAM(bool tapa_superior, bool tapa_inferior, int num_instancias, bool modoAjedrez);

      void modificarColor(Tupla3f c);

      Material* getMaterial();
   
   protected:

      void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

      std::vector<Tupla3f> v ;          // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
      std::vector<Tupla3i> f ;          // una terna de 3 enteros por cada cara o triángulo
      std::vector<Tupla3i> f_pares ;    // una terna de 3 enteros por cada cara o triángulo par
      std::vector<Tupla3i> f_impares ;  // una terna de 3 enteros por cada cara o triángulo impar
      std::vector<Tupla3f> nv ;         // tabla de las normales de vértices
      std::vector<Tupla2f> ct ;         // tabla de las coordenadas de la textura
      
      GLuint id_vbo_ver = 0, id_vbo_tri = 0, id_vbo_tri_pares = 0, id_vbo_tri_impares = 0, id_vbo_color = 0, id_vbo_color_rojo = 0, id_vbo_color_verde = 0, id_vbo_color_azul = 0, id_vbo_nv = 0, id_vbo_text = 0 ;    // Identificadores de VBOs
      
      // completar: tabla de colores, tabla de normales de vértices
      std::vector<Tupla3f> color_rojo;             // tabla de colores
      std::vector<Tupla3f> color_azul;             // tabla de colores
      std::vector<Tupla3f> color_verde;            // tabla de colores
      std::vector<Tupla3f> color;                  // tabla de colores
      int TAM, TAM_PAR, TAM_IMPAR;  // Variable para pintar el numero de triangulos

      Material *mat = nullptr ;    // Material del objeto para cuando se activa la luz en la escena
      Textura *textura = nullptr ;
} ;


#endif
