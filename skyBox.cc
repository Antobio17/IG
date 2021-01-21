#include "aux.h"
#include "malla.h"
#include "skyBox.h"

SkyBox::SkyBox(float lado)
{    
    // inicializar la tabla de vértices
    Tupla3f c0 ( lado, -lado, -lado ),   // FONDO
            c1 ( lado, lado, -lado ),
            c2 ( -lado, lado, -lado ),
            c3 ( -lado, -lado, -lado ),
            c4 ( lado, -lado, lado ),   // DERECHA
            c5 ( lado, lado, lado ),    // Los otros dos puntos ya están creados y se pueden reutilizar c0 y c1
            c6 ( -lado, -lado, lado ),  // IZQUIERDA
            c7 ( -lado, lado, lado ),   // Los otros dos puntos ya están creados y se pueden reutilizar c2 y c3
            c8 ( -lado, -lado, lado),   // ESPALDA
            c9 ( -lado, lado, lado ),   // Los otros dos puntos ya están creados y se pueden reutilizar c4 y c5
            c10 ( lado, lado, lado ),   // CIELO
            c11 ( -lado, lado, lado ),  // Los otros dos puntos ya están creados y se pueden reutilizar c1 y c2
            c12 ( lado, -lado, lado ),  // SUELO
            c13 ( -lado, -lado, lado ); // Los otros dos puntos ya están creados y se pueden reutilizar c0 y c3

    v.push_back(c0);
    v.push_back(c1);
    v.push_back(c2);
    v.push_back(c3);
    v.push_back(c4);
    v.push_back(c5);
    v.push_back(c6);
    v.push_back(c7);
    v.push_back(c8);
    v.push_back(c9);
    v.push_back(c10);
    v.push_back(c11);
    v.push_back(c12);
    v.push_back(c13);

    // inicializar la tabla de caras o triángulos:
    // (es importante en cada cara ordenar los vértices en sentido contrario
    //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
    Tupla3i t0( 1, 3, 0 ); // FONDO
    Tupla3i t1( 1, 2, 3 ); 
    Tupla3i t2( 5, 1, 0 ); // DERECHA
    Tupla3i t3( 4, 5, 0 );
    Tupla3i t4( 2, 7, 6 ); // IZQUIERDA
    Tupla3i t5( 2, 6, 3 );
    Tupla3i t6( 5, 4, 8 ); // ESPALDA
    Tupla3i t7( 5, 8, 9 );
    Tupla3i t8( 10, 11, 2 ); // CIELO
    Tupla3i t9( 10, 2, 1 );
    Tupla3i t10( 0, 13, 12 ); // SUELO
    Tupla3i t11( 0, 3, 13 );

    f.push_back(t0);
    f.push_back(t1);
    f.push_back(t2);
    f.push_back(t3);
    f.push_back(t4);
    f.push_back(t5);
    f.push_back(t6);
    f.push_back(t7);
    f.push_back(t8);
    f.push_back(t9);
    f.push_back(t10);
    f.push_back(t11);

    generarColoresBasicos();
    calcular_normales();
    mat = new Material(Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 0.0), Tupla4f(1.0, 1.0, 1.0, 1.0), 1.0);
    generarCoordenadasTextura();
}

void SkyBox::generarCoordenadasTextura(){
   ct.resize(v.size());
   ct[0] = { 0.5, 0.368 };
   ct[1] = { 0.5, 0.664 };
   ct[2] = { 0.25, 0.664 };
   ct[3] = { 0.25, 0.368 };
   ct[4] = { 0.75, 0.368 };
   ct[5] = { 0.75, 0.664 };
   ct[6] = { 0, 0.368 };
   ct[7] = { 0, 0.664 };
   ct[8] = { 1, 0.368 };
   ct[9] = { 1, 0.664 };
   ct[10] = { 0.5, 1 };
   ct[11] = { 0.25, 1 };
   ct[12] = { 0.5, 0.1 };
   ct[13] = { 0.25, 0.1 };
}