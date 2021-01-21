

#include "aux.h"
#include "ejes.h"

// -----------------------------------------------------------------------------

Ejes::Ejes()
{
    axisSize = 1000;
    createArrayData();
}
// -----------------------------------------------------------------------------

void Ejes::changeAxisSize( float newSize )
{
	axisSize = newSize;
	createArrayData();
}
// -----------------------------------------------------------------------------

void Ejes::createArrayData()
{
	colorArray[0] = 1; colorArray[1] = 0; colorArray[2] = 0;          // 1, 0, 0     
	colorArray[3] = 1; colorArray[4] = 0; colorArray[5] = 0;          // 1, 0, 0    Quiero que los dos vertices del eje x sea rojo por lo que los 2 puntos deben ser del mismo color
	colorArray[6] = 0; colorArray[7] = 1; colorArray[8] = 0;          // 0, 1, 0
	colorArray[9] = 0; colorArray[10] = 1; colorArray[11] = 0;        // 0, 1, 0    Quiero que los dos vertices del eje x sea verde
	colorArray[12] = 0; colorArray[13] = 0; colorArray[14] = 1;       // 0, 0, 1    
	colorArray[15] = 0; colorArray[16] = 0; colorArray[17] = 1;       // 0, 0, 1    Quiero que los dos vertices del eje x sea rojo

	vertexArray[0] = -axisSize; vertexArray[1] = 0; vertexArray[2] = 0;        // -1000, 0, 0
	vertexArray[3] = axisSize; vertexArray[4] = 0; vertexArray[5] = 0;         // 1000, 0, 0
	vertexArray[6] = 0; vertexArray[7] = -axisSize; vertexArray[8] = 0;        // 0, -1000, 0
	vertexArray[9] = 0; vertexArray[10] = axisSize; vertexArray[11] = 0;       // 0, 1000, 0
	vertexArray[12] = 0; vertexArray[13] = 0; vertexArray[14] = -axisSize;     // 0, 0, -1000
	vertexArray[15] = 0; vertexArray[16] = 0; vertexArray[17] = axisSize;      // 0, 0, 1000
}
 

void Ejes::draw()
{ 
	glEnableClientState(GL_VERTEX_ARRAY);             // Habilitar el array de vértices
	glVertexPointer(3, GL_FLOAT, 0, vertexArray );    // Decir a OpenGL donde está el array (en vertexArray definido como variable privada de la clase Ejes)
	glEnableClientState(GL_COLOR_ARRAY);              // Habilitar el color
	glColorPointer(3, GL_FLOAT, 0, colorArray );      // Decir a OpenGL donde está el color (en colorArray definido como variable privada de la clase Ejes)
	glDrawArrays( GL_LINES, 0, 6 ) ;                  // Para que se interpreten los vértices como líneas 
}
