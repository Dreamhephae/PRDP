#ifndef GLOBAL_H
#define GLOBAL_H

#include <gsl/gsl_matrix.h>
#include "datatypes.h"

struct Coord
{
    float64 x;
    float64 y;
    float64 z;

    inline Coord operator = (const Coord & a)
    {
        this->x = a.x;
        this->y = a.y;
        this->z = a.z;
        return *this;
    }

    inline Coord operator - (const Coord & a)
    {

        this->x = this->x - a.x;
        this->y = this->y - a.y;
        this->z = this->z - a.z;

        return *this;
    }

    inline Coord operator * (const float64 d)           //点乘
    {
        this->x = this->x * d;
        this->y = this->y * d;
        this->z = this->z * d;
        return *this;
    }

    inline float64 operator * (const Coord & a)
    {
        return (this->x*a.x + this->y*a.y + this->z*a.z);
    }
};

extern Coord sate_coord[4];

extern float64 getNorm(const Coord & src);  //计算src的模

extern void gsl_matrix_mul(gsl_matrix * a, gsl_matrix * b, gsl_matrix * c); //矩阵乘运算 c=ab
extern void GetInverse(gsl_matrix * A, gsl_matrix * inverse);  //矩阵求逆

#endif // GLOBAL_H
