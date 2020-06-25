#include <iostream>
#include "Modelo3D.h"
#include "Camara.h"
#include "Foco.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

#include <stdio.h>

#include <vector>
#include <cstring>
#include "Cara.h"
#include "Punto3D.h"
#include "Material.h"
//enum look_type { WIRE = GL_LINES, SOLID = GL_POLYGON, FLAT = GL_FLAT, SMOOTH = GL_SMOOTH};

#include "Parser.h"
#include "util.h"
#include "xmlnode.h"
#include "xmlnodelist.h"
#include "xmlparser.h"

#include <time.h>

class Mundo
{
private:
public:
    bool circulos;
    float angulo;
    Foco *foco;
    Parser *parserMundo;
    vector<Camara> camara;
    vector<Modelo3D> modelos;
    vector<Material> materiales;
    vector<float> vEstrellas;
    bool estrellas;
    bool lunas;

    int numModelos;
    look_type look;
    //vector<Modelo3D> ;
    Camara *camaraSola;
    Modelo3D *modelo3D;
    float alpha;
    float beta;
    int x0, y0;
    int zoom;
    int camaraActiva;
    int numCamaras;
    Mundo();
    void InitParser();
    void InitGL(float Width,float Height, float posx, float posy);
    void iniciar();
    void InitCamaras();
    void encenderCam();
    void setMateriales();
    void onMotion(int x, int y);
    void onMouse(int button, int state, int x, int y);
    void zoomIn();
    void zoomOut();
    void DrawGLScene();
    void dibujarCirculo(GLfloat radioCirculo);
    void cambiarCamara();
    void incrementarTiempo();
    void apagarFocos();
    void switchCirculos();
    void dibujarEstrellas();
    void generarEstrellas(int numEstrellas, int posMax);

};
