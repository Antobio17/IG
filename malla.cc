#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualización en modo diferido con la luz activada y 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(GLenum tipoIluminacion)
{
   // La primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto
   if( id_vbo_ver == 0 || id_vbo_tri == 0 || id_vbo_nv == 0 ){
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*sizeof(float)*3, v.data());
      id_vbo_nv = CrearVBO(GL_ARRAY_BUFFER, nv.size()*sizeof(float)*3, nv.data());
      id_vbo_text = CrearVBO(GL_TEXTURE_BUFFER, ct.size()*sizeof(float)*2, ct.data());
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*sizeof(int)*3, f.data());
   }
   
   glShadeModel(tipoIluminacion);

   // Habilitamos los vectores de vértices y de normales
   glEnableClientState( GL_VERTEX_ARRAY );
   glEnableClientState( GL_NORMAL_ARRAY );
   // Activar e indicar la ubicación del vector de texturas
   // if(textura != nullptr){
		// textura->activar();
		// glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      // glBindBuffer(GL_TEXTURE_BUFFER, id_vbo_text);    // Activar VBO de textura
		// glTexCoordPointer( 2, GL_FLOAT, 0, 0);
      // glBindBuffer(GL_TEXTURE_BUFFER, 0);             // Desactivar VBO de vértices
	// }
   
   if(textura != nullptr && glIsEnabled(GL_LIGHTING)){
		textura->activar();
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer( 2, GL_FLOAT, 0, ct.data());
	}
    
   // indicar la ubicacion del vector de vertices y de normales
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);    // Activar VBO de vértices
   glVertexPointer(3, GL_FLOAT, 0, 0);           // Especificar formato y offset (=0)
   glBindBuffer(GL_ARRAY_BUFFER, 0);             // Desactivar VBO de vértices  
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_nv);     // Activar VBO de vértices
   glNormalPointer(GL_FLOAT, 0, 0);              // Especificar formato y offset (=0)
   glBindBuffer(GL_ARRAY_BUFFER, 0);             // Desactivar VBO de vértices

   // Aplicar los valores del material y dibujar
   mat->aplicar();
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);          // Activar VBO de triángulos
   glDrawElements(GL_TRIANGLES, TAM, GL_UNSIGNED_INT, 0);      // Visualizar la malla
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                   // Desactivar VBO de triángulos
   // Deshabilitamos las texturas
   if(textura != nullptr ){
	   glDisable( GL_TEXTURE_2D );
	   glDisable(GL_TEXTURE_COORD_ARRAY);
   }

   // Deshabilitamos los vectores de vértices y de normales
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_NORMAL_ARRAY );
}

//------------------------------------------------------------------------
// Visualización en modo inmediato con la luz activada y 'glDrawElements'

void Malla3D::draw_ModoInmediato(GLenum tipoIluminacion)
{
   glShadeModel(tipoIluminacion);

   // Habilitamos los vectores de vértices y de normales
   glEnableClientState( GL_VERTEX_ARRAY );
   glEnableClientState( GL_NORMAL_ARRAY );

   // Indicar la ubicacion del vector de vertices y de normales
   glVertexPointer( 3, GL_FLOAT, 0, v.data() ) ;   
   glNormalPointer(GL_FLOAT,0, nv.data() );
   
   // Activar e indicar la ubicación del vector de texturas
   if(textura != nullptr  && glIsEnabled(GL_LIGHTING)){
		textura->activar();
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer( 2, GL_FLOAT, 0, ct.data());
	}

   // Aplicar los valores del material y dibujar
   mat->aplicar();
   glDrawElements( GL_TRIANGLES, TAM, GL_UNSIGNED_INT, f.data() );
   
   // Deshabilitamos las texturas
   if(textura != nullptr){
	   glDisable( GL_TEXTURE_2D );
	   glDisable(GL_TEXTURE_COORD_ARRAY);
   }
   
   // Deshabilitamos los vectores de vértices y de normales
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_NORMAL_ARRAY );
}

//------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez)
{  
   //printf("\nDEPURANDO\n");
   glEnableClientState(GL_VERTEX_ARRAY);               // Habilitar array de vértices
   glEnableClientState( GL_COLOR_ARRAY );              // Habilitar array de colores
   glVertexPointer(3, GL_FLOAT, 0, v.data());          // Le indicamos donde está el vector de vértices

   // Activar e indicar la ubicación del vector de texturas
   if(textura != nullptr  && glIsEnabled(GL_LIGHTING)){
		textura->activar();
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer( 2, GL_FLOAT, 0, ct.data());
	}

   // Si el modo ajedrez está activo, el condicional se ejecutará y pintará los triángulos pares de diferente color
   if(modoAjedrez){
      // Con el modo ajedrez activado solo se pintará el modo sólido
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      // Pintamos los triangulos pares
      glColorPointer(3, GL_FLOAT, 0, color_rojo.data());                                // Le indicamos donde está el vector de colores
      glDrawElements(GL_TRIANGLES, TAM_PAR, GL_UNSIGNED_INT, f_pares.data());  // Visualizar la malla
      // Pintamos los triangulos impares
      glColorPointer(3, GL_FLOAT, 0, color_verde.data());                                   // Le indicamos donde está el vector de colores
      glDrawElements(GL_TRIANGLES, TAM_IMPAR, GL_UNSIGNED_INT, f_impares.data());  // Visualizar la malla
   }else{
      // Si el modo Punto está activado dibujará la figura en modo punto
      if(modoPunto){
         glPolygonOffset(2.0f, 2.0f);                                          // Para que no se solapen los modos de dibujo
         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
         glColorPointer(3, GL_FLOAT, 0, color_rojo.data());                    // Le indicamos donde está el vector de colores
         glDrawElements(GL_TRIANGLES, TAM, GL_UNSIGNED_INT, f.data());  // Visualizar la malla
      }
      // Si el modo Linea está activado dibujará la figura en modo linea
      if(modoLinea){
         glPolygonOffset(1.0f, 1.0f);                                          // Para que no se solapen los modos de dibujo
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         glColorPointer(3, GL_FLOAT, 0, color_verde.data());                   // Le indicamos donde está el vector de colores
         glDrawElements(GL_TRIANGLES, TAM, GL_UNSIGNED_INT, f.data());  // Visualizar la malla
      }
      // Si el modo Solido está activado dibujará la figura en modo solido
      if(modoSolido){
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glColorPointer(3, GL_FLOAT, 0, color.data());                    // Le indicamos donde está el vector de colores
         glDrawElements(GL_TRIANGLES, TAM, GL_UNSIGNED_INT, f.data());  // Visualizar la malla
      }
   }
   // Deshabilitamos las texturas
   if(textura != nullptr){
	   glDisable( GL_TEXTURE_2D );
	   glDisable(GL_TEXTURE_COORD_ARRAY);
   }
   glDisableClientState(GL_VERTEX_ARRAY);                                      // Desactivar uso de array de vértices
   glDisableClientState(GL_COLOR_ARRAY);                                       // Desactivar uso de array de colores
}


// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez)
{
   // La primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto
   if(id_vbo_ver == 0 || id_vbo_tri == 0 || id_vbo_tri_pares == 0 || id_vbo_tri_impares == 0 ){
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*sizeof(float)*3, v.data());
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*sizeof(int)*3, f.data());
      id_vbo_tri_pares = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f_pares.size()*sizeof(int)*3, f_pares.data());
      id_vbo_tri_impares = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f_impares.size()*sizeof(int)*3, f_impares.data());
      id_vbo_color_rojo = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, color_rojo.size()*sizeof(int)*3, color_rojo.data());
      id_vbo_color_verde = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, color_verde.size()*sizeof(int)*3, color_verde.data());
      id_vbo_color_azul = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, color_azul.size()*sizeof(int)*3, color_azul.data());
      id_vbo_color = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, color.size()*sizeof(int)*3, color.data());
   }

   // Especificar localización y formato de la tabla de vértices , habilitar tabla
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);    // Activar VBO de vértices
   glVertexPointer(3, GL_FLOAT, 0, 0);           // Especificar formato y offset (=0)
   glBindBuffer(GL_ARRAY_BUFFER, 0);             // Desactivar VBO de vértices
   
   // Activar e indicar la ubicación del vector de texturas
   if(textura != nullptr  && glIsEnabled(GL_LIGHTING)){
		textura->activar();
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer( 2, GL_FLOAT, 0, ct.data());
	}

   // Si el modo ajedrez está activo, el condicional se ejecutará y pintará los triángulos pares de diferente color
   if(modoAjedrez){
      // Con el modo ajedrez activado solo se pintará el modo sólido
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      // Pintamos los triangulos pares
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_rojo);                      // Activar VBO de color rojo
      glColorPointer(3, GL_FLOAT, 0, 0);                                     // Le indicamos donde está el vector de colores
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                      // Desactivar VBO
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_pares);               // Activar VBO de triángulos pares
      glDrawElements(GL_TRIANGLES, TAM_PAR, GL_UNSIGNED_INT, 0);    // Visualizar la malla
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                              // Desactivar VBO de triángulos pares
      // Pintamos los triangulos impares
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_verde);                     // Activar VBO de color verde
      glColorPointer(3, GL_FLOAT, 0, 0);                                     // Le indicamos donde está el vector de colores
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                      // Desactivar VBO de colores
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_impares);             // Activar VBO de triángulos impares
      glDrawElements(GL_TRIANGLES, TAM_IMPAR, GL_UNSIGNED_INT, 0);  // Visualizar la malla
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                              // Desactivar VBO de triángulos impares
   }else{
      // Si el modo Punto está activado dibujará la figura en modo punto
      if(modoPunto){
         glPolygonOffset(2.0f, 2.0f);                                       // Para que no se solapen los modos de dibujo
         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_rojo);                  // Activar VBO de color rojo
         glColorPointer(3, GL_FLOAT, 0, 0);                                 // Le indicamos donde está el vector de colores
         glBindBuffer(GL_ARRAY_BUFFER, 0);                                  // Desactivar VBO
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);                 // Activar VBO de triángulos
         glDrawElements(GL_TRIANGLES, TAM, GL_UNSIGNED_INT, 0);      // Visualizar la malla
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                          // Desactivar VBO
      }
      // Si el modo Linea está activado dibujará la figura en modo linea
      if(modoLinea){
         glPolygonOffset(1.0f, 1.0f);                                       // Para que no se solapen los modos de dibujo
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_verde);                 // Activar VBO de color verde
         glColorPointer(3, GL_FLOAT, 0, 0);                                 // Le indicamos donde está el vector de colores
         glBindBuffer(GL_ARRAY_BUFFER, 0);                                  // Desactivar VBO
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);                 // Activar VBO de triángulos
         glDrawElements(GL_TRIANGLES, TAM, GL_UNSIGNED_INT, 0);      // Visualizar la malla
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                             // Desactivar VBO de triángulos
      }
      // Si el modo Solido está activado dibujará la figura en modo solido
      if(modoSolido){
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color);                  // Activar VBO de color azul
         glColorPointer(3, GL_FLOAT, 0, 0);                                 // Le indicamos donde está el vector de colores
         glBindBuffer(GL_ARRAY_BUFFER, 0);                                  // Desactivar VBO
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);                 // Activar VBO de triángulos
         glDrawElements(GL_TRIANGLES, TAM, GL_UNSIGNED_INT, 0);      // Visualizar la malla
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                             // Desactivar VBO de triángulos
      }
   }

   // Deshabilitamos las texturas
   if(textura != nullptr){
	   glDisable( GL_TEXTURE_2D );
	   glDisable(GL_TEXTURE_COORD_ARRAY);
   }
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, GLenum tipoIluminacion)
{
   // Calculamos el numero de triangulos a dibujar
   modificarTAM(true, true, 0, modoAjedrez);

   // Selección de Modo Caras Ocultas
   switch (caraOculta){
      case ACTIVADO: 
         glEnable(GL_CULL_FACE);
      break;
      case DESACTIVADO: 
         glDisable(GL_CULL_FACE);
      break;
   }

   // Selección de Modo de dibujado
   switch (modoDibu){
      case GLDRAW:
         if(glIsEnabled(GL_LIGHTING)){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            draw_ModoInmediato(tipoIluminacion);
         }
         else
            draw_ModoInmediato(modoPunto, modoLinea, modoSolido, modoAjedrez);
      break;
      case VBO:
         if(glIsEnabled(GL_LIGHTING)){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            draw_ModoDiferido(tipoIluminacion);
         }
         else
            draw_ModoDiferido(modoPunto, modoLinea, modoSolido, modoAjedrez);
      break;
   }
}

// -----------------------------------------------------------------------------
// Función que crea los VBOs (Vertex Buffer Objects) para el modo diferido

GLuint Malla3D::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram )
{
   GLuint id_vbo;                      // Resultado: indentificador de VBO
   glGenBuffers( 1, &id_vbo );         // Crear nuevo VBO, obtener identificador
   glBindBuffer( tipo_vbo, id_vbo );   // Activar el VBO usando su identificador

   // Esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
   glBindBuffer( tipo_vbo, 0 );        // Desactivación del VBO (activar 0)
   return id_vbo;                      // Devolver el indentificador
}

// -----------------------------------------------------------------------------
// Función que calcula las normales de los vertices de la Malla 3D

void Malla3D::calcular_normales(){
   Tupla3f vectorA = { 0,0,0 }, vectorB = { 0,0,0 }, perpendicular, normal;

   // para cada cara calculamos dos vectores, si por ejemplo la cara esta formada
   // por los puntos p, q y r, A = q - p y B = r - p
   // tendremos una normal por cada vertice asique inicializamos el la tabla de normales
   for (int i = 0; i < v.size(); i++)
      nv.push_back({0,0,0});

   for (int i = 0; i < f.size(); i++){
      vectorA = v[f[i][1]] - v[f[i][0]];
      vectorB = v[f[i][2]] - v[f[i][0]];


      // calculamos la permendicular haciendo el producto vectorial
      perpendicular = vectorA.cross(vectorB);

      // lo normalizamos
		// si podemos, esto esta hecho asi para caso de la esfera
		// que repetimos lospuntos de los polos
		if (perpendicular.lengthSq() > 0)
      	normal = perpendicular.normalized();

      nv[f[i][0]] = nv[f[i][0]] + normal;
      nv[f[i][1]] = nv[f[i][1]] + normal;
      nv[f[i][2]] = nv[f[i][2]] + normal;

   }


   for (int i = 0; i < nv.size(); i++){
      if (nv[i].lengthSq() > 0)
         nv[i] = nv[i].normalized();
   }
}

// -----------------------------------------------------------------------------
// Función para modificar el color
void Malla3D::modificarColor(Tupla3f c){
   color.resize(v.size());
   for(int i = 0; i < color.size(); i++)
         color[i] = c;
}

// -----------------------------------------------------------------------------
// Función que genera los 3 colores básicos del RGB
void Malla3D::generarColoresBasicos(){
   Tupla3f color_r( 1.0, 0.0, 0.0 );
   Tupla3f color_g( 0.0, 1.0, 0.0 );
   Tupla3f color_b( 0.0, 0.0, 1.0 );

   color_rojo.resize(v.size());
   for(int i = 0; i < color_rojo.size(); i++)
         color_rojo[i] = color_r;

   color_verde.resize(v.size());
   for(int i = 0; i < color_verde.size(); i++)
         color_verde[i] = color_g;
      
   color_azul.resize(v.size());
   color.resize(v.size());
   for(int i = 0; i < color_azul.size(); i++){
      color_azul[i] = color_b;
      color[i] = color_b;
   }
}

// -----------------------------------------------------------------------------
// Función para cambiar el material de la malla

void Malla3D::cambiarMaterial ( Material *mat ){
   this->mat->cambiarMaterial(mat->getAmbiente(), mat->getDifuso(), mat->getEspecular(), mat->getBrillo());
}

//------------------------------------------------------------------------------
//Funcion para crear la textura del objeto
void Malla3D::setTextura(const std::string archivo){
   // Si ya habíamos creado una textura la eliminamos
   if (textura != nullptr)
		delete textura;

	textura = new Textura(archivo);

	//generarCoordenadasTextura(modoTexturas);
}

// -----------------------------------------------------------------------------
// Función para modificar la variable TAM

void Malla3D::modificarTAM(bool tapa_superior, bool tapa_inferior, int num_instancias, bool modoAjedrez){
   if(modoAjedrez){
      if(!tapa_superior && !tapa_inferior){
         TAM_PAR = f_pares.size()*3-3*num_instancias;
         TAM_IMPAR = f_impares.size()*3-3*num_instancias;
      }
      else if(!tapa_superior || !tapa_inferior){
         TAM_PAR = f_pares.size()*3-3*num_instancias/2;  
         TAM_IMPAR = f_impares.size()*3-3*num_instancias/2;
      }
      else{
         TAM_PAR = f_pares.size()*3;
         TAM_IMPAR = f_impares.size()*3;
      }
   }else{
      if(!tapa_superior && !tapa_inferior)
         TAM = f.size()*3-2*3*num_instancias;
      else if(!tapa_superior || !tapa_inferior)
         TAM = f.size()*3-3*num_instancias;  
      else
         TAM = f.size()*3; 
   }
}

Material* Malla3D::getMaterial(){
    return mat;
}