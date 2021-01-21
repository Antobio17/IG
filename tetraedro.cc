#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{
     // inicializar la tabla de vértices
     Tupla3f c0( 0.0, 75.0, 0.0 ),
             c1( 50.0, 0, 50.0 ),
             c2( -50.0, 0, 50.0 ),
             c3( 0.0, 0, -50.0 );

     v.push_back(c0);        
     v.push_back(c1);
     v.push_back(c2);
     v.push_back(c3);
    
     // inicializar la tabla de caras o triángulos:
     // (es importante en cada cara ordenar los vértices en sentido contrario
     //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
     Tupla3i t0( 0, 2, 1 );      // FRONT
     Tupla3i t1( 0, 1, 3 );      // RIGHT
     Tupla3i t2( 0, 3, 2 );      // LEFT
     Tupla3i t3( 1, 2, 3 );      // DOWN
   
     
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
     //mat = new Material(Tupla4f(1.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 0.7, 0.7, 1.0), Tupla4f(0.0, 0.0, 1.0, 1.0), 0.7);
     mat = new Material();
}

