#include <cmath>

#include "global.h"
#include "satellite.h"

static const float64 GM = 3986005e8; //地球引力常数
static const float omega_ie = 7.292115e-5;   //地球自转角速率(rad/s)

Satellite::Satellite()
{
    _satcoord = gsl_matrix_alloc(3, 1);
    _coord = gsl_matrix_alloc(3, 1);
    coord_trans = gsl_matrix_alloc(3, 3);
}

Satellite::~Satellite()
{
    gsl_matrix_free(_satcoord);
    gsl_matrix_free(_coord);
    gsl_matrix_free(coord_trans);
}

float64 Satellite::getE(const float64 M,const float64 e,const float64 epci)
{
    int max_iter = 30;

    float64 M_temp_cur;
    float64 M_temp_pref = M;
    float64 delta_M= 10;
    //float64 delta_E;

    float64 E = M;

    while (delta_M > epci && max_iter>=0)
    {
        M_temp_cur = E - e*sin(E);
        delta_M = M_temp_pref - M_temp_cur;
        E = E + (delta_M / (1 - e*cos(E)));
        M_temp_pref = M_temp_cur;

        max_iter--;
    }

    return E;
}

void Satellite::refresh()
{
    n = sqrt(GM / pow(pow(eph.as_sq,2), 3));
    delta_t = t-eph.toe;
    M = eph.mean_anom + n*delta_t;
    E = getE(M, eph.eccentricity, 0.001); //误差取0.001
    ro = pow(eph.as_sq, 2)*(1 - eph.eccentricity*cos(E));
    f = 2 * atan(sqrt((1+eph.eccentricity)/(1-eph.eccentricity))*tan(E/2));
    phi = eph.perigee + f;
    float64 cosphi = cos(2* phi);
    float64 sinphi = sin(2 * phi);
    delta_u = eph.cus*sinphi + eph.cuc*cosphi;
    delta_r = eph.crs*sinphi + eph.crc*cosphi;
    delta_i = eph.cis*sinphi + eph.cic*cosphi;

    phi_corrected = phi + delta_u;
    r = ro + delta_r;
    i = eph.orbital_inclination + delta_i + eph.inclination_rate*delta_t;

    lamda = eph.right_ascen + (eph.rra - omega_ie)*delta_t - omega_ie*eph.toe;


    /************************************************************************/

    float64 lamda_sin = sin(lamda);
    float64 lamda_cos = cos(lamda);
    float64 i_sin = sin(i);
    float64 i_cos = cos(i);

    gsl_matrix_set(_satcoord, 0, 0, r*cos(phi_corrected));
    gsl_matrix_set(_satcoord, 1, 0, r*sin(phi_corrected));
    gsl_matrix_set(_satcoord, 2, 0, r * 0);

    gsl_matrix_set(coord_trans, 0, 0, lamda_cos);
    gsl_matrix_set(coord_trans, 1, 0, lamda_sin);
    gsl_matrix_set(coord_trans, 2, 0, 0);
    gsl_matrix_set(coord_trans, 0, 1, -lamda_sin*i_cos);
    gsl_matrix_set(coord_trans, 1, 1, lamda_cos*i_cos);
    gsl_matrix_set(coord_trans, 2, 1, i_sin);
    gsl_matrix_set(coord_trans, 0, 2, lamda_sin*i_sin);
    gsl_matrix_set(coord_trans, 1, 2, -lamda_cos*i_sin);
    gsl_matrix_set(coord_trans, 2, 2, i_cos);

    gsl_matrix_mul(coord_trans, _satcoord, _coord);
}

Coord Satellite::outputCoord()
{
    Coord temp;
    temp.x = gsl_matrix_get(_coord, 0, 0);
    temp.y = gsl_matrix_get(_coord, 1, 0);
    temp.z = gsl_matrix_get(_coord, 2, 0);

    return temp;
}
