#include "Cara.h"

Cara::Cara() {
    setA(a);
    setB(b);
    setC(c);
}

Cara::~ Cara( ) { /* Nada que hacer */}


int Cara::getA()  {
	return a;
}

void Cara::setA(int a) {
	this->a = a;
}

int Cara::getB()  {
	return b;
}

void Cara::setB(int b) {
	this->b = b;
}

int Cara::getC()  {
	return c;
}

void Cara::setC(int c) {
	this->c = c;
}

TNormal Cara::getNormal()  {
	return normal;
}


Cara::Cara(int a, int b, int c, TNormal Normal) {
    setA(a);
    setB(b);
    setC(c);
    setNormal(Normal);
}
  
void Cara::setNormal(TNormal normal) {
	this->normal = normal;
}
