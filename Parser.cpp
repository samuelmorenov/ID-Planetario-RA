#include "Parser.h"

Parser::Parser(xmlnode * _node)
{
    node = _node;
}


int Parser::getNum_recursivo(int num, xmlnode * nodoAux, string tipo){

    map<string,string>::iterator it;
    map<string,string> params;


    if(nodoAux->getNodeName()==tipo){   //Vemos si el nodo es de tipo material
        params= nodoAux->getNodeParamMap();    //Obtenemos los parametros
        it=params.begin();                  //inicializamos el iterador en el primer parametro


        string id_string = it->second;
        int id_int = atoi(id_string.c_str());

        if(id_int == num){    //Si el identificador del material es el que bucamos hacemos:
           num++;
           //cout << "num++  = " << num << endl;
        }
        else{
            cout << "El identificador del " << tipo << " en el xml no coincide con su numero de orden." << endl;
            cout << "Error encontrado en el numero: " << num << ", con identificador: " << id_int << endl;
            exit(1);
        }
    }
    else{
        for(int i=0;i<nodoAux->getChildCount();i++){
            num = getNum_recursivo(num, nodoAux->getChild(i), tipo);
        }
    }
   return num;

}


void Parser::getVector_recursivo(xmlnode * nodoAux, GLfloat *datos, int id, string tipo, string clase, int numParametros){
    map<string,string>::iterator it;
    map<string,string> params;


    if(nodoAux->getNodeName()==clase){   //Vemos si el nodo es de tipo material
        params= nodoAux->getNodeParamMap();    //Obtenemos los parametros
        it=params.begin();                  //inicializamos el iterador en el primer parametro


        string id_string = it->second;
        int id_int = atoi(id_string.c_str());

        if(id_int == id){    //Si el identificador del material es el que bucamos hacemos:
            for(int f=0;f<nodoAux->getChildCount();f++){   //recorremos todos los tipos de materiales
                if(nodoAux->getChild(f)->getNodeName() == tipo){         //si el material es el que buscamos
                    int numeroParametros = nodoAux->getChild(f)->getChildCount();
                    if (numeroParametros != numParametros){
                        cout << "Numero de parametros es distinto de "<< numParametros<<" en el " << tipo << " de "<< clase << " " << id << endl;
                        exit(1);
                    }
                    for(int parametro=0;parametro<numParametros;parametro++){

                        string valor_string = nodoAux->getChild(f)->getChild(parametro)->getNodeText(); //obtenemos el valor
                        float valor_float = atof(valor_string.c_str());
                        GLfloat valor_GLfloat = valor_float;
                        datos[parametro] = valor_GLfloat;

                    }
                }
            }
        }
    }
    else{
        for(int i=0;i<nodoAux->getChildCount();i++) getVector_recursivo(nodoAux->getChild(i), datos, id, tipo, clase, numParametros);

    }

}




int Parser::getNumMateriales(){
    int num = 0;
    num = getNum_recursivo(num, node, "Material");
    return num;

}
int Parser::getNumFocos(){
    int num = 0;
    num = getNum_recursivo(num, node, "Foco");
    //if(num > 8) num = 8;
    return num;
}

int Parser::getNumCamaras(){
    int num = 0;
    num = getNum_recursivo(num, node, "Camara");
    return num;
}
int Parser::getNumModelos(){
    int num = 0;
    num = getNum_recursivo(num, node, "Modelo");
    return num;
}

void Parser::getMaterial(GLfloat *material, int id, string tipo){
    getVector_recursivo(node, material, id, tipo, "Material", 4);
}
void Parser::getFoco(GLfloat *foco, int id, string tipo){
    getVector_recursivo(node, foco, id, tipo, "Foco", 4);
}
void Parser::getCamara(GLfloat *camara, int id){
    getVector_recursivo(node, camara, id, "DatosCamara", "Camara", 9);
}
void Parser::getFrustrum(GLfloat *frustrum, int id){
    getVector_recursivo(node, frustrum, id, "Frustrum", "Camara", 4);
}
void Parser::getModelo(GLfloat *modelo, int id){
    getVector_recursivo(node, modelo, id, "Datos", "Modelo", 5);
}







