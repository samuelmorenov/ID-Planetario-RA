#include "Punto3D.h"

float Punto3D::getX() const {
	return x;
}

void Punto3D::setX(float x) {
	this->x = x;
}

float Punto3D::getY() const {
	return y;
}

void Punto3D::setY(float y) {
	this->y = y;
}

float Punto3D::getZ() const {
	return z;
}

Punto3D::Punto3D(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Punto3D::Punto3D() {
}

void Punto3D::setZ(float z) {
	this->z = z;
}
