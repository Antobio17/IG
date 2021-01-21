#include "aux.h"
#include "objrevolucion.h"
#include "rueda.h"

Rueda::Rueda ( const int num_instancias_perf , const float radio , const float anchura, const bool tapa_inferior, const bool tapa_superior, const AnguloRotacion angulo_rotacion, const bool coor_texturas ){
    std::vector<Tupla3f> perfil;
    float div = radio / num_instancias_perf;
    float y = 0;
    perfil.push_back(Tupla3f(0, 0, 0));
    for(int i = 0; i < num_instancias_perf; i++){
        y += div;
        perfil.push_back(Tupla3f(0, y, 0));
    }
    for(int i = num_instancias_perf-1; i >= 0; i--){
        perfil.push_back(Tupla3f(anchura, y, 0));
        y -= div;
    }

    crearMalla(perfil, num_instancias_perf, tapa_inferior, tapa_superior, angulo_rotacion);
    
    generarColoresBasicos();

    calcular_normales();
    //mat = new Material(Tupla4f(1.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 0.7, 0.7, 1.0), Tupla4f(0.0, 0.0, 1.0, 1.0), 0.7);
    mat = new Material();
}