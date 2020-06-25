#include "Material.h"

Material::Material()
{

}
void Material::setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
        v[3] = v3;
}
