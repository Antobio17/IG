#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"

Cilindro::Cilindro ( const int num_vert_perfil , const int num_instancias_perf , const float altura , const float radio, const bool tapa_inferior, const bool tapa_superior, const AnguloRotacion angulo_rotacion, const bool coor_texturas, const modoGenTextura modoTexturas ){
    std::vector<Tupla3f> perfil;
    perfil.push_back(Tupla3f(0, 0, 0));
    perfil.push_back(Tupla3f(radio, 0, 0));
    perfil.push_back(Tupla3f(radio, altura/4, 0));
    perfil.push_back(Tupla3f(radio, altura/2, 0));
    perfil.push_back(Tupla3f(radio, altura/1.3, 0));
    perfil.push_back(Tupla3f(radio, altura, 0));
    perfil.push_back(Tupla3f(0, altura, 0));
    crearMalla(perfil, num_instancias_perf, tapa_inferior, tapa_superior, angulo_rotacion);
    
    if(coor_texturas)
        generarCoordenadasTextura(modoTexturas, num_instancias_perf);

    generarColoresBasicos();
    calcular_normales();
    //mat = new Material(Tupla4f(1.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 0.7, 0.7, 1.0), Tupla4f(0.0, 0.0, 1.0, 1.0), 0.7);
    mat = new Material();
}