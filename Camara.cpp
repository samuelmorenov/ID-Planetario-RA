#include "Camara.h"
#include <GL/freeglut_ext.h>
Camara::Camara(){

}
void Camara::setCamara(GLfloat *vector){
    eyeX=vector[0];
    eyeY=vector[1];
    eyeZ=vector[2];
    cenX=vector[3];
    cenY=vector[4];
    cenZ=vector[5];
    vp_X=vector[6];
    vp_Y=vector[7];
    vp_Z=vector[8];
}
void Camara::setFrustrum(GLfloat *vector){
    alfa = vector[0];
    aspect = vector[1];
    near = vector[2];
    far= vector[3];
}
void Camara::encenderCamara(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Apilamos la vista
    gluPerspective(alfa, aspect, near, far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Apilamos la vista
    gluLookAt(eyeX, eyeY, eyeZ, cenX, cenY, cenZ, vp_X, vp_Y, vp_Z);
}

