#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <cmath>


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() { }

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, const bool tapa_inferior, const bool tapa_superior, const AnguloRotacion angulo_rotacion, const bool coor_texturas, modoGenTextura modoTexturas) {
   std::vector<Tupla3f> perfil, auxiliar;
   ply::read_vertices( archivo, perfil);
   // Para poder generar la figura con sus tapas dandonoslas en cualquier orden
   // vamos a comprobar en el orden que se nos da el perfil (norte a sur o sur a norte)
   // Y vamos a colocarlo siempre de sur a norte
   if(perfil[0][Y] > perfil[perfil.size()-1][Y]){
      auxiliar = perfil;
      perfil.clear();
      for(int i = auxiliar.size()-1; i >= 0; i++)
         perfil.push_back(auxiliar[i]);
   }
   crearMalla(perfil, num_instancias, tapa_inferior, tapa_superior, angulo_rotacion);

   if(coor_texturas)
      generarCoordenadasTextura(modoTexturas, num_instancias);
   generarColoresBasicos();
   calcular_normales();

   if(mat == nullptr){
      mat = new Material();
      //mat = new Material(Tupla4f(0.2, 0.0, 0.0, 1.0), Tupla4f(0.8, 0.0, 0.0, 0.8), Tupla4f(0.5, 0.0, 0.0, 0.5), 0.6);
   }
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, const bool tapa_inferior, const bool tapa_superior, const AnguloRotacion angulo_rotacion, const bool coor_texturas, modoGenTextura modoTexturas) {
   std::vector<Tupla3f> auxiliar;
   // Para poder generar la figura con sus tapas dandonoslas en cualquier orden
   // vamos a comprobar en el orden que se nos da el perfil (norte a sur o sur a norte)
   // Y vamos a colocarlo siempre de sur a norte
   if(archivo[0][Y] > archivo[archivo.size()][Y]){
      auxiliar = archivo;
      archivo.clear();
      for(int i = auxiliar.size()-1; i >= 0; i++)
         archivo.push_back(auxiliar[i]);
   }
   crearMalla(archivo, num_instancias, tapa_inferior, tapa_superior, angulo_rotacion);
   if(coor_texturas)
      generarCoordenadasTextura(modoTexturas, num_instancias);
   generarColoresBasicos();
}

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> perfil_original, const int num_instancias, const bool tapa_inferior, const bool tapa_superior, const AnguloRotacion angulo_rotacion) {
   float angulo, x, y, z;
   int a = 0, b = 0, indice_tapa = 0, m = perfil_original.size();;
   std::vector<Tupla3f> aux = perfil_original;
   Tupla3f coordenada_tapa_inferior, coordenada_tapa_superior;
   bool polo_norte = false, polo_sur = false;
   
   // Antes de crear la malla eliminamos los polos, en el caso de que tenga, para añadirlos al final
   if(aux[0][X] == 0){
      coordenada_tapa_inferior = aux[0];      // Guardamos el valor del polo ya que en el caso del cono no podríamos usar su "reflejo"
      polo_sur = true;
      aux.erase(aux.begin());
      m--;
   }else{                                     // Si no tiene polos los creamos nosotros reflejando su primera coordenada en el eje Y
      coordenada_tapa_inferior = Tupla3f(0, aux[0][Y], 0);
   }
   if(aux[m-1][X] == 0){
      coordenada_tapa_superior = aux[m-1];    // Guardamos el valor del polo ya que en el caso del cono no podríamos usar su "reflejo"
      polo_norte = true;
      aux.erase(aux.begin()+m-1);
      m--;
   }else{                                     // Si no tiene polos los creamos nosotros reflejando su última coordenada en el eje Y
      coordenada_tapa_superior = Tupla3f(0, aux[m-1][Y], 0);
   }

   // Creamos los puntos del objeto por revolución a partir del perfil dependiendo del angulo de rotacion
   if(angulo_rotacion == ROTACIONY){
      for(int i = 0; i <= num_instancias; i++){
         angulo = 2*M_PI*i/num_instancias;
         for(int j = 0; j < m; j++){
            x = aux[j][X] * cos(angulo);
            z = aux[j][X] * sin(angulo);
            v.push_back(Tupla3f(x*40,aux[j][Y]*40,z*40));
         }
      }
   }else if(angulo_rotacion == ROTACIONX)
      for(int i = 0; i < num_instancias; i++){
         angulo = 2*M_PI*i/num_instancias;
         for(int j = 0; j < m; j++){
            y = aux[j][X] * cos(angulo);
            z = aux[j][X] * sin(angulo);
            v.push_back(Tupla3f(aux[j][X]*40,y*40,z*40));
         }
      }
   else if(angulo_rotacion == ROTACIONZ)
      for(int i = 0; i < num_instancias; i++){
         angulo = 2*M_PI*i/num_instancias;
         for(int j = 0; j < m; j++){
            x = aux[j][X] * cos(angulo);
            z = aux[j][X] * sin(angulo);
            v.push_back(Tupla3f(x*40,aux[j][Y]*40,z*40));
         }
      }

   // Damos las caras en sentido antihorario y las introducimos en la tabla de caras
   // Añadimos también las caras al vector de caras pares/impares según corresponda
   for(int i = 0; i < num_instancias; i++){
      for(int j = 0; j < m-1; j++){
         a = m*i + j;
         b = m*((i+1)%num_instancias) + j;
         f.push_back(Tupla3i(b+1, b, a));
         f_pares.push_back(Tupla3i(b+1, b, a));
         f.push_back(Tupla3i(a+1, b+1, a));
         f_impares.push_back(Tupla3i(a+1, b+1, a));
      }
   }

   // Añadimos el polo sur y el polo norte al final
   coordenada_tapa_inferior[X] *= 40;
   coordenada_tapa_inferior[Y] *= 40;
   coordenada_tapa_inferior[Z] *= 40;
   v.push_back(coordenada_tapa_inferior);

   coordenada_tapa_superior[X] *= 40;
   coordenada_tapa_superior[Y] *= 40;
   coordenada_tapa_superior[Z] *= 40;
   v.push_back(coordenada_tapa_superior);

   // Tapa superior
   indice_tapa = v.size()-1;             
   for(int i = 0; i < num_instancias-1; i++){
      a = m*(i+1)-1;                                            // Índice del vertice superior de la instancia i 
      b = a + m;                                                // Índice del vertice superior de la instancia i+1
      f.push_back(Tupla3i(indice_tapa, b, a));                  // Introducimos los indices en sentido antihorario
      if(i%2 == 0)
         f_pares.push_back(Tupla3i(indice_tapa, b, a));
      else
         f_impares.push_back(Tupla3i(indice_tapa, b, a));
   }
   f.push_back(Tupla3i(indice_tapa, m-1, b));                   // Cara formada por el vertice de la primera y la última instancia
   if((num_instancias-1)%2 == 0)
      f_pares.push_back(Tupla3i(indice_tapa, m-1, b));
   else
      f_impares.push_back(Tupla3i(indice_tapa, m-1, b));
      
   // Tapa inferior
   indice_tapa = v.size()-2;     
   for(int i = 0; i < num_instancias-1; i++){
      a = m*i;                                                  // Índice del vertice inferior de la instancia i
      b = a + m;                                                // Índice del vertice inferior de la instancia i+1
      f.push_back(Tupla3i(indice_tapa, a, b));                  // Introducimos los indices en sentido antihorario
      if(i%2 == 0)
         f_pares.push_back(Tupla3i(indice_tapa, a, b));
      else
         f_impares.push_back(Tupla3i(indice_tapa, a, b));
   }
   f.push_back(Tupla3i(indice_tapa, b, 0));                     // Cara formada por el vertice de la primera y la última instancia
   if((num_instancias-1)%2 == 0)
      f_pares.push_back(Tupla3i(indice_tapa, b, 0));
   else
      f_impares.push_back(Tupla3i(indice_tapa, b, 0));
}

// -----------------------------------------------------------------------------
// Función para generar las coordenadas de textura,
// 

void ObjRevolucion::generarCoordenadasTextura(modoGenTextura modoTexturas, int num_instancias){
   float alpha, beta, h, h_min = v[0][Y], h_max = v[v.size()-3][Y], s, t;

   if(modoTexturas == CILINDRICAS){
      ct.resize(v.size()-2);
      for(int i = 0; i < ct.size()-5; i++){
         alpha = atan2(v[i][Z], v[i][X]);
         h = v[i][Y];
         
         s = alpha/(2*M_PI);
         if(s < 0)
            s = 1+s;
         
         t = (h - h_min)/(h_max - h_min);

         ct[i] = {s, t};
         //////////////////////////// AUX
         // if(i == 0 || i == 5 || i == 10 || i == 15 || i == 20 || i == 25 || i == 30 || i == 140 || i == 160 || i == 180 || i == 200 || i == 220 || i == 240 || i == 260 || i == 280 || i == 300|| i == 320 || i == 340 || i == 360 || i == 380 || i == 400){
         //    printf("                   SOY EL PERFIL %i\n", i/5);
         // }
         // printf("Mis coordenadas son:\n");
         // printf("%i:[%f,%f,%f]\n", i%5, v[i][X], v[i][Y], v[i][Z]);
         // printf("Mis coordenadas son de textura son:\n");
         // printf("Textura:[%f,%f]\n", s, t);
      }
      for(int i = ct.size()-5; i < ct.size(); i++){
         h = v[i][Y];
         
         s = 1.0;
         t = (h - h_min)/(h_max - h_min);

         ct[i] = {s, t};
         //////////////////////////// AUX
         // if(i == 0 || i == 5 || i == 10 || i == 15 || i == 20 || i == 25 || i == 30 || i == 140 || i == 160 || i == 180 || i == 200 || i == 220 || i == 240 || i == 260 || i == 280 || i == 300|| i == 320 || i == 340 || i == 360 || i == 380 || i == 400){
         //    printf("                   SOY EL PERFIL %i\n", i/5);
         // }
         // printf("Mis coordenadas son:\n");
         // printf("%i:[%f,%f,%f]\n", i%5, v[i][X], v[i][Y], v[i][Z]);
         // printf("Mis coordenadas son de textura son:\n");
         // printf("Textura:[%f,%f]\n", s, t);
      }
   }else if(modoTexturas == ESFERICAS){
      ct.resize(v.size());
      for(int i = 0; i < ct.size(); i++){
         alpha = atan2(v[i][Z], v[i][X]);
         beta = atan2(v[i][Y], sqrt(pow(v[i][X], 2) + pow(v[i][Z], 2)));
         
         s = 0.5 + alpha/(2*M_PI);
         t = 0.5 + beta/M_PI;

         ct[i] = {s, t};
      }
   }
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjRevolucion::draw(modoDibujado modoDibu, carasOcultas caraOculta, bool modoPunto, bool modoLinea, bool modoSolido, bool modoAjedrez, bool tapa_inferior, bool tapa_superior, int num_instancias, GLenum tipoIluminacion)
{
   // Calculamos el numero de triangulos a dibujar
   modificarTAM(tapa_inferior, tapa_superior, num_instancias, modoAjedrez);
   
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
            Malla3D::draw_ModoInmediato(tipoIluminacion);
         }
         else
            Malla3D::draw_ModoInmediato(modoPunto, modoLinea, modoSolido, modoAjedrez);
      break;
      case VBO:
         if(glIsEnabled(GL_LIGHTING)){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            Malla3D::draw_ModoDiferido(tipoIluminacion);
         }
         else
            Malla3D::draw_ModoDiferido(modoPunto, modoLinea, modoSolido, modoAjedrez);
      break;
   }
}