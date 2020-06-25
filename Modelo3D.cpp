#include "Modelo3D.h"
#include <math.h>
#include <GL/freeglut_ext.h>

using namespace std;

Modelo3D::Modelo3D() {
	NFaces = 0;
	NVertex = 0;

}
int Modelo3D::getCaras() {
	return NFaces;
}
int Modelo3D::getVertices() {
	return NVertex;
}
void Modelo3D::setCaras(int NFaces) {
	this->NFaces = NFaces;
}
void Modelo3D::setVertices(int NVertex) {
	this->NVertex = NVertex;
}


// Model Loader from file in ASC format
bool Modelo3D::Load_Model(char *nombre) {

	FILE *fich;
	int NVertex, NFaces, VertexNumber, FaceNumber, N, A, B, C;
	float X, Y, Z, ax, ay, az, bx, by, bz, len;
	TNormal Normal;

	char cad1[20], cad2[20], cad3[20], cad4[20],cad5[20];
	char cadena[100]; // Lo suf. larga para leer una línea

	if ((fich = fopen(nombre, "r")) == NULL) // open for reading  // open for reading
	{
		cout << " Error en la apertura. Es posible que el fichero no exista \n "
				<< endl;
		exit(1);
	}
    //cout << "Opened File....." << endl;
	while (fgets(cadena, 100, fich) != NULL) {
		if (strncmp(cadena, "Named", 5) == 0) // Nvertex and NFaces in file
		{
			fscanf(fich, "%[Tri-mesh A-Za-z:-,: ]%d%[ ]%[Faces]:%d\n", cad1,
					&NVertex, cad2, cad3, &NFaces);
			this->setCaras(NFaces);
			this->setVertices(NVertex);
		}
		ListaCaras.resize(getCaras());
		ListaPuntos3D.resize(getVertices());
		if (strncmp(cadena, "Vertex list:", 12) == 0) // Vertex List in file
			for (N = 1; N <= NVertex; N++) {
				fscanf(fich, "%[A-Za-z ]%d: %[X:] %f %[Y:] %f %[Z:] %f    \n",
						cad1, &VertexNumber, cad2, &X, cad3, &Y, cad4, &Z);
				ListaPuntos3D[VertexNumber].setX(X);
				ListaPuntos3D[VertexNumber].setY(Y);
				ListaPuntos3D[VertexNumber].setZ(Z);
			}
		if (strncmp(cadena, "Face list:", 10) == 0) { // Face List in model file

			for (N = 0; N < NFaces; N++) {
				fgets(cadena, 100, fich);
				if (strncmp(cadena, "Face", 4) == 0) {
					sscanf(cadena,
							"%[Face]%d: %[A:]%d %[B:]%d %[C:]%d %[^\n]%*c",cad1, &FaceNumber, cad2, &A, cad3, &B, cad4, &C,cad5);
					// Cálculo del vector normal a cada cara (Nx,Ny,Nz)........NEW¡¡¡¡
					ListaCaras[FaceNumber] = Cara(A, B, C, Normal);
					ax =
							ListaPuntos3D[ListaCaras[FaceNumber].getA()].getX()
									- ListaPuntos3D[ListaCaras[FaceNumber].getB()].getX(); //  X[A] - X[B];
					ay =
							ListaPuntos3D[ListaCaras[FaceNumber].getA()].getY()
									- ListaPuntos3D[ListaCaras[FaceNumber].getB()].getY(); //  Y[A] - Y[B];
					az =
							ListaPuntos3D[ListaCaras[FaceNumber].getA()].getZ()
									- ListaPuntos3D[ListaCaras[FaceNumber].getB()].getZ(); //  Z[A] - Z[B];
					bx =
							ListaPuntos3D[ListaCaras[FaceNumber].getB()].getX()
									- ListaPuntos3D[ListaCaras[FaceNumber].getC()].getX(); //  X[B] - X[C];
					by =
							ListaPuntos3D[ListaCaras[FaceNumber].getB()].getY()
									- ListaPuntos3D[ListaCaras[FaceNumber].getC()].getY(); //  Y[B] - Y[C];
					bz =
							ListaPuntos3D[ListaCaras[FaceNumber].getB()].getZ()
									- ListaPuntos3D[ListaCaras[FaceNumber].getC()].getZ(); //  Z[B] - Z[C];
					Normal.x = (ay * bz) - (az * by);
					Normal.y = (az * bx) - (ax * bz);
					Normal.z = (ax * by) - (ay * bx);
					len = sqrt(
							(Normal.x * Normal.x) + (Normal.y * Normal.y)
									+ (Normal.z * Normal.z));
					Normal.x = Normal.x / len;
					Normal.y = Normal.y / len;
					Normal.z = Normal.z / len;
					//cout<<"Normalx: "<<Normal.x<<"   Normaly: "<<Normal.y<<"   Normalz: "<<Normal.z<<endl;
					ListaCaras[FaceNumber] = Cara(A, B, C, Normal);

				} else {
					N--;
				}

			}
			}
	}
	fclose(fich);

}

void Modelo3D::dibujarFlat(){
    glShadeModel(GL_FLAT);
    for (int i = 0; i < getCaras(); i++) {
        glBegin(GL_POLYGON);
        glNormal3f(
            ListaCaras[i].getNormal().x,
            ListaCaras[i].getNormal().y,
            ListaCaras[i].getNormal().z
        );
        glVertex3f(
            ListaPuntos3D[ListaCaras[i].getA()].getX(),
            ListaPuntos3D[ListaCaras[i].getA()].getY(),
            ListaPuntos3D[ListaCaras[i].getA()].getZ());
        glVertex3f(
            ListaPuntos3D[ListaCaras[i].getB()].getX(),
            ListaPuntos3D[ListaCaras[i].getB()].getY(),
            ListaPuntos3D[ListaCaras[i].getB()].getZ());
        glVertex3f(
            ListaPuntos3D[ListaCaras[i].getC()].getX(),
            ListaPuntos3D[ListaCaras[i].getC()].getY(),
            ListaPuntos3D[ListaCaras[i].getC()].getZ());

        glEnd();
    }
}
void Modelo3D::dibujarSmooth(){
    glShadeModel(GL_SMOOTH);
    for (int i = 0; i < getCaras(); i++) {
        glBegin(GL_POLYGON);
        glNormal3f(
           ListaPuntos3D[ListaCaras[i].getA()].getX(),
           ListaPuntos3D[ListaCaras[i].getA()].getY(),
           ListaPuntos3D[ListaCaras[i].getA()].getZ());
        glVertex3f(
           ListaPuntos3D[ListaCaras[i].getA()].getX(),
           ListaPuntos3D[ListaCaras[i].getA()].getY(),
           ListaPuntos3D[ListaCaras[i].getA()].getZ());
        glNormal3f(
           ListaPuntos3D[ListaCaras[i].getB()].getX(),
           ListaPuntos3D[ListaCaras[i].getB()].getY(),
           ListaPuntos3D[ListaCaras[i].getB()].getZ());
        glVertex3f(
           ListaPuntos3D[ListaCaras[i].getB()].getX(),
           ListaPuntos3D[ListaCaras[i].getB()].getY(),
           ListaPuntos3D[ListaCaras[i].getB()].getZ());
        glNormal3f(
           ListaPuntos3D[ListaCaras[i].getC()].getX(),
           ListaPuntos3D[ListaCaras[i].getC()].getY(),
           ListaPuntos3D[ListaCaras[i].getC()].getZ());
        glVertex3f(
           ListaPuntos3D[ListaCaras[i].getC()].getX(),
           ListaPuntos3D[ListaCaras[i].getC()].getY(),
           ListaPuntos3D[ListaCaras[i].getC()].getZ());
        glEnd();
    }
}

void Modelo3D::dibujarWireSolid(look_type look){
    for (int i = 0; i < getCaras(); i++) {
        glShadeModel(GL_SMOOTH);
        glBegin(look);
        glColor3f(1.0,1.0,0.0);
        glVertex3f(
            ListaPuntos3D[ListaCaras[i].getA()].getX(),
            ListaPuntos3D[ListaCaras[i].getA()].getY(),
            ListaPuntos3D[ListaCaras[i].getA()].getZ());
        glColor3f(1.0,0.5,0.0);
        glVertex3f(
            ListaPuntos3D[ListaCaras[i].getB()].getX(),
            ListaPuntos3D[ListaCaras[i].getB()].getY(),
            ListaPuntos3D[ListaCaras[i].getB()].getZ());

        glColor3f(1.0,1.0,0.0);
        glVertex3f(
            ListaPuntos3D[ListaCaras[i].getC()].getX(),
            ListaPuntos3D[ListaCaras[i].getC()].getY(),
            ListaPuntos3D[ListaCaras[i].getC()].getZ());
        glColor3f(1.0,0.5,0.0);
        glVertex3f(
            ListaPuntos3D[ListaCaras[i].getA()].getX(),
            ListaPuntos3D[ListaCaras[i].getA()].getY(),
            ListaPuntos3D[ListaCaras[i].getA()].getZ());

        glEnd();
    }
}
void Modelo3D::setMaterial(Material mat){

    GLfloat brillo = 10;

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat.material_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat.material_emission);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.material_difuso);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat.material_ambiente);
    glMaterialf(GL_FRONT, GL_SHININESS, brillo);

}

void Modelo3D::setValores(int id, Parser *p){

    GLfloat datos[5];
    p->getModelo(datos, id);


        radioGiro = datos[0];
        radioAstro = datos[1];
        velocidad = datos[2];
        if(datos[3] == 0) esLuna =false;
        else esLuna = true;
        velocidadRotacion = datos[4];

}

