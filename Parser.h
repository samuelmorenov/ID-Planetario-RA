#ifndef PARSER_H
#define PARSER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <map>

#include "util.h"
#include "xmlnode.h"
#include "xmlnodelist.h"
#include "xmlparser.h"

using namespace std;
class Parser
{
private:
    xmlnode * node;
    int getNum_recursivo(int num, xmlnode * nodoAux, string tipo);
    void getVector_recursivo(xmlnode * nodoAux, GLfloat *datos, int id, string tipo, string clase, int numParametros);
public:
    Parser(xmlnode * _node);
    int getNumMateriales();
    int getNumFocos();
    int getNumCamaras();
    int getNumModelos();
    void getMaterial(GLfloat *material, int id, string tipo);
    void getFoco(GLfloat *foco, int id, string tipo);
    void getCamara(GLfloat *camara, int id);
    void getFrustrum(GLfloat *frustrum, int id);
    void getModelo(GLfloat *modelo, int id);





};

#endif // PARSER_H
