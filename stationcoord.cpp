#include <cmath>
#include <gsl/gsl_linalg.h>

#include "datatypes.h"
#include "global.h"
#include "stationcoord.h"

uint64_t StationCoord::observe_public_set = 0;

StationCoord::StationCoord()
{
    G = gsl_matrix_alloc(4, 4);
    X = gsl_vector_alloc(4);
    AS = gsl_vector_alloc(4);
    P = gsl_vector_alloc(4);
    pe = gsl_permutation_alloc(4);
    temp_vec = gsl_vector_alloc(4);
}

//StationCoord::StationCoord(int n)
//{
//	snum = n;
//	G = gsl_matrix_alloc(snum, snum);
//	X = gsl_matrix_alloc(snum, 1);
//	A = gsl_matrix_alloc(snum, snum);
//	S = gsl_matrix_alloc(snum, 1);
//	P = gsl_matrix_alloc(snum, 1);
//}

StationCoord::~StationCoord()
{
    gsl_matrix_free(G);
    gsl_vector_free(X);
    gsl_vector_free(AS);
    gsl_vector_free(P);
    gsl_permutation_free(pe);
    gsl_vector_free(temp_vec);
}

bool StationCoord::getPos_onestep()
{
    gsl_vector_sub(AS, P);
    int sign = 0;
    gsl_linalg_LU_decomp(G, pe, &sign);
    gsl_vector_memcpy(temp_vec, X);
    gsl_linalg_LU_solve(G, pe, AS, X);

    gsl_vector_sub(temp_vec, X);

    _station_coord.x = gsl_vector_get(X, 0);
    _station_coord.y = gsl_vector_get(X, 1);
    _station_coord.z = gsl_vector_get(X, 2);

    if (pow(gsl_vector_get(temp_vec, 0), 2) + pow(gsl_vector_get(temp_vec, 1), 2) + pow(gsl_vector_get(temp_vec, 2), 2) < e)
        return true;
    else
        return false;
}

void StationCoord::getPos()
{
    const int max_ier = 6; //最大迭代次数为6

    for (int i = 0; i < max_ier; i++)
    {

        if (getPos_onestep())
            break;
        refreshParam();
    }

}

void StationCoord::refreshParam()
{
    Coord temp;
    double _se;
    gsl_matrix_set_all(G, 1);
    for (int i = 0; i < 4; i++)
    {
        temp = sate_coord[i] - _station_coord;
        temp = temp * (1/getNorm(temp));

        gsl_matrix_set(G, i, 0, temp.x);
        gsl_matrix_set(G, i, 1, temp.y);
        gsl_matrix_set(G, i, 2, temp.z);
    }

    for (int i = 0; i < 4; i++)
    {
        _se = temp*sate_coord[i];
        gsl_vector_set(AS, i, _se);
    }

}
