/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QByteArray>
#include <iostream>
#include <cstring>
#include <QVector>
#include <QPointF>
#include <QString>

typedef unsigned short    uint16_t;
typedef unsigned int      uint32_t;


const int DataPointsArduino=1600;
const int DataPointsPi=1600;
const int DataPoints_=10000;



struct DataStructArduino {//This is the structure we get from the Arduino
    uint32_t Time;
    //uint16_t values[DataPoints];
    char values[DataPointsArduino];
};

struct DataStructPi {//This is the structure we get from the Raspberry Pi
    uint32_t Time;
    //uint16_t values[DataPoints];
    char values[DataPointsPi];
    char values2[DataPointsPi];
};


struct DataStruct {//This is the general structure we in the gui
    uint32_t Time;
    //uint16_t values[DataPoints];
    char values[DataPoints_];
    char values2[DataPoints_];
    int nPoints;
};


struct PlotDataStruct{//This is the data structure passed to the plotting widget
    QVector<QPointF> Channel1;
    QVector<QPointF> Channel2;

};

struct UsrFunctionStruct{
    QString FunctionName="";
    double ReturnValue=0;
    QString Unit="";
};


DataStruct convertByteArrayToStruct(const QByteArray& a, std::string Source);
/*
DataStruct convertByteArrayToStruct(const QByteArray& a, std::string Source){//Sources are Arduino, Pi

    DataStruct data;



    if(Source=="Arduino"){
        DataStructArduino DataA;
        if(a.size()!=sizeof(DataA)) return data;
        char *structurePointer=(char *)&DataA;
        for(int i=0;i<sizeof(DataA);i++){
            structurePointer[i]=a[i];
        }

        //Convert into general data structure
        for(int i=0;i<DataPointsArduino;i++){
            data.values[i]=DataA.values[i];
        }
        data.Time=DataA.Time;
        data.nPoints=DataPointsArduino;


    }
    else if(Source=="Pi"){
        DataStructPi DataP;
        if(a.size()!=sizeof(DataP)) return data;
        char *structurePointer=(char *)&DataP;
        for(int i=0;i<sizeof(DataP);i++){
            structurePointer[i]=a[i];
        }

        //Convert into general data structure
        for(int i=0;i<DataPointsPi;i++){
            data.values[i]=DataP.values[i];
            data.values2[i]=DataP.values2[i];
        }
        data.Time=DataP.Time;
        data.nPoints=DataPointsPi;
    }
    else{
        std::cerr<<"There was an error in the data structure"<<std::endl;
        return data;
    }



    return data;
}
*/




#endif // DATASTRUCTURE_H
