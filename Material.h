#ifndef MATERIAL_H
#define MATERIAL_H


#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

#include <stdio.h>

#include <vector>
#include <cstring>

class Material
{
public:
    Material();
    GLfloat material_difuso[4];
    GLfloat material_ambiente[4];
    GLfloat material_specular[4];
    GLfloat material_emission[4];
    void setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
};

#endif // MATERIAL_H
