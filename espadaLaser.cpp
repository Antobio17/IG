#include "espadaLaser.h"
#include "escena.h"

// *****************************************************************************
//
// Clase EspadaLaser
//
// *****************************************************************************

EspadaLaser::EspadaLaser(){
    n_instancias = 20;
    mat_negro = new Material(Tupla4f(0.2, 0.2, 0.2, 0.2), Tupla4f(0.0, 0.0, 0.0, 0.0), Tupla4f(0.2, 0.2, 0.2, 1.0), 0.5);
    mat_morado = new Material(Tupla4f(0.5, 0.1, 0.9, 0.0), Tupla4f(0.0, 0.0, 0.0, 0.0), Tupla4f(0.5, 0.1, 0.9, 0.0), 0.3);

    empuniadura = new Cilindro(7, n_instancias, 3, 1, true, true, ROTACIONY, false, ESFERICAS);
    empuniadura->modificarColor(Tupla3f{0.0,0.0,0.0});
    laser = new Cilindro(7, n_instancias, 3, 1, true, true, ROTACIONY, false, ESFERICAS);
    laser->modificarColor(Tupla3f{0.0,0.0,0.0});

    escalado = 0;

    this->resetMaterialPersonaje();
}

void EspadaLaser::draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipo_iluminacion){
    glPushMatrix();
        // Empuñadura
        glTranslatef(0.0, -19.0, 0.0);
        glPushMatrix();
            glScalef(0.1, 0.05, 0.1);
            // empuniadura->cambiarMaterial(mat_negro);
            empuniadura->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, n_instancias, tipo_iluminacion);
        glPopMatrix();
        glPushMatrix();
            glScalef(0.07, 0.3, 0.07);
            // empuniadura->cambiarMaterial(mat_negro);
            empuniadura->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, n_instancias, tipo_iluminacion);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, 36.0, 0.0);
            glScalef(0.1, 0.05, 0.1);
            empuniadura->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, n_instancias, tipo_iluminacion);
        glPopMatrix();

        //Laser
        glPushMatrix();
            glTranslatef(0.0, 10.0, 0.0);
            glScalef(0.06, escalado, 0.06);
            // laser->cambiarMaterial(mat_morado);
            laser->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, n_instancias, tipo_iluminacion);
        glPopMatrix();
    glPopMatrix();
}

void EspadaLaser::modificarEscaladoLaser(float x){
    escalado += x;
    if(escalado >= 1.5)
        escalado = 1.5;
    else if(escalado <= 0)
        escalado = 0;
}

float EspadaLaser::getEscaladoLaser(){ return escalado; }

void EspadaLaser::setMaterialSeleccion ( Material *mat ){
    empuniadura->cambiarMaterial(mat);
    laser->cambiarMaterial(mat);
}

void EspadaLaser::resetMaterialPersonaje(){
    empuniadura->cambiarMaterial(mat_negro);
    laser->cambiarMaterial(mat_morado);
}