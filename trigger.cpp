#include "trigger.h"

Trigger::Trigger()
{
    m_TriggerLevel=0;

    m_isSoftTrigger=true;
}


PlotDataStruct Trigger::EdgeTrigger(const PlotDataStruct& pv){
    //edge Trigger

    PlotDataStruct Output;

    int FirstPointOverLevel=-1;
    int NTriggerEdge=0;

    if(m_isSoftTrigger){
        for(int i=1;i<pv.Channel1.size();i++){
            if(pv.Channel1[i].y()>=m_TriggerLevel && pv.Channel1[i-1].y()<m_TriggerLevel){
                FirstPointOverLevel=i;
                //We trigger on the second raising edge!
                //This make the trigger more stable since we do not have a hardware trigger
                //and it is possible that datatakling started in the middle of a rasing edge and the top
                //This would make the whole spectrum shaky
                NTriggerEdge++;
                if(NTriggerEdge==2)break;
            }
        }
    }
    else{
        if(pv.Channel1.size()>1)FirstPointOverLevel=1;
    }

    if(FirstPointOverLevel==-1) return Output;

    //calculate slope between fist triggered point and the point before
    double m=(pv.Channel1[FirstPointOverLevel].y()-pv.Channel1[FirstPointOverLevel-1].y())/(pv.Channel1[FirstPointOverLevel].x()-pv.Channel1[FirstPointOverLevel-1].x());

    //calculate the offset to always get the same start pos of the triggered point (y-b)/m=x

    double X_Off=m_TriggerLevel/m;

    //The point P[FirstPointOverLevel-1] + X_Off has to be alsways at the same pos

    //courve should start at -200

    double TotalOff=0.-(pv.Channel1[FirstPointOverLevel-1].x()+X_Off);

    //Correct all points by this offset
    for(int i=FirstPointOverLevel;i<pv.Channel1.size();i++){
        //pv[i].setX(pv[i].x()+TotalOff);
        Output.Channel1<<QPointF(pv.Channel1[i].x()+TotalOff,pv.Channel1[i].y());
        Output.Channel2<<QPointF(pv.Channel2[i].x()+TotalOff,pv.Channel2[i].y());
    }

    return Output;
}
