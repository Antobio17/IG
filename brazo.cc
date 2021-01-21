#include "brazo.h"
#include "escena.h"

// *****************************************************************************
//
// Clase Brazo
//
// *****************************************************************************

Brazo::Brazo(){
    n_instancias = 20;
    mat_camiseta = new Material(Tupla4f(0.8, 0.8, 0.8, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), 0.0);
    mat_azul = new Material(Tupla4f(0.2, 0.2, 0.1, 0.1), Tupla4f(0.0, 0.0, 0.1, 1.0), Tupla4f(0.0, 0.0, 1.0, 1.0), 1.0);
    mat_piel = new Material(Tupla4f(0.5, 0.2, 0.1, 0.0), Tupla4f(0.0, 0.0, 0.0, 0.0), Tupla4f(0.5, 0.2, 0.1, 0.0), 0.1);


    hombro = new Esfera(10, n_instancias, 1, ROTACIONY, false, ESFERICAS);
    hombro->modificarColor(Tupla3f{0.0,0.0,0.0});
    codo = new Esfera(10, n_instancias, 1, ROTACIONY, false, ESFERICAS);
    codo->modificarColor(Tupla3f{0.0,0.0,0.0});
    mano = new Esfera(10, n_instancias, 1, ROTACIONY, false, ESFERICAS);
    mano->modificarColor(Tupla3f{0.0,0.0,0.0});
    brazo = new Cilindro(7, n_instancias, 3, 1, true, true, ROTACIONY, false, ESFERICAS);
    brazo->modificarColor(Tupla3f{0.0,0.0,0.0});
    antebrazo = new Cilindro(7, n_instancias, 3, 1, true, true, ROTACIONY, false, ESFERICAS);
    antebrazo->modificarColor(Tupla3f{0.0,0.0,0.0});

    alpha_hombro = 0;
    beta_hombro = 0;
    alpha_codo = 0;
    beta_codo = 0;

    this->resetMaterialPersonaje();
}

void Brazo::draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipo_iluminacion){
    glRotatef(alpha_hombro, 1.0, 0.0, 0.0);
    glRotatef(beta_hombro, 0.0, 0.0, 1.0);
    glPushMatrix();         // Lo contruimos con la esfera en el 0,0,0
        glPushMatrix();
            glScalef(0.3, 0.3, 0.3);
            // hombro->cambiarMaterial(mat_camiseta);
            hombro->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, true, true, n_instancias, tipo_iluminacion);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, -72.5, 0.0);
            glScalef(0.2, 0.6, 0.2);
            // brazo->cambiarMaterial(mat_camiseta);
            brazo->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, n_instancias, tipo_iluminacion);
        glPopMatrix();
    glPopMatrix();

    glTranslatef(0.0, -70.0, 0.0);           // Lo bajamos a su posición de "codo"
    glRotatef(alpha_codo, 1.0, 0.0, 0.0);
    glRotatef(beta_codo, 0.0, 0.0, 1.0);
    glPushMatrix();                          // Lo contruimos con la esfera en el 0,0,0
        glScalef(0.3, 0.3, 0.3);
        // codo->cambiarMaterial(mat_piel);
        codo->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, true, true, n_instancias, tipo_iluminacion);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0, -72.5, 0.0);
        glPushMatrix();
            glScalef(0.2, 0.6, 0.2);
            // antebrazo->cambiarMaterial(mat_piel);
            antebrazo->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, n_instancias, tipo_iluminacion);
        glPopMatrix();
        glPushMatrix();
            glScalef(0.25, 0.25, 0.25);
            // mano->cambiarMaterial(mat_piel);
            mano->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, n_instancias, tipo_iluminacion);
        glPopMatrix();
    glPopMatrix();
}

void Brazo::setMaterialSeleccion ( Material *mat ){
    hombro->cambiarMaterial(mat);
    brazo->cambiarMaterial(mat);
    codo->cambiarMaterial(mat);
    antebrazo->cambiarMaterial(mat);
    mano->cambiarMaterial(mat);
}

void Brazo::resetMaterialPersonaje(){
    hombro->cambiarMaterial(mat_camiseta);
    brazo->cambiarMaterial(mat_camiseta);
    codo->cambiarMaterial(mat_piel);
    antebrazo->cambiarMaterial(mat_piel);
    mano->cambiarMaterial(mat_piel);
}

void Brazo::modificarGiroAlphaHombro(float x){
    alpha_hombro += x;
    // Vamos a simular un giro real del brazo y solo vamos dejar que tenga un rango de movimiento del 45 al -180
    if(alpha_hombro < -45)
        alpha_hombro = -45;
    if(alpha_hombro > 45)
        alpha_hombro = 45;
}

void Brazo::modificarGiroBetaHombro(float x){
    beta_hombro += x;
    //if(beta_hombro > 180)
    //    beta_hombro = 180;
    //if(beta_hombro < 0)
    //    beta_hombro = 0;
}

void Brazo::modificarGiroAlphaCodo(float x){
    alpha_codo += x;
    if(alpha_codo > 0)
        alpha_codo = 0;
    if(alpha_codo < -45)
        alpha_codo = -45;
}

void Brazo::modificarGiroBetaCodo(float x){
    beta_codo += x;
}

float Brazo::getAlphaHombro(){ return alpha_hombro; }
float Brazo::getBetaHombro(){ return beta_hombro; }
float Brazo::getAlphaCodo(){ return alpha_codo; }
float Brazo::getBetaCodo(){ return beta_codo; }