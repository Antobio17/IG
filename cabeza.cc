#include "cabeza.h"
#include "escena.h"

// *****************************************************************************
//
// Clase Brazo
//
// *****************************************************************************

Cabeza::Cabeza(){
    n_instancias = 20;
    mat_piel = new Material(Tupla4f(0.5, 0.2, 0.1, 0.0), Tupla4f(0.0, 0.0, 0.0, 0.0), Tupla4f(0.5, 0.2, 0.1, 0.0), 0.1);
    mat_blanco = new Material(Tupla4f(0.3, 0.3, 0.3, 0.1), Tupla4f(0.1, 0.1, 0.1, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), 1.0);

    cabeza = new Esfera(10, n_instancias, 1, ROTACIONY, false, ESFERICAS);
    cabeza->modificarColor(Tupla3f{0.0,0.0,0.0});
    ojoDch = new Esfera(10, n_instancias, 1, ROTACIONY, false, ESFERICAS);
    ojoDch->modificarColor(Tupla3f{0.0,0.0,0.0});
    ojoIzq = new Esfera(10, n_instancias, 1, ROTACIONY, false, ESFERICAS);
    ojoIzq->modificarColor(Tupla3f{0.0,0.0,0.0});

    this->resetMaterialPersonaje();
}

void Cabeza::draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipo_iluminacion){
    glPushMatrix();
        glScalef(0.8, 0.7, 0.8);
        // cabeza->cambiarMaterial(mat_piel);
        cabeza->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, true, true, num_instancias, tipo_iluminacion);
    glPopMatrix();
}

void Cabeza::setMaterialSeleccion ( Material *mat ){
    cabeza->cambiarMaterial(mat);
}

void Cabeza::resetMaterialPersonaje(){
    cabeza->cambiarMaterial(mat_piel);
}
