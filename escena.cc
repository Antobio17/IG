#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h"   // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   // Variables de selección
   objetoActivo=JERARQUICO;
   //objetoActivo=CILINDRO;
   modoDibu=GLDRAW; 
   modoDibu=VBO;
   caraOculta = ACTIVADO;
   modoAjedrez = false;
   modoPunto = false;
   modoLinea = true;
   modoSolido = false;
   modoIluminacion = true;
   animacion_luz = false;
   pCuerpo = VACIO;

   // Variables objeto revolución
   tapaInferior = true;
   tapaSuperior = true;
   num_instancias = 20;
   //angulo_rotacion = ROTACIONX;
   angulo_rotacion = ROTACIONY;
   //angulo_rotacion = ROTACIONZ;

   // Variables Luz
   tipoIlumniacion = GL_SMOOTH;
   //tipoIlumniacion = GL_FLAT;
   cuadro_de_luces = new Luz(GL_LIGHTING);
   luz_direccional = new LuzDireccional(Tupla2f(0.0, 0.0), GL_LIGHT0, Tupla4f(0.2, 0.2, 0.2, 1.0), Tupla4f(0.5, 0.5, 0.5, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0));
   luz_posicional = new LuzPosicional(Tupla3f(250.0, 0.0, 0.0), GL_LIGHT1, Tupla4f(1.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 0.0, 0.0, 0.8), Tupla4f(1.0, 0.0, 0.0, 0.5));
   luces_activas = {true, false, false, false, false, false, false, false};
   contador_luz = 0;

   // Materiales
   mat = new Material(Tupla4f(0.8, 0.0, 0.8, 0.8), Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 0.0, 1.0, 0.2), 0.8);
   mat_blanco = new Material(Tupla4f(0.8, 0.8, 0.8, 0.8), Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 0.2), 0.8);
   mat_verde = new Material(Tupla4f(0.2, 0.1, 0.2, 0.1), Tupla4f(0.0, 0.1, 0.0, 1.0), Tupla4f(0.0, 1.0, 0.0, 1.0), 1.0);
   mat_azul = new Material(Tupla4f(0.2, 0.2, 0.1, 0.1), Tupla4f(0.0, 0.0, 0.1, 1.0), Tupla4f(0.0, 0.0, 1.0, 1.0), 1.0);
   mat_negro = new Material(Tupla4f(0.2, 0.2, 0.2, 1.0), Tupla4f(0.9, 0.9, 0.9, 1.0), Tupla4f(0.1, 0.1, 0.1, 1.0), 1.0);
   mat_piramide = new Material(Tupla4f(0.5, 0.4, 0.1, 1.0), Tupla4f(0.7, 0.6, 0.1, 0.8), Tupla4f(0.7, 0.6, 0.1, 1.0), 1.0);
   mat_mate_blanco = new Material(Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 0.0), Tupla4f(1.0, 1.0, 1.0, 0.2), 1.0);
   mat_seleccion = new Material(Tupla4f(1.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 0.0, 0.0, 1.0), 1.0);
   mat_planeta = new Material(Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 0.0), Tupla4f(1.0, 1.0, 1.0, 1.0), 1.0);

   cubo = new Cubo();
   tetraedro = new Tetraedro();
   tetraedro->cambiarMaterial(mat_piramide);
   objPLY = new ObjPLY("plys/big_dodge.ply");
   objRevolucion = new ObjRevolucion("plys/lata-pcue.ply", num_instancias, true, true, angulo_rotacion, false, CILINDRICAS);
   //objRevolucion->setTextura("img/text-lata-1.jpg");
   cilindro = new Cilindro(7, 4, 3, 1, false, false, angulo_rotacion, true, CILINDRICAS);
   cilindro->setTextura("img/text-lata-1.jpg");
   //rueda = new Rueda(num_instancias, 2, 1, true, true, ROTACIONX);
   cono = new Cono(3, num_instancias, 3, 1, true, true, angulo_rotacion, false, ESFERICAS);
   esfera = new Esfera(10, num_instancias, 1, angulo_rotacion, false, ESFERICAS);
   peon_blanco = new ObjRevolucion("plys/peon.ply", num_instancias, true, true, angulo_rotacion, false, ESFERICAS);
   peon_negro = new ObjRevolucion("plys/peon.ply", num_instancias, true, true, angulo_rotacion, false, ESFERICAS);
   personaje = new Personaje();
   cuadro = new Cuadro();
   //cuadro->setTextura("img/text-mountain.jpg");
   skyBox = new SkyBox();
   skyBox->setTextura("img/sky-box-4.jpg");
   planeta = new Esfera(10, num_instancias, 1, angulo_rotacion, true, ESFERICAS);
   planeta->cambiarMaterial(mat_mate_blanco);
   planeta->setTextura("img/text-planetatierra.jpg");

   // Animación
   // No eliminar para guardar las posibilidades de los ifs, conflicto < y >
   velocidad_personaje = 0.05;
   velocidad_espada = 0.0005;
   hombro_derecho = velocidad_personaje;
   codo_derecho = velocidad_personaje;
   hombro_izquierdo = -velocidad_personaje;
   codo_izquierdo = -velocidad_personaje;
   gluteo_derecho = -velocidad_personaje;
   rodilla_derecha = -velocidad_personaje;
   gluteo_izquierdo = velocidad_personaje;
   rodilla_izquierda = velocidad_personaje;
   //Espada
   escalado_espada = velocidad_espada;
   alpha_espada = velocidad_personaje;
   beta_espada = velocidad_personaje;
   desplegar_espada = false;
   agitar = false;
   contador_desplegar = 0;
   //Luz Posicional
   velocidad_luz_X = 0.05;
   velocidad_luz_Y = 0.05;
   accion = CORRER;

   objetoSeleccionadoEnCamara.push_back(false);
   objetoSeleccionadoEnCamara.push_back(false);
   objetoSeleccionadoEnCamara.push_back(false);
   MOVIENDO_CAMARA_FIRSTPERSON = false;
   camaraActiva = 0;
   Tupla3f eye, at, up;
   eye = {0, -150, 600};
	at = {0, 0, 0};
	up = {0, 1, 0};
   // Camara 0: Perspectiva
   cam = new Camara(eye, at, up, 1, 50.0, 3000.0);
   camaras.push_back(cam);

   eye = {0, -150, -600};
	at = {0, 0, 0};
	up = {0, 1, 0};
   // Camara 1: Perspectiva
   cam = new Camara(eye, at, up, 1, 50.0, 3000.0);
   camaras.push_back(cam);

   eye = {0, -150, 600};
	at = {0, 0, 0};
	up = {0, 1, 0};
   // Camara 2: Ortografica
   cam = new Camara(eye, at, up, 0, 50.0, 3000.0);
   camaras.push_back(cam);

   xant_firstperson = 0 ;   // Para que no haga movimientos bruscos
   yant_firstperson = 0 ;
   click = false;
   tipoObjetoSeleccionadoEnCamara.push_back(NOBJECT);
   tipoObjetoSeleccionadoEnCamara.push_back(NOBJECT);
   tipoObjetoSeleccionadoEnCamara.push_back(NOBJECT);
   coorSeleccionCamara.push_back(Tupla2i{0,0});
   coorSeleccionCamara.push_back(Tupla2i{0,0});
   coorSeleccionCamara.push_back(Tupla2i{0,0});
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   for (int i = 0; i < camaras.size(); i++){
		camaras[i]->setLeft(-UI_window_width/5);
		camaras[i]->setRight(UI_window_width/5);
		camaras[i]->setBottom(-UI_window_height/5);
		camaras[i]->setTop(UI_window_height/5);
	}

   change_projection();
	glViewport( 0, 0, UI_window_width, UI_window_height );
   camaras[2]->zoom(6.0);
   // Mostramos las opciones del menu
   printf("Opciones disponibles: \n  'Q': Salir \n  'O': Modo Seleccion de objeto \n  'V': Modo Seleccion de visualizacion \n  'H': Modo Seleccion de dibujado\n  'F': Activar/Desactivar caras ocultas\n  'T': Visualizacion de Tapas en Objeto Revolucion\n  'N': Activar/Desactivar animación automática\n  'M': Mover grados de libertad (Objeto Jerárquico)\n  'C': Modo selección de Cámara\n  'L': Cámara libre\n");
}

// **************************************************************************
//
// función para animar el modelo jerarquico
//
// **************************************************************************

void Escena::animarModeloJerarquico(){
   if(modoMenu == AUTO){
      if(accion == CORRER){
         // Brazos
         if(!desplegar_espada){
            // Hombro Derecho
            if(personaje->getAlphaHombroDerecho() == -45.0){
               hombro_derecho = velocidad_personaje;
               if(contador_desplegar < 2)
                  contador_desplegar++;
               else
                  desplegar_espada = true;
            }
            else if(personaje->getAlphaHombroDerecho() == 45.0)
               hombro_derecho = -velocidad_personaje;
            personaje->modificarGiroAlphaHombroDerecho(hombro_derecho);
            
            // Codo Derecho
            if(personaje->getAlphaHombroDerecho() == -45.0)
               codo_derecho = velocidad_personaje;
            else if(personaje->getAlphaHombroDerecho() >= 0.0 && personaje->getAlphaHombroDerecho() <= 1.0)
               codo_derecho = -velocidad_personaje;
            else if(personaje->getAlphaHombroDerecho() > 0.0)
               codo_derecho = 0.0;
            personaje->modificarGiroAlphaCodoDerecho(codo_derecho);

            if(contador_desplegar == 1){
               // Espada
               if(personaje->getEscaladoLaser() == 0.0)
                  escalado_espada = velocidad_espada;
               personaje->modificarEscaladoLaser(escalado_espada);
            }else if(contador_desplegar > 2){
               if(personaje->getEscaladoLaser() == 1.5)
                  escalado_espada = -velocidad_espada;
               personaje->modificarEscaladoLaser(escalado_espada);

               if(personaje->getEscaladoLaser() == 0.0)
                  contador_desplegar = -1;
            }
         }else if(desplegar_espada){
            if( contador_desplegar < 10800 || personaje->getBetaEspada() <= -1 || personaje->getBetaEspada() >= 1 ){
               contador_desplegar++;
               if(personaje->getBetaEspada() == -45.0)
                  beta_espada = velocidad_personaje;
               else if(personaje->getBetaEspada() == 45.0)
                  beta_espada = -velocidad_personaje;
               personaje->modificarBetaEspada(beta_espada);
            }else if ( personaje->getAlphaHombroIzquierdo() <= 45.0 && personaje->getAlphaHombroIzquierdo() >= 44.0 ){
               desplegar_espada = false;
            }
         }
         // Hombro Izquierdo
         if(personaje->getAlphaHombroIzquierdo() == -45.0)
            hombro_izquierdo = velocidad_personaje;
         else if(personaje->getAlphaHombroIzquierdo() == 45.0)
            hombro_izquierdo = -velocidad_personaje;
         personaje->modificarGiroAlphaHombroIzquierdo(hombro_izquierdo);
         // Codo Izquierdo
         if(personaje->getAlphaHombroIzquierdo() == -45.0)
            codo_izquierdo = velocidad_personaje;
         else if(personaje->getAlphaHombroIzquierdo() >= 0.0 && personaje->getAlphaHombroIzquierdo() <= 1.0)
            codo_izquierdo = -velocidad_personaje;
         else if(personaje->getAlphaHombroIzquierdo() > 0.0)
            codo_izquierdo = 0.0;
         personaje->modificarGiroAlphaCodoIzquierdo(codo_izquierdo);

         // Piernas
         // Gluteo Derecho
         if(personaje->getAlphaGluteoDerecho() == -45.0)
            gluteo_derecho = velocidad_personaje;
         else if(personaje->getAlphaGluteoDerecho() == 45.0)
            gluteo_derecho = -velocidad_personaje;
         personaje->modificarGiroAlphaGluteoDerecho(gluteo_derecho);
         // Rodilla Derecha
         if(personaje->getAlphaGluteoDerecho() == -45.0)
            rodilla_derecha = velocidad_personaje;
         else if(personaje->getAlphaGluteoDerecho() >= 0.000000 && personaje->getAlphaGluteoDerecho() <= 1.0)
            rodilla_derecha = -velocidad_personaje;
         else if(personaje->getAlphaGluteoDerecho() > 0.0)
            rodilla_derecha = 0.0;
         personaje->modificarGiroAlphaRodillaDerecho(rodilla_derecha);
         // Gluteo Izquierdo
         if(personaje->getAlphaGluteoIzquierdo() <= -45.0)
            gluteo_izquierdo = velocidad_personaje;
         else if(personaje->getAlphaGluteoIzquierdo() >= 45.0)
            gluteo_izquierdo = -velocidad_personaje;
         personaje->modificarGiroAlphaGluteoIzquierdo(gluteo_izquierdo);
         // Rodilla Izquierda
         if(personaje->getAlphaGluteoIzquierdo() == -45.0)
            rodilla_izquierda = velocidad_personaje;
         else if(personaje->getAlphaGluteoIzquierdo() >= 0.0 && personaje->getAlphaGluteoIzquierdo() <= 1.0)
            rodilla_izquierda = -velocidad_personaje;
         else if(personaje->getAlphaGluteoIzquierdo() > 0.0)
            rodilla_izquierda = 0.0;
         personaje->modificarGiroAlphaRodillaIzquierdo(rodilla_izquierda);
      }
   }

   if(animacion_luz){
      luz_direccional->incrementarBeta(0.005);
      if(contador_luz < 20000)
         luz_direccional->decrementarColorLuz();
      else if(contador_luz >= 20000 && contador_luz < 40000)
         luz_direccional->incrementarColorLuz();
      else
         contador_luz = 0;
      contador_luz++;
      // if( luz_posicional->getPosicion()[Y] == 0 ){
      //    velocidad_luz_X = 0;
      //    velocidad_luz_Y = 0.050;
      // }else if( luz_posicional->getPosicion()[Y] == 500 && (luz_posicional->getPosicion()[X] == -250 || luz_posicional->getPosicion()[X] == 250)){
      //    if(velocidad_luz_Y != 0){
      //       if( luz_posicional->getPosicion()[X] == -250 ){
      //          velocidad_luz_X = 0.050;
      //          velocidad_luz_Y = 0;
      //       }else if( luz_posicional->getPosicion()[X] == 250 ){
      //          velocidad_luz_X = -0.050;
      //          velocidad_luz_Y = 0;
      //       }
      //    }else{
      //       velocidad_luz_X = 0;
      //       velocidad_luz_Y = -0.050;
      //    }
      // }
      // luz_posicional->modificarPosicionX(velocidad_luz_X);
      // luz_posicional->modificarPosicionY(velocidad_luz_Y);
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   change_projection();
   // Desactivamos las luces al inicio de dibujar para pintar los ejes en color plano
   cuadro_de_luces->desactivar();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   ejes.draw();
   
   if(modoIluminacion){
      cuadro_de_luces->activar();
      // Activar/Desactivar Luz 0
      if(luces_activas[0])
         luz_direccional->activar();
      else
         luz_direccional->desactivar();
      // Activar/Desactivar Luz 1
      if(luces_activas[1])
         luz_posicional->activar();
      else
         luz_posicional->desactivar();
   }
  
   switch (objetoActivo){
      case CUBO: cubo->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipoIlumniacion);
      break;
      case TETRAEDRO: tetraedro->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipoIlumniacion);
      break;
      case PLY:
            objPLY->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipoIlumniacion);
      break;
      case REVOLUCION:
         glPushMatrix();
            glRotatef(-85, 0.0, 1.0, 0.0);
            objRevolucion->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapaInferior, tapaSuperior, num_instancias, tipoIlumniacion);
         glPopMatrix();
      break;
      case CILINDRO:
         cilindro->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapaInferior, tapaSuperior, num_instancias, tipoIlumniacion);
      break;
      case CONO: cono->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapaInferior, true, num_instancias, tipoIlumniacion);
      break;
      case ESFERA: 
         glPushMatrix();
            glScalef(10.0, 10.0, 10.0);
            planeta->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, true, true, num_instancias, tipoIlumniacion);
         glPopMatrix();
      break;
      case TODOS:
         cubo->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipoIlumniacion);
         glPushMatrix();
            glTranslatef(100.0, 0, 0);
            tetraedro->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipoIlumniacion);
            glTranslatef(100.0, 0, 0);
            cono->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapaInferior, true, num_instancias, tipoIlumniacion);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(-100.0, 0, 0);
            objRevolucion->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapaInferior, tapaSuperior, num_instancias, tipoIlumniacion);
            glTranslatef(-100.0, 0, 0);
            cilindro->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapaInferior, tapaSuperior, num_instancias, tipoIlumniacion);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(0, 0, -200.0);
            objPLY->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipoIlumniacion);
            glTranslatef(300.0, 0, 0);
            esfera->cambiarMaterial(mat);
            esfera->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, true, true, num_instancias, tipoIlumniacion);
         glPopMatrix();
      break;
      case PRACTICA3:
         glPushMatrix();
            glTranslatef(-50.0, 0, 0);
            peon_blanco->cambiarMaterial(mat_blanco);
            peon_blanco->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapaInferior, tapaSuperior, num_instancias, tipoIlumniacion);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(50.0, 0, 0);
            peon_negro->cambiarMaterial(mat_negro);
            peon_negro->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapaInferior, tapaSuperior, num_instancias, tipoIlumniacion);
         glPopMatrix();
      break;
      case JERARQUICO:
         glPushMatrix();
            glTranslatef(0.0, 700.0, 0.0);
            //glScalef(20.0, 20.0, 1.0);
            //cuadro->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipoIlumniacion);
            skyBox->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipoIlumniacion);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(-400.0, -300.0, -500.0);
            glScalef(7.0, 7.0, 7.0);
            tetraedro->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tipoIlumniacion);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(400.0, 600.0, -400.0);
            glRotatef(-90, 0.0, 1.0, 0.0);
            glScalef(4.0, 4.0, 4.0);
            //planeta->cambiarMaterial(mat);
            planeta->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, true, true, num_instancias, tipoIlumniacion);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(0.0, -205.0, 0.0);
            glScalef(0.5, 0.5, 0.5);
            personaje->draw(modoDibu, caraOculta, modoPunto, modoLinea, modoSolido, modoAjedrez, tapaInferior, tapaSuperior, num_instancias, tipoIlumniacion);
         glPopMatrix();
      break;
      case NINGUNO:
      break;
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   bool salir=false;

   // Moviemiento primera persona WASD
   switch ( toupper(tecla) )
   {
	   case 'A':
         // Observer_angle_y-- ;
         if(!objetoSeleccionadoEnCamara[camaraActiva])
            camaras[camaraActiva]->mover(2);
         break;
	   case 'D':
         // Observer_angle_y++ ;
         if(!objetoSeleccionadoEnCamara[camaraActiva])
            camaras[camaraActiva]->mover(3);
         break;
	   case 'W':
         // Observer_angle_x-- ;
         if(!objetoSeleccionadoEnCamara[camaraActiva])
            camaras[camaraActiva]->mover(0);
         break;
	   case 'S':
         // Observer_angle_x++ ;
         if(!objetoSeleccionadoEnCamara[camaraActiva])
            camaras[camaraActiva]->mover(1);
	}
   change_projection();

   if(modoMenu == NADA){
      // cout << "  Tecla pulsada: '" << tecla << "'" << endl;
      switch( toupper(tecla) )
      {
         case 'Q':
               salir=true;
            break;
         case 'O':
            // ESTAMOS EN MODO SELECCION DE OBJETO
            modoMenu=SELOBJETO; 
            printf("  Modo de Seleccion de objeto. Opciones disponibles: \n    'Q': Atras\n    'C': Cubo\n    'T': Tetraedro\n    'P': PLY\n    'R': Perfil Revolucion PLY\n    'L': Cilindro\n    'O': Cono\n    'E': Esfera\n    'N': Todos los Objetos\n    '3': Escena Práctica 3\n    'J': Objeto Jerárquico\n");
            break;
         case 'V':
            // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
            modoMenu=SELVISUALIZACION;
            printf("  Modo de Seleccion de visualizacion. Opciones disponibles: \n    'Q': Atras\n    'P': Activar/Desactivar modo Punto\n    'L': Activar/Desactivar modo Linea\n    'K': Activar/Desactivar modo Solido\n    'N': Activar/Desactivar modo Ajedrez\n    'I': Activar/Desactivar modo Iluminación\n");
            break;
         case 'H':
            // ESTAMOS EN MODO SELECCION DE DIBUJADO
            modoMenu=SELDIBUJADO;
            printf("  Modo de Seleccion de dibujado. Opciones disponibles: \n    'Q': Atras\n    '1': glDrawElements\n    '2': Vertex Buffer Objects\n");
            break;
         case 'F':
            // ESTAMOS EN MODO SELECCION DE CARAS OCULTAS
            modoMenu=CARAOCULTA;
            printf("  Activar/Desactivar caras ocultas. Opciones disponibles: \n    'Q': Atras\n    'N': Activar\n    'H': Desactivar\n");
            break;
         case 'T':
            // ESTAMOS EN MODO SELECCION DE VISUALIZACION DE TAPAS
            modoMenu=TAPAS;
            printf("  Activar/Desactivar Tapas objeto revolucion. Opciones disponibles: \n    'Q': Atras\n    'N': Activa Tapas\n    'H': Desactivar Tapas\n");
            break;
         case 'N':
            // ESTAMOS EN MODO SELECCION DE MOVIMIENTO AUTOMATICO
            modoMenu=AUTO;
            printf("  Activar/Desactivar animación automática. Opciones disponibles: \n    'Q': Atras\n    '+': Aumentar velocidad\n    '-': Disminuir velocidad\n");
            break;
         case 'M':
            // ESTAMOS EN MODO SELECCION DE MOVIMIENTO
            modoMenu=MOVER;
            printf("  Mover grados de libertad (Objeto Jerárquico). Opciones disponibles: \n    'Q': Salir \n    'B': Mover brazo \n    'P': Mover pierna \n    'E': Mover espada \n");
            break;
         case 'C':
            // ESTAMOS EN MODO SELECCION DE MOVIMIENTO
            modoMenu=SELCAMARA;
            printf("  Seleccionar camará de la escena. Opciones disponibles: \n    'Q': Salir \n    '0': Camara 0 \n    '1': Camara 1 \n    '2': Camara 2 \n");
            break;
         case 'L':
            // ESTAMOS EN MODO SELECCION DE MOVIMIENTO
            objetoSeleccionadoEnCamara[camaraActiva]=false;
            devolverMaterial();
            tipoObjetoSeleccionadoEnCamara[camaraActiva] = NOBJECT;
            printf("  Cámara en modo libre\n");
            break;
      }
   }else{
      // cout << "    Tecla pulsada: '" << tecla << "'" << endl;
      if(modoMenu == SELOBJETO){
         switch( toupper(tecla) )
         {
            case 'Q':
               if (modoMenu!=NADA)
                  modoMenu=NADA;
               // Mostramos las opciones del menu
               printf("Opciones disponibles: \n  'Q': Salir \n  'O': Modo Seleccion de objeto \n  'V': Modo Seleccion de visualizacion \n  'H': Modo Seleccion de dibujado\n  'F': Activar/Desactivar caras ocultas\n  'T': Visualizacion de Tapas en Objeto Revolucion\n  'N': Activar/Desactivar animación automática\n  'M': Mover grados de libertad (Objeto Jerárquico)\n  'C': Modo selección de Cámara\n  'L': Cámara libre\n");            
               break;
            case 'C':
               objetoActivo = CUBO;
               break;
            case 'T':
               objetoActivo = TETRAEDRO;
               break;
            case 'P':
               objetoActivo = PLY;
               break;
            case 'R':
               objetoActivo = REVOLUCION;
               break;
            case 'L':
               objetoActivo = CILINDRO;
               break; 
            case 'O':
               objetoActivo = CONO;
               break;
            case 'E':
               objetoActivo = ESFERA;
               break;
            case 'N':
               objetoActivo = TODOS;
               break;
            case '3':
               objetoActivo = PRACTICA3;
               break;
            case 'J':
               objetoActivo = JERARQUICO;
               break;    
            default:
               printf("    No está eligiendo una opción válida\n");
               break;
         }
      }else if(modoMenu == SELVISUALIZACION){
         switch( toupper(tecla) )
         {
            case 'Q':
               if (modoMenu!=NADA)
                  modoMenu=NADA;
               // Mostramos las opciones del menu
               printf("Opciones disponibles: \n  'Q': Salir \n  'O': Modo Seleccion de objeto \n  'V': Modo Seleccion de visualizacion \n  'H': Modo Seleccion de dibujado\n  'F': Activar/Desactivar caras ocultas\n  'T': Visualizacion de Tapas en Objeto Revolucion\n  'N': Activar/Desactivar animación automática\n  'M': Mover grados de libertad (Objeto Jerárquico)\n  'C': Modo selección de Cámara\n  'L': Cámara libre\n");            
               break;
            case 'L':
               if(modoLinea)
                  modoLinea = false;
               else
                  modoLinea = true;
               break;
            case 'P':
               if(modoPunto)
                  modoPunto = false;
               else
                  modoPunto = true;
               break;
            case 'K':
               if(modoSolido)
                  modoSolido = false;
               else
                  modoSolido = true;
               break;
            case 'N':
               if(modoAjedrez)
                  modoAjedrez = false;
               else
                  modoAjedrez = true;
               break;
            case 'I':
               modoMenu=ILUMINACION;
               if(modoIluminacion)
                  printf("      Tipo de iluminación. Opciones disponibles: \n        'Q': Salir \n        'K': Modo Smooth \n        'F': Modo Flat \n        'E': Quitar Iluminacion\n        '0': Activar/Desactivar Luz0\n        '1': Activar/Desactivar Luz1\n        '2': Activar/Desactivar Luz2\n        '3': Activar/Desactivar Luz3\n        '4': Activar/Desactivar Luz4\n        '5': Activar/Desactivar Luz5\n        '6': Activar/Desactivar Luz6\n        '7': Activar/Desactivar Luz7\n        'N': Modo variación del angulo alfa\n        'B': Modo variación del angulo beta\n        'P': Animación automática luz puntual\n");            
               else
                  printf("      Tipo de iluminación. Opciones disponibles: \n        'Q': Salir \n        'K': Modo Smooth \n        'F': Modo Flat \n");            
               break;
            default:
               printf("    No está eligiendo una opción válida\n");
               break;
         }
      }else if(modoMenu == SELDIBUJADO){
         switch( toupper(tecla) )
         {
            case 'Q':
               if (modoMenu!=NADA)
                  modoMenu=NADA;
               // Mostramos las opciones del menu
               printf("Opciones disponibles: \n  'Q': Salir \n  'O': Modo Seleccion de objeto \n  'V': Modo Seleccion de visualizacion \n  'H': Modo Seleccion de dibujado\n  'F': Activar/Desactivar caras ocultas\n  'T': Visualizacion de Tapas en Objeto Revolucion\n  'N': Activar/Desactivar animación automática\n  'M': Mover grados de libertad (Objeto Jerárquico)\n  'C': Modo selección de Cámara\n  'L': Cámara libre\n");            
               break;
            case '1':
               modoDibu = GLDRAW;
               break;
            case '2':
               modoDibu = VBO;
               break;
            default:
               printf("    No está eligiendo una opción válida\n");
               break;
         }
      }else if(modoMenu == CARAOCULTA){
         switch( toupper(tecla) )
         {
            case 'Q':
               if (modoMenu!=NADA)
                  modoMenu=NADA;
               // Mostramos las opciones del menu
               printf("Opciones disponibles: \n  'Q': Salir \n  'O': Modo Seleccion de objeto \n  'V': Modo Seleccion de visualizacion \n  'H': Modo Seleccion de dibujado\n  'F': Activar/Desactivar caras ocultas\n  'T': Visualizacion de Tapas en Objeto Revolucion\n  'N': Activar/Desactivar animación automática\n  'M': Mover grados de libertad (Objeto Jerárquico)\n  'C': Modo selección de Cámara\n  'L': Cámara libre\n");            
               break;
            case 'N':
               caraOculta = ACTIVADO;
               break;
            case 'H':
               caraOculta = DESACTIVADO;
               break;
            default:
               printf("    No está eligiendo una opción válida\n");
               break;
         }
      }else if(modoMenu == TAPAS){
         switch( toupper(tecla) )
         {
            case 'Q':
               if (modoMenu!=NADA)
                  modoMenu=NADA;
               // Mostramos las opciones del menu
               printf("Opciones disponibles: \n  'Q': Salir \n  'O': Modo Seleccion de objeto \n  'V': Modo Seleccion de visualizacion \n  'H': Modo Seleccion de dibujado\n  'F': Activar/Desactivar caras ocultas\n  'T': Visualizacion de Tapas en Objeto Revolucion\n  'N': Activar/Desactivar animación automática\n  'M': Mover grados de libertad (Objeto Jerárquico)\n  'C': Modo selección de Cámara\n  'L': Cámara libre\n");            
               break;
            case 'N':
               tapaInferior = true;
               tapaSuperior = true;
               break;
            case 'H':
               tapaInferior = false;
               tapaSuperior = false;
               break;
            default:
               printf("    No está eligiendo una opción válida\n");
               break;
         }
      }else if(modoMenu == ILUMINACION){
         switch( toupper(tecla) )
         {
            case 'Q':
               modoMenu=SELVISUALIZACION;
               // Menu de visualizacion
               printf("  Modo de Seleccion de visualizacion. Opciones disponibles: \n    'Q': Atras\n    'P': Activar/Desactivar modo Punto\n    'L': Activar/Desactivar modo Linea\n    'K': Activar/Desactivar modo Solido\n    'N': Activar/Desactivar modo Ajedrez\n    'I': Activar/Desactivar modo Iluminación\n");           
               break;
            case 'K':
               modoIluminacion = true;
               tipoIlumniacion = GL_SMOOTH;
               // Mostramos las opciones del menu
               if(modoIluminacion)
                  printf("      Tipo de iluminación. Opciones disponibles: \n        'Q': Salir \n        'K': Modo Smooth \n        'F': Modo Flat \n        'E': Quitar Iluminacion\n        '0': Activar/Desactivar Luz0\n        '1': Activar/Desactivar Luz1\n        '2': Activar/Desactivar Luz2\n        '3': Activar/Desactivar Luz3\n        '4': Activar/Desactivar Luz4\n        '5': Activar/Desactivar Luz5\n        '6': Activar/Desactivar Luz6\n        '7': Activar/Desactivar Luz7\n        'N': Modo variación del angulo alfa\n        'B': Modo variación del angulo beta\n        'P': Animación automática luz puntual\n");            
               else
                  printf("      Tipo de iluminación. Opciones disponibles: \n        'Q': Salir \n        'K': Modo Smooth \n        'F': Modo Flat \n");            
               break;
            case 'F':
               modoIluminacion = true;
               tipoIlumniacion = GL_FLAT;
               // Mostramos las opciones del menu
               if(modoIluminacion)
                  printf("      Tipo de iluminación. Opciones disponibles: \n        'Q': Salir \n        'K': Modo Smooth \n        'F': Modo Flat \n        'E': Quitar Iluminacion\n        '0': Activar/Desactivar Luz0\n        '1': Activar/Desactivar Luz1\n        '2': Activar/Desactivar Luz2\n        '3': Activar/Desactivar Luz3\n        '4': Activar/Desactivar Luz4\n        '5': Activar/Desactivar Luz5\n        '6': Activar/Desactivar Luz6\n        '7': Activar/Desactivar Luz7\n        'N': Modo variación del angulo alfa\n        'B': Modo variación del angulo beta\n        'P': Animación automática luz puntual\n");            
               else
                  printf("      Tipo de iluminación. Opciones disponibles: \n        'Q': Salir \n        'K': Modo Smooth \n        'F': Modo Flat \n");            
               break;
            case 'E':
               modoIluminacion = false;
               // Mostramos las opciones del menu
               printf("      Tipo de iluminación. Opciones disponibles: \n        'Q': Salir \n        'K': Modo Smooth \n        'F': Modo Flat \n");
               break;      
         }
         if(modoIluminacion){
            switch( toupper(tecla) )
            {
               case '0':
                  luces_activas[0] = !luces_activas[0];
                  break;
               case '1':
                  luces_activas[1] = !luces_activas[1];
                  break;
               case '2':  
                  printf("  LUZ2\n");
                  break;
               case '3':  
                  printf("  LUZ3\n");
                  break;
               case '4':  
                  printf("  LUZ4\n");
                  break;
               case '5':  
                  printf("  LUZ5\n");
                  break;
               case '6':  
                  printf("  LUZ6\n");
                  break;
               case '7':  
                  printf("  LUZ7\n");
                  break;
               case 'N':
                  modoMenu = ALPHA;
                  printf("        Incrementar/Decrementar angulo Alpha. Opciones disponibles: \n          'Q': Atras\n          '>': Incrementar angulo Alpha\n          '<': Decrementar angulo Alpha\n");
                  break;
               case 'B':
                  modoMenu = BETA;
                  printf("        Incrementar/Decrementar angulo Beta. Opciones disponibles: \n          'Q': Atras\n          '>': Incrementar angulo Beta\n          '<': Decrementar angulo Beta\n");
                  break;
               case 'P':
                  if(!animacion_luz)
                     animacion_luz = true;
                  else
                     animacion_luz = false;
                  break;
            }
         }
      }else if(modoMenu == ALPHA){
         switch( toupper(tecla) )
         {
            case 'Q':
               modoMenu=ILUMINACION;
               // Mostramos las opciones del menu
               printf("      Tipo de iluminación. Opciones disponibles: \n        'Q': Salir \n        'K': Modo Smooth \n        'F': Modo Flat \n        'E': Quitar Iluminacion\n        '0': Activar/Desactivar Luz0\n        '1': Activar/Desactivar Luz1\n        '2': Activar/Desactivar Luz2\n        '3': Activar/Desactivar Luz3\n        '4': Activar/Desactivar Luz4\n        '5': Activar/Desactivar Luz5\n        '6': Activar/Desactivar Luz6\n        '7': Activar/Desactivar Luz7\n        'N': Modo variación del angulo alfa\n        'B': Modo variación del angulo beta\n        'P': Animación automática luz puntual\n");
               break;
            case '>':
               luz_direccional->incrementarAlpha();
               printf("          Incrementando angulo Alpha...\n");            
               break;
            case '<':
               luz_direccional->decrementarAlpha();
               printf("          Decrementando angulo Alpha...\n");            
               break;
            default:
               printf("          No está eligiendo una opción válida\n");
               break;
         }
      }else if(modoMenu == BETA){
         switch( toupper(tecla) )
         {
            case 'Q':
               modoMenu=ILUMINACION;
               // Mostramos las opciones del menu
               printf("      Tipo de iluminación. Opciones disponibles: \n        'Q': Salir \n        'K': Modo Smooth \n        'F': Modo Flat \n        'E': Quitar Iluminacion\n        '0': Activar/Desactivar Luz0\n        '1': Activar/Desactivar Luz1\n        '2': Activar/Desactivar Luz2\n        '3': Activar/Desactivar Luz3\n        '4': Activar/Desactivar Luz4\n        '5': Activar/Desactivar Luz5\n        '6': Activar/Desactivar Luz6\n        '7': Activar/Desactivar Luz7\n        'N': Modo variación del angulo alfa\n        'B': Modo variación del angulo beta\n        'P': Animación automática luz puntual\n");
               break;
            case '>':
               luz_direccional->incrementarBeta(5);
               printf("          Incrementando angulo Beta...\n");            
               break;
            case '<':
               luz_direccional->decrementarBeta(5);
               printf("          Decrementando angulo Beta...\n");            
               break;
            default:
               printf("          No está eligiendo una opción válida\n");
               break;
         }
      }else if(modoMenu == AUTO){
         switch( toupper(tecla) )
         {
            case 'Q':
               if (modoMenu!=NADA)
                  modoMenu=NADA;
               // Mostramos las opciones del menu
               printf("Opciones disponibles: \n  'Q': Salir \n  'O': Modo Seleccion de objeto \n  'V': Modo Seleccion de visualizacion \n  'H': Modo Seleccion de dibujado\n  'F': Activar/Desactivar caras ocultas\n  'T': Visualizacion de Tapas en Objeto Revolucion\n  'N': Activar/Desactivar animación automática\n  'M': Mover grados de libertad (Objeto Jerárquico)\n  'C': Modo selección de Cámara\n  'L': Cámara libre\n");            
               break;
            case '+':
               printf("    Aumentando la velocidad...\n");
               velocidad_personaje += 0.005;
               velocidad_espada += 0.00005;
               break;
            case '-':
               printf("    Decrementando la velocidad...\n");
               velocidad_personaje -= 0.005;
               velocidad_espada -= 0.00005;
               break;
            default:
               printf("    No está eligiendo una opción válida\n");
               break;
         }
      }else if(modoMenu == MOVER){
         if(pCuerpo == VACIO){
            switch( toupper(tecla) )
            {
               case 'Q':
                  if (modoMenu!=NADA)
                     modoMenu=NADA;
                  movPersonaje = NO;
                  // Mostramos las opciones del menu
                  printf("Opciones disponibles: \n  'Q': Salir \n  'O': Modo Seleccion de objeto \n  'V': Modo Seleccion de visualizacion \n  'H': Modo Seleccion de dibujado\n  'F': Activar/Desactivar caras ocultas\n  'T': Visualizacion de Tapas en Objeto Revolucion\n  'N': Activar/Desactivar animación automática\n  'M': Mover grados de libertad (Objeto Jerárquico)\n  'C': Modo selección de Cámara\n  'L': Cámara libre\n");            
                  break;
               case 'B':
                  printf("    Mover grados de libertad (Brazo). Opciones disponibles: \n    'Q': Salir \n    '0': Ángulo Alpha Hombro Derecho\n    '1': Ángulo Beta Hombro Derecho\n    '2': Ángulo Alpha Codo Derecho\n    '3': Ángulo Beta Codo Derecho\n    '4': Ángulo Alpha Hombro Izquierdo\n    '5': Ángulo Beta Hombro Izquierdo\n    '6': Ángulo Alpha Codo Izquierdo\n    '7': Ángulo Beta Codo Izquierdo\n");            
                  pCuerpo = BRAZO;
                  break;
               case 'P':
                  printf("    Mover grados de libertad (Pierna). Opciones disponibles: \n    'Q': Salir \n    '0': Ángulo Alpha Gluteo Derecho\n    '1': Ángulo Beta Gluteo Derecho\n    '2': Ángulo Alpha Rodilla Derecho\n    '3': Ángulo Beta Rodilla Derecho\n    '4': Ángulo Alpha Gluteo Izquierdo\n    '5': Ángulo Beta Gluteo Izquierdo\n    '6': Ángulo Alpha Rodilla Izquierdo\n    '7': Ángulo Beta Rodilla Izquierdo\n");
                  pCuerpo = PIERNA;
                  break;
               case 'E':
                  printf("    Mover grados de libertad (Espada). Opciones disponibles: \n    'Q': Salir \n    '0': Ángulo Alpha Espada\n    '1': Ángulo Beta Espada\n    '2': Valor Escalado Espada\n");
                  pCuerpo = ESPADA;
                  break;
               default:
                  printf("    No está eligiendo una opción válida\n");
                  break;
            }
         }else if(pCuerpo == BRAZO){
            switch( toupper(tecla) )
            {
               case 'Q':
                  pCuerpo = VACIO;
                  // Mostramos las opciones del menu
                  printf("  Mover grados de libertad (Objeto Jerárquico). Opciones disponibles: \n    'Q': Salir \n    'B': Mover brazo \n    'P': Mover pierna \n    'E': Mover espada \n");           
                  break;
               case '0':
                  printf("      Seleccionado Alpha Hombro Derecho\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = ALPHA_HOMBRO_DCH;
                  break;
               case '1':
                  printf("      Seleccionado Beta Hombro Derecho\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = BETA_HOMBRO_DCH;
                  break;
               case '2':
                  printf("      Seleccionado Alpha Codo Derecho\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = ALPHA_CODO_DCH;
                  break;
               case '3':
                  printf("      Seleccionado Beta Codo Derecho\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = BETA_CODO_DCH;
                  break;
               case '4':
                  printf("      Seleccionado Alpha Hombro Izquierdo\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = ALPHA_HOMBRO_IZQ;
                  break;
               case '5':
                  printf("      Seleccionado Beta Hombro Derecho\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = BETA_HOMBRO_IZQ;
                  break;
               case '6':
                  printf("      Seleccionado Alpha Codo Izquierdo\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = ALPHA_CODO_IZQ;
                  break;
               case '7':
                  printf("      Seleccionado Beta Codo Izquierdo\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = BETA_CODO_IZQ;
                  break;
            }
            if(movPersonaje == ALPHA_HOMBRO_DCH){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Alpha Hombro Derecho...\n");
                     personaje->modificarGiroAlphaHombroDerecho(5);
                     break;
                  case '-':
                     printf("        Decrementando Alpha Hombro Derecho\n");
                     personaje->modificarGiroAlphaHombroDerecho(-5);
                     break;
               }
            }else if(movPersonaje == BETA_HOMBRO_DCH){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Beta Hombro Derecho...\n");
                     personaje->modificarGiroBetaHombroDerecho(5);
                     break;
                  case '-':
                     printf("        Decrementando Beta Hombro Derecho...\n");
                     personaje->modificarGiroBetaHombroDerecho(-5);
                     break;
               }
            }else if(movPersonaje == ALPHA_HOMBRO_IZQ){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Alpha Hombro Izquierdo...\n");
                     personaje->modificarGiroAlphaHombroIzquierdo(5);
                     break;
                  case '-':
                     printf("        Decrementando Alpha Hombro Izquierdo...\n");
                     personaje->modificarGiroAlphaHombroIzquierdo(-5);
                     break;
               }
            }else if(movPersonaje == BETA_HOMBRO_IZQ){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Beta Hombro Izquierdo...\n");
                     personaje->modificarGiroBetaHombroIzquierdo(5);
                     break;
                  case '-':
                     printf("        Decrementando Beta Hombro Izquierdo\n");
                     personaje->modificarGiroBetaHombroIzquierdo(-5);
                     break;
               }
            }else if(movPersonaje == ALPHA_CODO_DCH){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Alpha Codo Derecho...\n");
                     personaje->modificarGiroAlphaCodoDerecho(5);
                     break;
                  case '-':
                     printf("        Decrementando Alpha Codo Derecho\n");
                     personaje->modificarGiroAlphaCodoDerecho(-5);
                     break;
               }
            }else if(movPersonaje == BETA_CODO_DCH){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Beta Codo Derecho...\n");
                     personaje->modificarGiroBetaCodoDerecho(5);
                     break;
                  case '-':
                     printf("        Decrementando Beta Codo Derecho...\n");
                     personaje->modificarGiroBetaCodoDerecho(-5);
                     break;
               }
            }else if(movPersonaje == ALPHA_CODO_IZQ){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Alpha Codo Izquierdo...\n");
                     personaje->modificarGiroAlphaCodoIzquierdo(5);
                     break;
                  case '-':
                     printf("        Decrementando Alpha Codo Izquierdo...\n");
                     personaje->modificarGiroAlphaCodoIzquierdo(-5);
                     break;
               }
            }else if(movPersonaje == BETA_CODO_IZQ){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Beta Codo Izquierdo...\n");
                     personaje->modificarGiroBetaCodoIzquierdo(5);
                     break;
                  case '-':
                     printf("        Decrementando Beta Codo Izquierdo\n");
                     personaje->modificarGiroBetaCodoIzquierdo(-5);
                     break;
               }
            }
         }else if(pCuerpo == PIERNA){
            switch( toupper(tecla) )
            {
               case 'Q':
                  pCuerpo = VACIO;
                  // Mostramos las opciones del menu
                  printf("  Mover grados de libertad (Objeto Jerárquico). Opciones disponibles: \n    'Q': Salir \n    'B': Mover brazo \n    'P': Mover pierna \n    'E': Mover espada \n");           
                  break;
               case '0':
                  printf("      Seleccionado Alpha Gluteo Derecho\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = ALPHA_GLUTEO_DCH;
                  break;
               case '1':
                  printf("      Seleccionado Beta Gluteo Derecho\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = BETA_GLUTEO_DCH;
                  break;
               case '2':
                  printf("      Seleccionado Alpha Rodilla Derecho\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = ALPHA_RODILLA_DCH;
                  break;
               case '3':
                  printf("      Seleccionado Beta Rodilla Derecho\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = BETA_RODILLA_DCH;
                  break;
               case '4':
                  printf("      Seleccionado Alpha Gluteo Izquierdo\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = ALPHA_GLUTEO_IZQ;
                  break;
               case '5':
                  printf("      Seleccionado Beta Gluteo Derecho\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = BETA_GLUTEO_IZQ;
                  break;
               case '6':
                  printf("      Seleccionado Alpha Rodilla Izquierdo\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = ALPHA_RODILLA_IZQ;
                  break;
               case '7':
                  printf("      Seleccionado Beta Rodilla Izquierdo\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = BETA_RODILLA_IZQ;
                  break;
            }
            if(movPersonaje == ALPHA_GLUTEO_DCH){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Alpha Gluteo Derecho...\n");
                     personaje->modificarGiroAlphaGluteoDerecho(5);
                     break;
                  case '-':
                     printf("        Decrementando Alpha Gluteo Derecho\n");
                     personaje->modificarGiroAlphaGluteoDerecho(-5);
                     break;
               }
            }else if(movPersonaje == BETA_GLUTEO_DCH){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Beta Gluteo Derecho...\n");
                     personaje->modificarGiroBetaGluteoDerecho(5);
                     break;
                  case '-':
                     printf("        Decrementando Beta Gluteo Derecho...\n");
                     personaje->modificarGiroBetaGluteoDerecho(-5);
                     break;
               }
            }else if(movPersonaje == ALPHA_GLUTEO_IZQ){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Alpha Gluteo Izquierdo...\n");
                     personaje->modificarGiroAlphaGluteoIzquierdo(5);
                     break;
                  case '-':
                     printf("        Decrementando Alpha Gluteo Izquierdo...\n");
                     personaje->modificarGiroAlphaGluteoIzquierdo(-5);
                     break;
               }
            }else if(movPersonaje == BETA_GLUTEO_IZQ){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Beta Gluteo Izquierdo...\n");
                     personaje->modificarGiroBetaGluteoIzquierdo(5);
                     break;
                  case '-':
                     printf("        Decrementando Beta Gluteo Izquierdo\n");
                     personaje->modificarGiroBetaGluteoIzquierdo(-5);
                     break;
               }
            }else if(movPersonaje == ALPHA_RODILLA_DCH){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Alpha Rodilla Derecho...\n");
                     personaje->modificarGiroAlphaRodillaDerecho(5);
                     break;
                  case '-':
                     printf("        Decrementando Alpha Rodilla Derecho\n");
                     personaje->modificarGiroAlphaRodillaDerecho(-5);
                     break;
               }
            }else if(movPersonaje == BETA_RODILLA_DCH){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Beta Rodilla Derecho...\n");
                     personaje->modificarGiroBetaRodillaDerecho(5);
                     break;
                  case '-':
                     printf("        Decrementando Beta Rodilla Derecho...\n");
                     personaje->modificarGiroBetaRodillaDerecho(-5);
                     break;
               }
            }else if(movPersonaje == ALPHA_RODILLA_IZQ){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Alpha Rodilla Izquierdo...\n");
                     personaje->modificarGiroAlphaRodillaIzquierdo(5);
                     break;
                  case '-':
                     printf("        Decrementando Alpha Rodilla Izquierdo...\n");
                     personaje->modificarGiroAlphaRodillaIzquierdo(-5);
                     break;
               }
            }else if(movPersonaje == BETA_RODILLA_IZQ){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Beta Rodilla Izquierdo...\n");
                     personaje->modificarGiroBetaRodillaIzquierdo(5);
                     break;
                  case '-':
                     printf("        Decrementando Beta Rodilla Izquierdo\n");
                     personaje->modificarGiroBetaRodillaIzquierdo(-5);
                     break;
               }
            }
         }else if(pCuerpo == ESPADA){
            switch( toupper(tecla) )
            {
               case 'Q':
                  pCuerpo = VACIO;
                  // Mostramos las opciones del menu
                  printf("  Mover grados de libertad (Objeto Jerárquico). Opciones disponibles: \n    'Q': Salir \n    'B': Mover brazo \n    'P': Mover pierna \n    'E': Mover espada \n");           
                  break;
               case '0':
                  printf("      Seleccionado Alpha Espada\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = ALPHA_ESPADA;
                  break;
               case '1':
                  printf("      Seleccionado Beta Espada\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = BETA_ESPADA;
                  break;
               case '2':
                  printf("      Seleccionado Escalado Espada\n      '+': Aumentar grado\n      '-': Disminuir grado\n");
                  movPersonaje = ESCALADO_ESPADA;
                  break;
            }
            if(movPersonaje == ALPHA_ESPADA){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Alpha Espada...\n");
                     personaje->modificarAlphaEspada(5);
                     break;
                  case '-':
                     printf("        Decrementando Alpha Espada...\n");
                     personaje->modificarAlphaEspada(-5);
                     break;
               }
            }else if(movPersonaje == BETA_ESPADA){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Beta Espada...\n");
                     personaje->modificarBetaEspada(5);
                     break;
                  case '-':
                     printf("        Decrementando Beta Espada\n");
                     personaje->modificarBetaEspada(-5);
                     break;
               }
            }else if(movPersonaje == ESCALADO_ESPADA){
               switch( toupper(tecla) )
               {
                  case '+':
                     printf("        Aumentando Escalado Espada...\n");
                     personaje->modificarEscaladoLaser(0.1);
                     break;
                  case '-':
                     printf("        Decrementando Escalado Espada\n");
                     personaje->modificarEscaladoLaser(-0.1);
                     break;
               }
            }
         }
      }else if(modoMenu == SELCAMARA){
         switch( toupper(tecla) )
         {
            case 'Q':
               if (modoMenu!=NADA)
                  modoMenu=NADA;
               // Mostramos las opciones del menu
               printf("Opciones disponibles: \n  'Q': Salir \n  'O': Modo Seleccion de objeto \n  'V': Modo Seleccion de visualizacion \n  'H': Modo Seleccion de dibujado\n  'F': Activar/Desactivar caras ocultas\n  'T': Visualizacion de Tapas en Objeto Revolucion\n  'N': Activar/Desactivar animación automática\n  'M': Mover grados de libertad (Objeto Jerárquico)\n  'C': Modo selección de Cámara\n  'L': Cámara libre\n");            
               break;
            case '0':
               devolverMaterial();
               camaraActiva = 0;
               if(objetoSeleccionadoEnCamara[camaraActiva])
                  pintarObjetoSelecionado();
               break;
            case '1':
               devolverMaterial();
               camaraActiva = 1;
               if(objetoSeleccionadoEnCamara[camaraActiva])
                  pintarObjetoSelecionado();
               break;
            case '2':  
               devolverMaterial();
               camaraActiva = 2;
               if(objetoSeleccionadoEnCamara[camaraActiva])
                  pintarObjetoSelecionado();
               break;
         }
      }
   }
   
   return salir;
}

// **************************************************************************
//
// función de dibujo de la escena: cuando está activado el modo seleccion
//
// **************************************************************************
void Escena::dibujaSeleccion(){
   // deshabilitamos el degradado
	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   change_projection();
	change_observer();
   ejes.draw();

   glPushMatrix();
      glTranslatef(0.0, 700.0, 0.0);
      skyBox->modificarColor(Tupla3f{1.0,0.0,0.0});
      skyBox->draw(modoDibu, caraOculta, false, false, true, modoAjedrez, tipoIlumniacion);
   glPopMatrix();
   glPushMatrix();
      glTranslatef(-400.0, -300.0, -500.0);
      glScalef(7.0, 7.0, 7.0);
      tetraedro->modificarColor(Tupla3f{0.0,1.0,0.0});
      tetraedro->draw(modoDibu, caraOculta, false, false, true, modoAjedrez, tipoIlumniacion);
   glPopMatrix();
   glPushMatrix();
      glTranslatef(400.0, 600.0, -400.0);
      glRotatef(-90, 0.0, 1.0, 0.0);
      glScalef(4.0, 4.0, 4.0);
      planeta->modificarColor(Tupla3f{0.0,0.0,1.0});
      planeta->draw(modoDibu, caraOculta, false, false, true, modoAjedrez, true, true, num_instancias, tipoIlumniacion);
   glPopMatrix();
   glPushMatrix();
      glTranslatef(0.0, -205.0, 0.0);
      glScalef(0.5, 0.5, 0.5);
      //personaje->modificarColor(Tupla3f{0.0,0.0,0.0});
      personaje->draw(modoDibu, caraOculta, false, false, true, modoAjedrez, tapaInferior, tapaSuperior, num_instancias, tipoIlumniacion);
   glPopMatrix();

   // volvemos a habilitar todo
   glEnable(GL_DITHER);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

// **************************************************************************
//
// función para pintar el objeto si hay selecionado en las diferentes camaras
//
// **************************************************************************
void Escena::pintarObjetoSelecionado(){
   if( tipoObjetoSeleccionadoEnCamara[camaraActiva] == SKYBOX ){        // ROJO -> SKYBOX
      devolverMaterial();
      skyBox->cambiarMaterial(mat_seleccion);
   }else if( tipoObjetoSeleccionadoEnCamara[camaraActiva] == PIRAMIDE ){  // VERDE -> PIRAMIDE
      devolverMaterial();
      tetraedro->cambiarMaterial(mat_seleccion);
   }else if( tipoObjetoSeleccionadoEnCamara[camaraActiva] == PLANETA ){  // AZUL -> PLANETA
      devolverMaterial();
      planeta->cambiarMaterial(mat_seleccion);
   }else if( tipoObjetoSeleccionadoEnCamara[camaraActiva] == PERSONAJE ){  // NEGRO -> PERSONAJE
      devolverMaterial();
      personaje->setMaterialSeleccion(mat_seleccion);
   }
}

// **************************************************************************
//
// función para obtener el objeto seleccionado
//
// **************************************************************************
void Escena::seleccion(int x, int y){
   glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

   int viewport[4];
	GLfloat pixels[3];

	glGetIntegerv(GL_VIEWPORT, viewport); // Para el height
	glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_FLOAT, (void *) pixels);

	Tupla3f seleccionado = {pixels[0], pixels[1], pixels[2]};

   //printf("ENTRO %f %f %f\n", seleccionado[X], seleccionado[Y], seleccionado[Z]);
   if( seleccionado[X] == 1.0 && seleccionado[Y] == 0.0 && seleccionado[Z] == 0.0 ){        // ROJO -> SKYBOX
      printf("  Has seleccionado el skybox\n");
      devolverMaterial();
      tipoObjetoSeleccionadoEnCamara[camaraActiva] = SKYBOX;
      camaras[camaraActiva]->setAt(Tupla3f{0.0,0.0,0.0}); // Centro
      objetoSeleccionadoEnCamara[camaraActiva] = true;
      skyBox->cambiarMaterial(mat_seleccion);
   }else if( seleccionado[X] == 0.0 && seleccionado[Y] == 1.0 && seleccionado[Z] == 0.0 ){  // VERDE -> PIRAMIDE
      printf("  Has seleccionado la pirámide\n");
      devolverMaterial();
      tipoObjetoSeleccionadoEnCamara[camaraActiva] = PIRAMIDE;
      camaras[camaraActiva]->setAt(Tupla3f{-400.0, -300.0, -500.0}); // Centro
      objetoSeleccionadoEnCamara[camaraActiva] = true;
      tetraedro->cambiarMaterial(mat_seleccion);
   }else if( seleccionado[X] == 0.0 && seleccionado[Y] == 0.0 && seleccionado[Z] == 1.0 ){  // AZUL -> PLANETA
      printf("  Has seleccionado el planeta\n");
      devolverMaterial();
      tipoObjetoSeleccionadoEnCamara[camaraActiva] = PLANETA;
      camaras[camaraActiva]->setAt(Tupla3f{400.0, 600.0, -400.0}); // Centro  
      objetoSeleccionadoEnCamara[camaraActiva] = true;
      planeta->cambiarMaterial(mat_seleccion);
   }else if( seleccionado[X] == 0.0 && seleccionado[Y] == 0.0 && seleccionado[Z] == 0.0 ){  // NEGRO -> PERSONAJE
      printf("  Has seleccionado el personaje\n");
      devolverMaterial();
      tipoObjetoSeleccionadoEnCamara[camaraActiva] = PERSONAJE;
      camaras[camaraActiva]->setAt(Tupla3f{0.0, -205.0, 0.0}); // Centro
      objetoSeleccionadoEnCamara[camaraActiva] = true;
      personaje->setMaterialSeleccion(mat_seleccion);
   }else {
      objetoSeleccionadoEnCamara[camaraActiva] = false;
      tipoObjetoSeleccionadoEnCamara[camaraActiva] = NOBJECT;
   }

   change_observer();
   // volvemos a habilitar todo
   glEnable(GL_DITHER);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

//***************************************************************************
// Funcion auxiliar para la selección de objeto
//
//***************************************************************************
void Escena::devolverMaterial(){
   if(tipoObjetoSeleccionadoEnCamara[camaraActiva] == SKYBOX)
      skyBox->cambiarMaterial(mat_planeta);
   else if(tipoObjetoSeleccionadoEnCamara[camaraActiva] == PIRAMIDE)
      tetraedro->cambiarMaterial(mat_piramide);
   else if(tipoObjetoSeleccionadoEnCamara[camaraActiva] == PLANETA){
      planeta->cambiarMaterial(mat_mate_blanco);
   }
   else if(tipoObjetoSeleccionadoEnCamara[camaraActiva] == PERSONAJE){
      personaje->resetMaterialPersonaje();
   }
}

//***************************************************************************
// Funcion que gestiona el click del raton
//
//***************************************************************************

void Escena::clickRaton(int boton , int estado , int x , int y)
{
   if(boton == GLUT_RIGHT_BUTTON){
      if(MOVIENDO_CAMARA_FIRSTPERSON)
	      MOVIENDO_CAMARA_FIRSTPERSON = false;
      else
	      MOVIENDO_CAMARA_FIRSTPERSON = true;
      xant_firstperson = x ;   // Para que no haga movimientos bruscos
      yant_firstperson = y ;
   } else if (boton == MOUSE_SCROLL_UP ){
		camaras[camaraActiva]->zoom(0.9);
	} else if (boton == MOUSE_SCROLL_DOWN){
		camaras[camaraActiva]->zoom(1.1);
	} else if(boton == GLUT_LEFT_BUTTON && !click){
      coorSeleccionCamara[camaraActiva][X] = x;
      coorSeleccionCamara[camaraActiva][Y] = y;
      dibujaSeleccion();
		seleccion(x,y);
      click = true;
   }else{
      click = false;
   }
   change_projection();
}

//***************************************************************************
// Funcion que gestiona el click del raton
//
//***************************************************************************

void Escena::ratonMovido(int x, int y)
{
	if ( MOVIENDO_CAMARA_FIRSTPERSON || !objetoSeleccionadoEnCamara[camaraActiva] ){
      camaras[ camaraActiva ]->girar(x - xant_firstperson ,y - yant_firstperson );
      xant_firstperson = x ;
      yant_firstperson = y ;
   }else{
      camaras[ camaraActiva ]->girarSeleccionado(x - xant_seleccionado ,y - yant_seleccionado );
      xant_seleccionado = x;
      yant_seleccionado = y;
   }
}

//**************************************************************************
void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         // Observer_angle_y-- ;
         if(!objetoSeleccionadoEnCamara[camaraActiva])
            camaras[camaraActiva]->mover(2);
         break;
	   case GLUT_KEY_RIGHT:
         // Observer_angle_y++ ;
         if(!objetoSeleccionadoEnCamara[camaraActiva])
            camaras[camaraActiva]->mover(3);
         break;
	   case GLUT_KEY_UP:
         // Observer_angle_x-- ;
         if(!objetoSeleccionadoEnCamara[camaraActiva])
            camaras[camaraActiva]->mover(0);
         break;
	   case GLUT_KEY_DOWN:
         // Observer_angle_x++ ;
         if(!objetoSeleccionadoEnCamara[camaraActiva])
            camaras[camaraActiva]->mover(1);
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[camaraActiva]->zoom(0.8);
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[camaraActiva]->zoom(1.2);
         break;
	}
   change_projection();
	//std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la selección de la camara actual
//
// numeroCamara: numero de la camara a seleccionar
//
//***************************************************************************
void Escena::seleccionaCamara(const int numeroCamara){
	camaraActiva = numeroCamara;
	change_projection();
	change_observer();
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection()
{
   // glMatrixMode( GL_PROJECTION );
   // glLoadIdentity();
   // const float wx = float(Height)*ratio_xy ;
   // glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
   // posicion del observador
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   camaras[ camaraActiva ]->setProyeccion();
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   // glMatrixMode(GL_MODELVIEW);
   // glLoadIdentity();
   // glTranslatef( 0.0, 0.0, -Observer_distance );
   // glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   // glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
   glMatrixMode ( GL_MODELVIEW );
   glLoadIdentity ();
   camaras[ camaraActiva ]->setObserver();
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection();
   glViewport( 0, 0, newWidth, newHeight );
}