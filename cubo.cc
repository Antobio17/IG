#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{    
     // inicializar la tabla de vértices
     Tupla3f c0( lado, lado, lado ),
               c1( -lado, lado, lado ),
               c2( -lado, -lado, lado ),
               c3( lado, -lado, lado ),
               c4( lado, lado, -lado ),
               c5( lado, -lado, -lado ),
               c6( -lado, -lado, -lado ),
               c7( -lado, lado, -lado );
     
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
     Tupla3i t0( 0, 1, 2 );      // FRONT
     Tupla3i t1( 2, 3, 0 );
     Tupla3i t2( 7, 4, 5 );      // BACK
     Tupla3i t3( 5, 6, 7 );
     Tupla3i t4( 0, 3, 5 );      // RIGHT
     Tupla3i t5( 4, 0, 5 );
     Tupla3i t6( 6, 2, 7 );      // LEFT
     Tupla3i t7( 2, 1, 7 );
     Tupla3i t8( 7, 1, 0 );      // UP
     Tupla3i t9( 0, 4, 7 );
     Tupla3i t10( 3, 2, 6 );     // DOWN
     Tupla3i t11( 6, 5, 3 );

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
     f_pares.push_back(t0);
     f_pares.push_back(t2);
     f_pares.push_back(t4);
     f_pares.push_back(t6);
     f_pares.push_back(t8);
     f_pares.push_back(t10);
     f_impares.push_back(t1);
     f_impares.push_back(t3);
     f_impares.push_back(t5);
     f_impares.push_back(t7);
     f_impares.push_back(t9);
     f_impares.push_back(t11);

     generarColoresBasicos();

     calcular_normales();
     mat = new Material(Tupla4f(0.0, 0.0, 0.2, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(0.0, 0.0, 6.0, 1.0), 0.6);
     //mat = new Material();
}