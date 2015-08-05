/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#include "DataStructure.h"

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
