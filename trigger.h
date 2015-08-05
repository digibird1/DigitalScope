#ifndef TRIGGER_H
#define TRIGGER_H

#include <iostream>
#include <cmath>
#include <QtCore>
#include "DataStructure.h"

class Trigger
{
public:
    Trigger();

    void setTriggerLevel(const double& tl){m_TriggerLevel=tl;}
    PlotDataStruct EdgeTrigger(const PlotDataStruct& pv);
    void setSoftTrigger(bool isSoftTrig=true){m_isSoftTrigger=isSoftTrig;}

private:
    double m_TriggerLevel;

    bool m_isSoftTrigger;



};

#endif // TRIGGER_H
