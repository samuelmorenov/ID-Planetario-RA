
#ifndef MODELO3D_H_
#define MODELO3D_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstring>
#include "Cara.h"
#include "Camara.h"
#include "Punto3D.h"
#include "Material.h"
#include "Parser.h"

using namespace std;
enum look_type { WIRE = GL_LINES, SOLID = GL_POLYGON, FLAT = GL_FLAT, SMOOTH = GL_SMOOTH};
class Modelo3D {
private:
	vector<Cara> ListaCaras;
	vector<Punto3D> ListaPuntos3D;
	int NFaces, NVertex;


public:
    float radioGiro;
    float radioAstro;
    float velocidad;
    bool  esLuna;
    float velocidadRotacion;

	Modelo3D();
	int getCaras();
	int getVertices();

	void setCaras(int NFaces);
	void setVertices(int NVertex);
	bool Load_Model(char *nombre);
    void DrawGLScene(float alpha,float beta, int zoom, Camara *camara);

    void dibujarFlat();
    void dibujarSmooth();
    void dibujarWireSolid(look_type look);

    void setMaterial(Material mat);
    void setValores(int id, Parser *p);
};


#endif /* MODELO3D_H_ */
