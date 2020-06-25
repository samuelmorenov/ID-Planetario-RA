#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

#include <stdio.h>
#include <iostream>
#include <vector>

#include "Mundo.h"
#include <GL/freeglut_ext.h>

using namespace std;
const int MOUSE_SCROLL_UP = 3;
const int MOUSE_SCROLL_DOWN = 4;
Mundo::Mundo() {
InitParser();//NUEVO

//this->modelo3D2 = new Modelo3D;
iniciar();


numModelos = parserMundo->getNumModelos();
int numMateriales = parserMundo->getNumMateriales();
if(numMateriales != numModelos){
    cout << "El numero de modelos y de materiales es diferente" << endl;
    exit(1);
}
for(int i = 0; i < numModelos; i++){
    modelos[i].Load_Model("data/Esfera.asc");
    modelos[i].setValores(i, parserMundo);
}



//modelo3D->Load_Model(nombre[1]);
look = SMOOTH;
//look = WIRE;
alpha=1;
//camaraActiva=0;
beta=2;
x0=0; y0=0;
zoom = 0;
//numCamaras=3;
angulo = 100;
circulos = true;
estrellas = false;
lunas = true;
}
void Mundo::InitParser(){//NUEVO

    xmlparser * parser;
    xmlnode * gameXML;
    string line,xml;
    ifstream textstream;
    textstream.open("data/config.xml");
    if (!textstream.is_open()){
            cout << endl << ">> Error al abrir el archivo data/config.xml <<"<< endl << endl;
            exit(1);
        }
    while (getline(textstream, line)) {
        xml+=line;
    }
    textstream.close();
    parser = new xmlparser(xml);
    gameXML = parser->getParentNode();
    //parser->printTree(parser->getParentNode()); //Descomentar para imprimir el XML

    parserMundo = new Parser(gameXML); //NUEVO


}
void Mundo::InitGL(float Width,float Height, float posx, float posy){
//    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Llenamos el lienzo de negro
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glutInitWindowSize(Width, Height);
    gluPerspective(40.0f,1.0f,0.01f,50.0f);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_RGBA | GLUT_DEPTH);
    //glutInitWindowPosition(posx, posy);
    //glutCreateWindow("Modelo en almabre con geometría.....");
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    foco=new Foco(parserMundo);
    foco->switchFoco(0);
//    //InitCamaras();
    setMateriales();
}
void Mundo::onMotion(int x, int y) {
    this->alpha=this->alpha + (y - y0);
    beta=beta+ (x - x0);
    x0 = x; y0 = y;
    this->alpha=this->alpha + (y - y0);
    this->beta=beta + (x - x0);
    x0 = x; y0 = y;
    glutPostRedisplay();
}
void Mundo::onMouse(int button, int state, int x, int y)
{
    if( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN)) {
        x0 = x; y0 = y; //actualiza los valores de x,y
    }
    if( button == MOUSE_SCROLL_UP )
        zoomIn();
    if( button == MOUSE_SCROLL_DOWN )
        zoomOut();
}
void Mundo::zoomIn() {
    zoom++;
}
void Mundo::zoomOut() {
    if(zoom >= -10) zoom--;
}
void Mundo::iniciar(){
    modelos.resize(numModelos);

}
void Mundo::InitCamaras(){
    numCamaras = parserMundo->getNumCamaras();
    camara.resize(numCamaras);
    for (int i=0;i<numCamaras;i++){
        GLfloat datosCamara[9];
        GLfloat frustrum[4];
        parserMundo->getCamara(datosCamara, i);
        parserMundo->getFrustrum(frustrum, i);
        camara[i].setCamara(datosCamara);
        camara[i].setFrustrum(frustrum);
    }

}
void Mundo::encenderCam(){
    camaraSola->encenderCamara();
}

void Mundo::DrawGLScene() {
//    glClearColor(0.f, 0.f, 0.0f, 0.f);
//    glClearStencil(0);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

    //camara[camaraActiva].encenderCamara();

    glRotatef(alpha, 1.0f, 0.0f, 0.0f);
    glRotatef(beta, 0.0f, 1.0f, 0.0f);

    float scale_from_editor = 0.005 + double( (float)(zoom)/(float)3000);
    glScalef(scale_from_editor, scale_from_editor, scale_from_editor);


        incrementarTiempo();
        //dibujarEstrellas();
    for (int i =0; i<numModelos; i++){

        if(i == 1 && !lunas);
        else {

        glPushMatrix();

        GLfloat angulo_float = angulo*modelos[i].velocidad;
        GLfloat r = modelos[i].radioAstro;


        int aux = 6;
       r = r*aux;

        glRotatef(90, 10.0f, 0.0f, 0.0f); //Rotación de los astros sobre si mismos
        if(modelos[i].esLuna){

            if(lunas){
                int f = i;
                while (modelos[f].esLuna){
                    f--;
                    if(f <= 0){
                        cout << "El astro " << i << " no tiene astro sobre el que girar" << endl;
                        exit(1);
                    }
                }

                GLfloat angulo_float_anterior = angulo*modelos[f].velocidad;
                glRotatef(angulo_float_anterior, 0.0f, 0.0f, 10.0f);
                glTranslatef(modelos[f].radioGiro*aux,0,0);

                dibujarCirculo(modelos[i].radioGiro*aux);
                glRotatef(angulo_float, 0.0f, 0.0f, 10.0f);
                glTranslatef(modelos[i].radioGiro*aux,0,0);

                glScalef( r, r, r);
            }


        }
        else{
            dibujarCirculo(modelos[i].radioGiro*aux);
            glRotatef(angulo_float, 0.0f, 0.0f, 10.0f);
            glTranslatef(modelos[i].radioGiro*aux,0,0);
            glScalef( r, r, r);
        }
        GLfloat angulo_rotacion = angulo*modelos[i].velocidadRotacion;
        glRotatef(angulo_rotacion, 0.0f, 0.0f, 10.0f); //Rotación de los astros sobre si mismos
        modelos[i].setMaterial(materiales[i]);



        switch (look) {
        case WIRE:
            glDisable(GL_LIGHTING);
            modelos[i].dibujarWireSolid(look);
            break;
        case SOLID:
            glDisable(GL_LIGHTING);
            modelos[i].dibujarWireSolid(look);
            break;
        case FLAT:
            glEnable(GL_LIGHTING);
            modelos[i].dibujarFlat();
            break;
        case SMOOTH:
            glEnable(GL_LIGHTING);
            modelos[i].dibujarSmooth();
            break;

        }
        glPopMatrix();
        }
    }

    glFlush();
    //glutSwapBuffers();
}
void Mundo::dibujarEstrellas(){
    int numEstrellas = 20000;
    int posMax = 200000;
    if(!estrellas){
        estrellas = true;
        generarEstrellas(numEstrellas, posMax);
    }
    glColor3f(1,1,1);
    glDisable(GL_LIGHTING);
    glBegin(GL_POINTS);
    for (int f = 0; f < numEstrellas*3; f++){
        glVertex3f(vEstrellas[f], vEstrellas[f+1], vEstrellas[f+2]);
        f++;
        f++;
    }
    glEnd();
    glEnable(GL_LIGHTING);


}
void Mundo::generarEstrellas(int numEstrellas, int posMax){
    vEstrellas.resize(numEstrellas*3);
    int rangoMax,rangoMin,posicion,distancia;


    //rangoMax = sqrt((posMax*posMax)+(posMax*posMax)+(posMax*posMax));
    rangoMax = posMax;
    rangoMin = posMax-(posMax/10);


    for(int i = 0; i < numEstrellas*3; i++){

        bool creado = false;
        while (!creado){

            for (int n = 0; n < 3; n++){
                posicion = i + n;
                int random = rand()%posMax;
                vEstrellas[posicion] = random;
                if(rand()%2 == 0)vEstrellas[posicion] = -vEstrellas[posicion];
            }
            distancia = sqrt (
                        (vEstrellas[i]*vEstrellas[i])+
                        (vEstrellas[i+1]*vEstrellas[i+1])+
                        (vEstrellas[i+2]*vEstrellas[i+2])
                        );
            if (rangoMin < distancia && distancia < rangoMax){
                creado = true;
            }

        }
        //cout << "Rango minimo("<<rangoMin<< ") < Distancia("<< distancia <<") < Rango Maximo ("<< rangoMax<<")" << endl;
        i++;
        i++;
    }
}

void Mundo::dibujarCirculo(GLfloat radioCirculo){
    GLfloat calcx = 0;
    GLfloat calcy = 0;


    if(circulos){
        glColor3f(0.2,0.2,0.2);
        glDisable(GL_LIGHTING);
        glBegin(GL_POINTS);
        for (double i=0; i<10; i+=0.001){
            calcx=radioCirculo*cos(i);
            calcy=radioCirculo*sin(i);

            glVertex2f(calcx,calcy);
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }

}
void Mundo::switchCirculos(){
    if(!circulos) circulos = true;
    else  circulos = false;
}

void Mundo::setMateriales(){

    int numMateriales = parserMundo->getNumMateriales();
    materiales.resize(numMateriales);

    for (int i=0; i<numMateriales; i++){
        parserMundo->getMaterial(materiales[i].material_specular, i, "specular"); //NUEVO
        parserMundo->getMaterial(materiales[i].material_emission, i, "emision"); //NUEVO
        parserMundo->getMaterial(materiales[i].material_difuso, i, "difuso"); //NUEVO
        parserMundo->getMaterial(materiales[i].material_ambiente, i, "ambiente"); //NUEVO
    }
}

void Mundo::cambiarCamara(){
    camaraActiva=(camaraActiva+1)%numCamaras;
}
void Mundo::incrementarTiempo(){

    angulo = 30000+(glutGet(GLUT_ELAPSED_TIME)/20);

}

void Mundo::apagarFocos(){
            int numero = parserMundo->getNumFocos();
            for (int i=0; i<numero; i++){
               glDisable(GL_LIGHT0+i);
            }
}
