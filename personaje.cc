#include "personaje.h"
#include "escena.h"

// *****************************************************************************
//
// Clase Personaje
//
// *****************************************************************************

Personaje::Personaje(){
    cabeza = new Cabeza();
    tronco = new Tronco();
    brazoDch = new Brazo();
    brazoIzq = new Brazo();
    piernaDch = new Pierna();
    piernaIzq = new Pierna();
    espadaLaser = new EspadaLaser();
    alpha_espada = 90;
    beta_espada = 0;
}

void Personaje::draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipo_iluminacion){
    // Cabeza
    glPushMatrix();
        glTranslatef(0.0, 170.0, 0.0);
        cabeza->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, num_instancias, tipo_iluminacion);
    glPopMatrix();
    //Tronco
    glPushMatrix();
        tronco->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, num_instancias, tipo_iluminacion);
    glPopMatrix();
    // Brazos
    glPushMatrix();
        glPushMatrix();
            glTranslatef(52.5, 120.0, 0.0);
            brazoDch->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, num_instancias, tipo_iluminacion);
            glPushMatrix();
                glTranslatef(0.0, -75.0, 0.0);
                glRotatef(alpha_espada, 1.0, 0.0, 0.0);
                glRotatef(beta_espada, 0.0, 0.0, 1.0);
                espadaLaser->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, num_instancias, tipo_iluminacion);  
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-52.5, 120.0, 0.0);
            brazoIzq->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, num_instancias, tipo_iluminacion);
        glPopMatrix();
    glPopMatrix();  
    // Piernas
    glPushMatrix();
        glPushMatrix();
            glTranslatef(26.0, -15.0, 0.0);
            piernaDch->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, num_instancias, tipo_iluminacion);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-26.0, -15.0, 0.0);
            piernaIzq->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapa_inferior, tapa_superior, num_instancias, tipo_iluminacion);
        glPopMatrix();
    glPopMatrix();
}

void Personaje::modificarAlphaEspada(float x){
   alpha_espada += x; 
}

void Personaje::modificarBetaEspada(float x){
   beta_espada += x; 
   if(beta_espada <= -45)
        beta_espada = -45;
    if(beta_espada >= 45)
        beta_espada = 45;
}

void Personaje::setMaterialSeleccion ( Material *mat ){
    cabeza->setMaterialSeleccion(mat);
    brazoDch->setMaterialSeleccion(mat);
    brazoIzq->setMaterialSeleccion(mat);
    piernaDch->setMaterialSeleccion(mat);
    piernaIzq->setMaterialSeleccion(mat);
    tronco->setMaterialSeleccion(mat);
    espadaLaser->setMaterialSeleccion(mat);
}

void Personaje::resetMaterialPersonaje(){
    cabeza->resetMaterialPersonaje();
    brazoDch->resetMaterialPersonaje();
    brazoIzq->resetMaterialPersonaje();
    piernaDch->resetMaterialPersonaje();
    piernaIzq->resetMaterialPersonaje();
    tronco->resetMaterialPersonaje();
    espadaLaser->resetMaterialPersonaje();
}

void Personaje::modificarEscaladoLaser(float x){
    espadaLaser->modificarEscaladoLaser(x);
}

void Personaje::modificarGiroAlphaHombroDerecho(float x){
    brazoDch->modificarGiroAlphaHombro(x);
}

void Personaje::modificarGiroBetaHombroDerecho(float x){
    brazoDch->modificarGiroBetaHombro(x);
}

void Personaje::modificarGiroAlphaHombroIzquierdo(float x){
    brazoIzq->modificarGiroAlphaHombro(x);
}

void Personaje::modificarGiroBetaHombroIzquierdo(float x){
    brazoIzq->modificarGiroBetaHombro(x);
}

void Personaje::modificarGiroAlphaCodoDerecho(float x){
    brazoDch->modificarGiroAlphaCodo(x);
}

void Personaje::modificarGiroBetaCodoDerecho(float x){
    brazoDch->modificarGiroBetaCodo(x);
}

void Personaje::modificarGiroAlphaCodoIzquierdo(float x){
    brazoIzq->modificarGiroAlphaCodo(x);
}

void Personaje::modificarGiroBetaCodoIzquierdo(float x){
    brazoIzq->modificarGiroBetaCodo(x);
}

void Personaje::modificarGiroAlphaGluteoDerecho(float x){
    piernaDch->modificarGiroAlphaGluteo(x);
}

void Personaje::modificarGiroBetaGluteoDerecho(float x){
    piernaDch->modificarGiroBetaGluteo(x);
}

void Personaje::modificarGiroAlphaGluteoIzquierdo(float x){
    piernaIzq->modificarGiroAlphaGluteo(x);
}

void Personaje::modificarGiroBetaGluteoIzquierdo(float x){
    piernaIzq->modificarGiroBetaGluteo(x);
}

void Personaje::modificarGiroAlphaRodillaDerecho(float x){
    piernaDch->modificarGiroAlphaRodilla(x);
}

void Personaje::modificarGiroBetaRodillaDerecho(float x){
    piernaDch->modificarGiroBetaRodilla(x);
}

void Personaje::modificarGiroAlphaRodillaIzquierdo(float x){
    piernaIzq->modificarGiroAlphaRodilla(x);
}

void Personaje::modificarGiroBetaRodillaIzquierdo(float x){
    piernaIzq->modificarGiroBetaRodilla(x);
}

float Personaje::getAlphaHombroDerecho(){ return brazoDch->getAlphaHombro(); }
float Personaje::getBetaHombroDerecho(){ return brazoDch->getBetaHombro(); }
float Personaje::getAlphaHombroIzquierdo(){ return brazoIzq->getAlphaHombro(); }
float Personaje::getBetaHombroIzquierdo(){ return brazoIzq->getBetaHombro(); }
float Personaje::getAlphaCodoDerecho(){ return brazoDch->getAlphaCodo(); }
float Personaje::getBetaCodoDerecho(){ return brazoDch->getBetaCodo(); }
float Personaje::getAlphaCodoIzquierdo(){ return brazoIzq->getAlphaCodo(); }
float Personaje::getBetaCodoIzquierdo(){ return brazoIzq->getBetaCodo(); }
float Personaje::getAlphaGluteoDerecho(){ return piernaDch->getAlphaGluteo(); }
float Personaje::getBetaGluteoDerecho(){ return piernaDch->getBetaGluteo(); }
float Personaje::getAlphaGluteoIzquierdo(){ return piernaIzq->getAlphaGluteo(); }
float Personaje::getBetaGluteoIzquierdo(){ return piernaIzq->getBetaGluteo(); }
float Personaje::getAlphaRodillaDerecho(){ return piernaDch->getAlphaRodilla(); }
float Personaje::getBetaRodillaDerecho(){ return piernaDch->getBetaRodilla(); }
float Personaje::getAlphaRodillaIzquierdo(){ return piernaIzq->getAlphaRodilla(); }
float Personaje::getBetaRodillaIzquierdo(){ return piernaIzq->getBetaRodilla(); }
float Personaje::getEscaladoLaser(){ return espadaLaser->getEscaladoLaser(); }
float Personaje::getAlphaEspada(){ return alpha_espada; }
float Personaje::getBetaEspada(){ return beta_espada; }

//Blender (modelado 3D) para trocear un ply
//Meshlab de .obj a .ply