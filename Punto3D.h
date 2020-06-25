
#ifndef PUNTO3D_H_
#define PUNTO3D_H_

// -lGL -lGLU -lglut

class Punto3D {
private:

	float x;
	float y;
	float z;

public:
	Punto3D();
	Punto3D(int x, int y, int z);
	float getX() const;
	void setX(float x);
	float getY() const;
	void setY(float y);
	float getZ() const;
	void setZ(float z);

}


;



#endif /* PUNTO3D_H_ */
