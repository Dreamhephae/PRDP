#ifndef STATIONCOORD_H
#define STATIONCOORD_H


#include <gsl/gsl_permutation.h>

struct Map_station2satellite
{
    uint8_t ID; //卫星ID
    uint32_t pseudorange; //卫星至参考站的伪距
};

//class Satellite;
class StationCoord
{
public:

    //StationCoord(int n); //n为基准站与移动站所能共同检测的卫星颗数，n>4时使用
    StationCoord(); //默认构造函数，取共同检测到的卫星颗数为4
    ~StationCoord();

    void getData();
    void refreshParam();    //更新参数矩阵
    void getPos();          //计算接收机位置
    uint64_t outputObserve(){ return observe_set; }     //输出观测卫星列表
    static void getPublicSet(uint64_t a, uint64_t b){ observe_public_set = a & b; }    //计算参考站与移动站所能共同观测到的卫星集合
private:

    gsl_matrix * G;   //几何矩阵1
    gsl_vector * X;	  //用户状态向量
    gsl_vector * AS;	  //几何矩阵2与卫星状态矩阵的积
    gsl_vector * P;   //测量伪矩阵
    gsl_permutation * pe;
    gsl_vector * temp_vec;

    Coord _station_coord; //观测站坐标
    int snum;  //探测到的卫星颗数
    const double e = 0.1;  //收敛阈值

    //list<Satellite *> observelist;  //观察到的卫星列表
    //std::list<int> observelist;   //观察到的卫星列表
    //static std::list<Map_station2satellite> observe_public;//能观测到的公共卫星列表，需要保证listsize大于4

    /*******************************************************************************************
    observe_set用于记录观测到的卫星ID，GPS共64颗卫星，从低位到高位依次表示每颗卫星是否被被观测到，对应位置0
    表示未被观测到，置1表示观测到该卫星。操作时注意计算机是Big_Endian还是Little_Endian
    *******************************************************************************************/
    uint64_t observe_set = 0;

    static uint64_t observe_public_set;//用于记录基准站，参考站所能公共观测到的卫星列表，用法同observe_set
    bool getPos_onestep();  //进行一次迭代计算,用户状态矩阵变化小于一定值时，返回true
};


#endif // STATIONCOORD_H
