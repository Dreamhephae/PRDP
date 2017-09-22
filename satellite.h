#ifndef SATELLITE_H
#define SATELLITE_H

#include <gsl/gsl_matrix.h>
#include "datatypes.h"

struct Ephemeris
{
    //uint32_t t;           //观测历元
    float64 mean_anom;     //Toe时的平近点角(rad)
    float64 deltan;        //平均角速度校正值
    float64 eccentricity;  //卫星轨道偏心率
    float64 as_sq;         // 轨道长半轴的平方根(m^1/2)
    float64 right_ascen;   //Toe时的升交点赤经(rad)
    float64 orbital_inclination;  //Toe时的轨道倾角(rad)
    float64 perigee;       //轨道近地点角距(rad)
    float64 rra;           //升交点赤经变化率 (R/s)
    float64 inclination_rate; //卫星轨道倾角变化率(r/s)
    float64 cuc;           //升交点角距余弦调和校正振幅(rad)
    float64 cus;           //升交点角距正弦调和校正振幅(rad)
    float64 crc;           //轨道半经余弦调和校正振幅(m)
    float64 crs;           //轨道半经正弦调和校正振幅(m)
    float64 cic;           //轨道倾角余弦调和校正振幅(rad)
    float64 cis;           //轨道倾角余弦调和校正振幅(rad)

    uint32_t toe;         //参考历元(s)
};

class Satellite
{
public:
    uint8_t ID;          //卫星ID


    Satellite();
    ~Satellite();

    void refresh();  //更新卫星坐标
    Coord outputCoord();  //输出卫星坐标

private:
    /*float64 x;
    float64 y;
    float64 z;*/
    gsl_matrix * _satcoord;
    gsl_matrix * _coord;
    uint32_t t;     //观测历元，取得到测码伪距的时间？
    Ephemeris eph;  //星历
    //float64 pseudorange;  //伪距

    float64 n;  //平均运行角速度

    float64 delta_t;// 归化时间δt
    float64 M;//平近点角
    float64 E; //偏近点角
    float64 ro;//地心矢径
    float64 f; //真近点角
    float64 phi; //交点角距
    float64 delta_u;
    float64 delta_r;
    float64 delta_i;
    float64 phi_corrected; //摄动改正后的升交点角距
    float64 i;    //摄动改正后的轨道倾面角
    float64 r;    //摄动修正后的卫星矢径
    float64 lamda; //升交点经度

    gsl_matrix * coord_trans;    // 坐标变换矩阵 大小3*3

    float64 getE(const float64 M,const float64 e,const float64 epci); //计算偏近点角E

    //void refreshparam(); //更新轨道参数
};

#endif // SATELLITE_H
