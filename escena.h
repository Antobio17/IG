#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzDireccional.h"
#include "luzPosicional.h"
#include "rueda.h"
#include "personaje.h"
#include "cuadro.h"
#include "skyBox.h"
#include "camara.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,CARAOCULTA, TAPAS, ILUMINACION, ALPHA, BETA, AUTO, MOVER, SELCAMARA} menu;
typedef enum {NINGUNO, CUBO, TETRAEDRO, PLY, REVOLUCION, CILINDRO, CONO, ESFERA, TODOS, PRACTICA3, JERARQUICO} objetoVisible;
typedef enum {NO, ALPHA_HOMBRO_DCH, BETA_HOMBRO_DCH, ALPHA_CODO_DCH, BETA_CODO_DCH, ALPHA_HOMBRO_IZQ, BETA_HOMBRO_IZQ, ALPHA_CODO_IZQ, BETA_CODO_IZQ,
              ALPHA_GLUTEO_DCH, BETA_GLUTEO_DCH, ALPHA_RODILLA_DCH, BETA_RODILLA_DCH, ALPHA_GLUTEO_IZQ, BETA_GLUTEO_IZQ, ALPHA_RODILLA_IZQ, BETA_RODILLA_IZQ, ALPHA_ESPADA, BETA_ESPADA, ESCALADO_ESPADA} movimiento;
typedef enum {VACIO, BRAZO, PIERNA, ESPADA} parteCuerpo;
typedef enum {QUIETO, CORRER} acciones;
typedef enum {PERSONAJE, PIRAMIDE, PLANETA, SKYBOX, NOBJECT} ObjetoSeleccionado;

enum {MOUSE_LEFT_BUTTON = 0, MOUSE_MIDDLE_BUTTON = 1, MOUSE_RIGHT_BUTTON = 2, MOUSE_SCROLL_UP = 3, MOUSE_SCROLL_DOWN = 4};

class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection();
	void change_observer();
    


    void clear_window();

    menu modoMenu=NADA;
    movimiento movPersonaje=NO;             // Variable para eleccion de grado de libertad del objeto jerarquico
    parteCuerpo pCuerpo=VACIO;              // Elegir entre pierna o brazo
    objetoVisible objetoActivo;             // Para la seleción del objeto. Por defecto no habrá ninguno selecionado (implementado en el constructor)
    modoDibujado modoDibu;                  // Por defecto dibujará con VBO (implementado en el constructor)
    carasOcultas caraOculta;                // Activar/desactivar caras ocultas. Por defecto estará activado (implementado en el constructor)
    bool modoPunto;                         // Activar/desactivar modo punto. Por defecto estará desactivado (implementado en el constructor)
    bool modoLinea;                         // Activar/desactivar modo linea. Por defecto estará desactivado (implementado en el constructor)
    bool modoSolido;                        // Activar/desactivar modo solido. Por defecto estará activado (implementado en el constructor)
    bool modoAjedrez;                       // Activar/desactivar modo ajedrez. Por defecto estará desactivado (implementado en el constructor)
    bool tapaInferior;                      // Variable para mostrar o no las tapas de los objetos revolución
    bool tapaSuperior;                      // Variable para mostrar o no las tapas de los objetos revolución
    bool modoIluminacion;                   // Variable para activar o desactivar el modo visualización con iluminación
    bool animacion_luz;                     // Variable para activar o desactivar la animación automática de la luz
    int num_instancias;                     // Numero de instancias para los perfiles de revolucion
    GLenum tipoIlumniacion;                 // Variable para definir el tipo de iluminacion
    std::vector<bool> luces_activas;        // Vector de luces para saber si están activas en la escena
    AnguloRotacion angulo_rotacion;         // Angulo sobre el que rotal el perfil de rotacion

    // Variables para la animación
    float velocidad_personaje, velocidad_espada, velocidad_luz_X, velocidad_luz_Y;
    acciones accion;
    // Animación personaje
    float hombro_derecho, codo_derecho, hombro_izquierdo, codo_izquierdo, gluteo_derecho, rodilla_derecha, gluteo_izquierdo, rodilla_izquierda; // Variables para gestionar el valor de la animación
    // Animación espada
    float escalado_espada;
    float alpha_espada, beta_espada;
    bool desplegar_espada, agitar;
    int contador_desplegar;
    

    // Variable para crear materiales
    Material * mat;
    Material * mat_blanco;
    Material * mat_negro;
    Material * mat_verde;
    Material * mat_azul;
    Material * mat_piramide;
    Material * mat_mate_blanco;
    Material * mat_seleccion;
    Material * mat_planeta;

    // Objetos de la escena
    Ejes ejes;
    Cubo * cubo = nullptr;             
    Tetraedro * tetraedro = nullptr;   
    ObjPLY * objPLY = nullptr;         
    ObjRevolucion * objRevolucion = nullptr;
    Cilindro * cilindro = nullptr;
    Cono * cono = nullptr;
    Esfera * esfera = nullptr;
    // Luces
    Luz * cuadro_de_luces = nullptr;
    LuzPosicional * luz_posicional = nullptr;
    LuzDireccional * luz_direccional = nullptr;
    ObjRevolucion * peon_blanco = nullptr;
    ObjRevolucion * peon_negro = nullptr;
    Rueda * rueda = nullptr;
    // Animación final
    Personaje *personaje = nullptr;
    Esfera *planeta = nullptr;
    Cuadro *cuadro = nullptr;
    SkyBox *skyBox = nullptr;
    int contador_luz;

    // Practica Cámara
    Camara * cam = nullptr;
    int camaraActiva;
	std::vector<Camara*> camaras;
    void seleccionaCamara(const int numeroCamara);
    bool MOVIENDO_CAMARA_FIRSTPERSON, click;
    int xant_firstperson, yant_firstperson, xant_seleccionado, yant_seleccionado;
    std::vector<ObjetoSeleccionado> tipoObjetoSeleccionadoEnCamara;
    std::vector<bool> objetoSeleccionadoEnCamara;
    std::vector<Tupla2i> coorSeleccionCamara;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
    void animarModeloJerarquico();

	// Dibujar
	void dibujar() ;
    void dibujaSeleccion();
    void pintarObjetoSelecionado();

    void seleccion(int x, int y);

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
    void clickRaton(int boton , int estado , int x , int y);
    void ratonMovido(int x , int y);

    void devolverMaterial();
};
#endif
