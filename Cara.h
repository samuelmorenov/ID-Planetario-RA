
#ifndef CARA_H_
#define CARA_H_

struct TNormal {
		 float x;
		 float y;
		 float z;

} ;

class Cara {
		int a;
		int b;
		int c;
		TNormal normal;
public:
		Cara();
                 ~ Cara( ); 
		Cara(int a, int b, int c, TNormal Normal);
                
		int getA() ;
		void setA(int a);
		int getB() ;
		void setB(int b);
		int getC() ;
		void setC(int c);
                
		TNormal getNormal() ;
		void setNormal(TNormal normal);
};

#endif /* CARA_H_ */
