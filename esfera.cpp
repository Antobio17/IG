#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"

Esfera::Esfera ( const int num_vert_perfil , const int num_instancias_perf , const float radio, const AnguloRotacion angulo_rotacion, const bool coor_texturas, const modoGenTextura modoTexturas ){
    std::vector<Tupla3f> perfil;
    float x, y, angulo;
    // Creamos los puntos del perfil del objeto por revolución a partir del radio
    perfil.push_back(Tupla3f(0,-radio,0));
    for(int i = (num_vert_perfil/2)-1; i >= 0 ; i--){
        angulo = M_PI*i/num_vert_perfil;
        y = radio * sin(-angulo);
        x = radio * cos(-angulo);
        perfil.push_back(Tupla3f(x,y,0));
    }
    for(int i = 0; i < num_vert_perfil/2; i++){
        angulo = M_PI*i/num_vert_perfil;
        y = radio * sin(angulo);
        x = radio * cos(angulo);
        perfil.push_back(Tupla3f(x,y,0));
    }
    perfil.push_back(Tupla3f(0,radio,0));
    crearMalla(perfil, num_instancias_perf, false, false, angulo_rotacion);
    
    if(coor_texturas)
        generarCoordenadasTextura(modoTexturas, num_instancias_perf);

    generarColoresBasicos();
    calcular_normales();
    //mat = new Material(Tupla4f(1.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 0.7, 0.7, 1.0), Tupla4f(0.0, 0.0, 1.0, 1.0), 0.7);
    mat = new Material();
}
