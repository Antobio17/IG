#include "pierna.h"
#include "escena.h"

// *****************************************************************************
//
// Clase Pierna
//
// *****************************************************************************

Pierna::Pierna(){
    n_instancias = 20;
    mat_negro = new Material(Tupla4f(1.0, 1.0, 1.0, 0.1), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), 0.0);
    mat_azul = new Material(Tupla4f(0.2, 0.2, 0.8, 0.1), Tupla4f(0.0, 0.0, 0.1, 1.0), Tupla4f(0.0, 0.0, 1.0, 1.0), 0.0);
    mat_piel = new Material(Tupla4f(0.5, 0.2, 0.1, 0.0), Tupla4f(0.0, 0.0, 0.0, 0.0), Tupla4f(0.5, 0.2, 0.1, 0.0), 0.1);

    gluteo = new Esfera(10, n_instancias, 1, ROTACIONY, false, ESFERICAS);
    gluteo->modificarColor(Tupla3f{0.0,0.0,0.0});
    rodilla = new Esfera(10, n_instancias, 1, ROTACIONY, false, ESFERICAS);
    rodilla->modificarColor(Tupla3f{0.0,0.0,0.0});
    cuadricep = new Cubo();
    cuadricep->modificarColor(Tupla3f{0.0,0.0,0.0});
    gemelo = new Cubo();
    gemelo->modificarColor(Tupla3f{0.0,0.0,0.0});
    pie = new ObjPLY("plys/zapatillas.ply");
    pie->modificarColor(Tupla3f{0.0,0.0,0.0});

    alpha_gluteo = 0;
    beta_gluteo = 0;
    alpha_rodilla = 0;
    beta_rodilla = 0;

    this->resetMaterialPersonaje();
}

void Pierna::draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipo_iluminacion){
    glPushMatrix();
        glRotatef(alpha_gluteo, 1.0, 0.0, 0.0);
        glRotatef(beta_gluteo, 0.0, 0.0, 1.0);
        glPushMatrix();         // Lo contruimos con la esfera en el 0,0,0
            glPushMatrix();
                glScalef(0.4, 0.4, 0.4);
                // gluteo->cambiarMaterial(mat_azul);
                gluteo->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, true, true, n_instancias, tipo_iluminacion);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0, -35.0, 0.0);
                glScalef(0.25, 0.9, 0.25);
                // cuadricep->cambiarMaterial(mat_azul);
                cuadricep->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipo_iluminacion);
            glPopMatrix();
        glPopMatrix();

        glTranslatef(0.0, -70.0, 0.0);           // Lo bajamos a su posición de "rodilla"
        glRotatef(alpha_rodilla, 1.0, 0.0, 0.0);
        glRotatef(beta_rodilla, 0.0, 0.0, 1.0);
        glPushMatrix();
            glScalef(0.4, 0.4, 0.4);
            // rodilla->cambiarMaterial(mat_piel);
            rodilla->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, true, true, n_instancias, tipo_iluminacion);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, -35.0, 0.0);
            glPushMatrix();
                glScalef(0.25, 0.9, 0.25);
                // gemelo->cambiarMaterial(mat_piel);
                gemelo->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipo_iluminacion);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-5.0, -40.0, 30.0);
                glRotatef(-90, 0.0, 1.0, 0.0);
                glScalef(0.5, 0.5, 0.5);
                // pie->cambiarMaterial(mat_negro);
                pie->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipo_iluminacion);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Pierna::modificarGiroAlphaGluteo(float x){
    alpha_gluteo += x;
    if(alpha_gluteo < -45)
        alpha_gluteo = -45;
    if(alpha_gluteo > 45)
        alpha_gluteo = 45;
}

void Pierna::setMaterialSeleccion ( Material *mat ){
    gluteo->cambiarMaterial(mat);
    cuadricep->cambiarMaterial(mat);
    rodilla->cambiarMaterial(mat);
    gemelo->cambiarMaterial(mat);
    pie->cambiarMaterial(mat);
}

void Pierna::resetMaterialPersonaje(){
    gluteo->cambiarMaterial(mat_azul);
    cuadricep->cambiarMaterial(mat_azul);
    rodilla->cambiarMaterial(mat_piel);
    gemelo->cambiarMaterial(mat_piel);
    pie->cambiarMaterial(mat_negro);
}

void Pierna::modificarGiroBetaGluteo(float x){
    beta_gluteo += x;
}

void Pierna::modificarGiroAlphaRodilla(float x){
    alpha_rodilla += x;
    if(alpha_rodilla < 0)
        alpha_rodilla = 0;
    if(alpha_rodilla > 45)
        alpha_rodilla = 45;
}

void Pierna::modificarGiroBetaRodilla(float x){
    beta_rodilla += x;
}

float Pierna::getAlphaGluteo(){ return alpha_gluteo; }
float Pierna::getBetaGluteo(){ return beta_gluteo; }
float Pierna::getAlphaRodilla(){ return alpha_rodilla; }
float Pierna::getBetaRodilla(){ return beta_rodilla; }