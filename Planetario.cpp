#include <GL/glut.h>    
#include <AR/gsub.h>    
#include <AR/video.h>   
#include <AR/param.h>   
#include <AR/ar.h>
#include "Mundo.h"

int    patt_id1;            // Identificador unico de la marca
int    patt_id2;            // Identificador unico de la marca
double patt_trans[3][4];   // Matriz de transformacion de la marca



Mundo *mundo;

void print_error (char *error) {//  printf(error); exit(0);
                               }
static void cleanup(void) {   
  arVideoCapStop();            // Libera recursos al salir ...
  arVideoClose();
  argCleanup();
}



void display(void){
    mundo->DrawGLScene();
}

void ControlTeclado (unsigned char key, int x, int y){
    switch(key){
        case '1':
            mundo->foco->switchFoco(0);
            break;
        case '2':
            mundo->foco->switchFoco(1);
            break;
        case '3':
            mundo->foco->switchFoco(2);
            break;
        case '4':
            mundo->foco->switchFoco(3);
            break;
        case '5':
            mundo->foco->switchFoco(4);
            break;
        case '6':
            mundo->foco->switchFoco(5);
            break;
        case '7':
            mundo->foco->switchFoco(6);
            break;
        case '8':
            mundo->foco->switchFoco(7);
            break;
        case '9':
            mundo->apagarFocos();
            break;
        case '0':
            mundo->switchCirculos();
            break;
        case 32:
            mundo->cambiarCamara();
            break;
        case 27:
            cleanup();
            exit(0);
            break;
    }
}

static void draw( void ) {
    double  gl_para[16], OpenGlMat[16];   // Esta matriz 4x4 es la usada por OpenGL
    GLfloat mat_ambient[]     = {0.0, 1.0, 0.0, 0.0}; // propiedades del material RGBA
    GLfloat light_position[]  = {100.0,-200.0,200.0,0.0}; // propiedades del foco XYZW

    argDrawMode3D();              // Cambiamos el contexto a 3D
    argDraw3dCamera(0, 0);        // Y la vista de la camara a 3D
    glClear(GL_DEPTH_BUFFER_BIT); // Limpiamos buffer de profundidad
    glEnable(GL_DEPTH_TEST);glDepthFunc(GL_LEQUAL);
    argConvGlpara(patt_trans, gl_para);   // Convertimos la matriz de

    glMatrixMode(GL_MODELVIEW);         // Modo modelado
    glLoadMatrixd(gl_para);           // Cargamos la matriz de cámara

    glEnable(GL_LIGHTING);  //glEnable(GL_LIGHT0); //Activamos la luz

    glDisable(GL_LIGHTING);
    glBegin(GL_LINES); // pinta los ejes coordenados.
    glColor3f(0.0,0.0,0.5);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(200.0f, 0.0f, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 200.0f, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 200.0f);
    glEnd();
    glTranslatef(0.0, 0.0, 20.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_LIGHTING);  //glEnable(GL_LIGHT0); //Activamos la luz


    mundo->DrawGLScene();

    glDisable(GL_DEPTH_TEST);
}

// ======== init ====================================================
static void init( void ) {
  ARParam  wparam, cparam;   // Parametros intrinsecos de la camara
  int xsize, ysize;          // Tamaño del video de camara (pixels)
  
  // Abrimos dispositivo de video. videoi... i indica el dispositivo 
  if(arVideoOpen("-dev=/dev/video0") < 0) exit(0);  
  if(arVideoInqSize(&xsize, &ysize) < 0) exit(0); //control de tam.

  // Cargamos los parametros intrinsecos de la camara (ya calibrada)
    if(arParamLoad("data/camera_para.dat", 1, &wparam) < 0)   
  //if(arParamLoad("my_camera_HP.dat", 1, &wparam) < 0)    
    print_error ("Error en carga de parametros de camara\n");
  
  arParamChangeSize(&wparam, xsize, ysize, &cparam);
  arInitCparam(&cparam);   // Inicializamos la camara con "cparam"

  // Cargamos la marca que vamos a reconocer en este ejemplo
  if((patt_id1=arLoadPatt("data/senial_1.patt")) < 0){
    cout << "Error >>> Añadir el archivo senial_2.patt en la carpeta 'data'" << endl;
    exit(-1);
  }
  if((patt_id2=arLoadPatt("data/senial_2.patt")) < 0){
    cout << "Error >>> Añadir el archivo senial_2.patt en la carpeta 'data'" << endl;
    exit(-1);
  }



  argInit(&cparam, 1.0, 0, 0, 0, 0);   // Abrimos la ventana
  mundo->InitGL(1024, 768, 100, 100);
}

// ======== mainLoop ================================================
static void mainLoop(void) {
  ARUint8 *dataPtr;
  ARMarkerInfo *marker_info;
  int marker_num, j, k;

  double p_width     = 120.0;        // Ancho y alto del patron en mm (marca)
  double p_center[2] = {0.0, 0.0};   // Centro del patron (marca)

  glutKeyboardFunc(ControlTeclado);

  // Capturamos un frame de la camara de video
  if((dataPtr = (ARUint8 *)arVideoGetImage()) == NULL) {
    // Si devuelve NULL es porque no hay un nuevo frame listo
    arUtilSleep(2);  return;  // Dormimos el hilo 2ms y salimos
  }
  argDrawMode2D(); // Modo 2D para pintar la imagen
  argDispImage(dataPtr, 0,0); // Dibujamos lo que ve la camara (imagen) 
  // Detectamos la marca en el frame capturado (return -1 si error)
  if(arDetectMarker(dataPtr, 100, &marker_info, &marker_num) < 0) {
    cleanup(); exit(0);   // Si devolvio -1, salimos del programa!
  }
  arVideoCapNext();      // Frame pintado y analizado... A por otro!
  
  // Vemos donde detecta el patron con mayor fiabilidad


  k = -1;
  for(j = 0; j < marker_num; j++){
    if(patt_id1 == marker_info[j].id){
      if (k == -1){
          k = j;
      }
      else {
          if(marker_info[k].cf < marker_info[j].cf){
              k = j;
          }
      }
    }
  }


  bool segundoPatt = false;
  for(j = 0; j < marker_num; j++){
    if(patt_id2 == marker_info[j].id){
        segundoPatt = true;
    }
  }
  if(segundoPatt) mundo->lunas = false;
  else mundo->lunas = true;



  if(k != -1) {   // Si ha detectado el patron en algun sitio...
    // Obtener transformacion relativa entre la marca y la camara real (registro)
    arGetTransMat(&marker_info[k], p_center, p_width, patt_trans);

    draw();       // Dibujamos los objetos de la escena
  }

  argSwapBuffers(); // Cambiamos el buffer con lo que tenga dibujado
}

// ======== Main ====================================================
int main(int argc, char **argv) {
  glutInit(&argc, argv);    // Creamos la ventana OpenGL con Glut
  mundo = new Mundo();
  init();                   // Llamada a nuestra funcion de inicio
  arVideoCapStart();        // Creamos un hilo para captura de video
  argMainLoop( NULL, NULL, mainLoop );   // Asociamos callbacks...
  return (0);
}
