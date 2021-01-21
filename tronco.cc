#include "tronco.h"
#include "escena.h"

// *****************************************************************************
//
// Clase Brazo
//
// *****************************************************************************

Tronco::Tronco(){
    n_instancias = 20;
    mat_camiseta = new Material(Tupla4f(0.8, 0.8, 0.8, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), 0.0);
    mat_azul = new Material(Tupla4f(0.2, 0.2, 0.8, 0.1), Tupla4f(0.0, 0.0, 0.1, 1.0), Tupla4f(0.0, 0.0, 1.0, 1.0), 0.0);
    mat_piel = new Material(Tupla4f(0.5, 0.2, 0.1, 0.0), Tupla4f(0.0, 0.0, 0.0, 0.0), Tupla4f(0.5, 0.2, 0.1, 0.0), 0.1);

    tronco = new Cubo();
    tronco->modificarColor(Tupla3f{0.0,0.0,0.0});
    ingle = new Cubo();
    ingle->modificarColor(Tupla3f{0.0,0.0,0.0});
    cuello = new Cilindro(7, n_instancias, 3, 1, true, true, ROTACIONY, false, ESFERICAS);
    cuello->modificarColor(Tupla3f{0.0,0.0,0.0});

    this->resetMaterialPersonaje();
}

void Tronco::draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipo_iluminacion){
    glPushMatrix();
        glTranslatef(0.0, 125.0, 0.0);
        glScalef(0.4, 0.2, 0.4);
        // cuello->cambiarMaterial(mat_piel);
        cuello->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, num_instancias, tipo_iluminacion);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 70.0, 0.0);
        glScalef(1.0, 1.75, 0.5);
        // tronco->cambiarMaterial(mat_camiseta);
        tronco->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipo_iluminacion);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, -10.0, 0.0);
        glScalef(0.25, 0.25, 0.25);
        // ingle->cambiarMaterial(mat_azul);
        ingle->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipo_iluminacion);
    glPopMatrix();
}

void Tronco::setMaterialSeleccion ( Material *mat ){
    cuello->cambiarMaterial(mat);
    tronco->cambiarMaterial(mat);
    ingle->cambiarMaterial(mat);
}

void Tronco::resetMaterialPersonaje(){
    cuello->cambiarMaterial(mat_piel);
    tronco->cambiarMaterial(mat_camiseta);
    ingle->cambiarMaterial(mat_azul);
}
