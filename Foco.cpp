#include "Foco.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


using namespace std;

Foco::Foco(Parser *parserFoco){
    int numero = parserFoco->getNumFocos();
    for (int i=0; i<numero; i++){
        this->ID=i;
        parserFoco->getFoco(this->luzdifusa, i, "luzdifusa");
        parserFoco->getFoco(this->luzambiente, i, "luzambiente");
        parserFoco->getFoco(this->luzspecular, i, "luzspecular");
        parserFoco->getFoco(this->posicion0, i, "posicion");

        glLightfv(GL_LIGHT0+ID, GL_DIFFUSE, this->luzdifusa);
        glLightfv(GL_LIGHT0+ID, GL_AMBIENT, this->luzambiente);
        glLightfv(GL_LIGHT0+ID, GL_SPECULAR, this->luzspecular);
        glLightfv(GL_LIGHT0+ID, GL_POSITION, this->posicion0);
    }

}

void Foco::switchFoco(int id){
    if(glIsEnabled(GL_LIGHT0+id)) {
        glDisable(GL_LIGHT0+id);
    }
    else glEnable(GL_LIGHT0+id);

}
