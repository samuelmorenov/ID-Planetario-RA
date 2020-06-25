#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include "Parser.h"
#include "util.h"
#include "xmlnode.h"
#include "xmlnodelist.h"
#include "xmlparser.h"
class Foco
{
private:
int ID;
GLfloat luzdifusa[4];
GLfloat luzambiente[4];
GLfloat luzspecular[4];
GLfloat posicion0[4];

public:
    Foco(Parser *parserFoco);
    void switchFoco(int id);
    void apagarFocos();
};
