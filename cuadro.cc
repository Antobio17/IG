#include "aux.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro(float width, float height)
{    
    // inicializar la tabla de vértices
    Tupla3f c0( -width, -height, 0 ),
            c1(  width, -height, 0 ),
            c2(  width, height, 0 ),
            c3(  -width, height, 0 ),
            c4( -width, -height, -0.01 ),
            c5(  width, -height, -0.01 ),
            c6(  width, height, -0.01 ),
            c7(  -width, height, -0.01 );
     
    v.push_back(c0);
    v.push_back(c1);
    v.push_back(c2);
    v.push_back(c3);
    v.push_back(c4);
    v.push_back(c5);
    v.push_back(c6);
    v.push_back(c7);

    // inicializar la tabla de caras o triángulos:
    // (es importante en cada cara ordenar los vértices en sentido contrario
    //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
    Tupla3i t0( 0, 1, 2 );
    Tupla3i t1( 2, 3, 0 );
    Tupla3i t2( 4, 6, 5 );
    Tupla3i t3( 6, 4, 7 );


    f.push_back(t0);
    f.push_back(t1);
    f.push_back(t2);
    f.push_back(t3);
    f_pares.push_back(t0);
    f_pares.push_back(t2);
    f_impares.push_back(t1);
    f_impares.push_back(t3);

     generarColoresBasicos();

     calcular_normales();
     mat = new Material(Tupla4f(0.2, 0.2, 0.2, 1.0), Tupla4f(1.0, 1.0, 1.0, 0.0), Tupla4f(1.0, 1.0, 1.0, 0.0), 0.0);
     generarCoordenadasTextura();
}

void Cuadro::generarCoordenadasTextura(){
   ct.resize(4);
   ct[0] = { 0, 0 };
   ct[1] = { 1, 0 };
   ct[2] = { 1, 1 };
   ct[3] = { 0, 1 };
}