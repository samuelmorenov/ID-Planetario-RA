#ifndef CAMARA_H
#define CAMARA_H

#include <iostream>
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

#include <stdio.h>

#include <vector>
#include <cstring>

class Camara
{
private:
    GLdouble eyeX;
    GLdouble eyeY;
    GLdouble eyeZ;
    GLdouble cenX;
    GLdouble cenY;
    GLdouble cenZ;
    GLdouble vp_X;
    GLdouble vp_Y;
    GLdouble vp_Z;

    GLdouble alfa;
    GLdouble aspect;
    GLdouble near;
    GLdouble far;
public:
    Camara();
    void setCamara(GLfloat * vector);
    void setFrustrum(GLfloat * vector);
    void encenderCamara();
};

#endif // CAMARA_H
