/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#ifndef SCOPEDISPLAY_H
#define SCOPEDISPLAY_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QString>
#include "DataStructure.h"

class ScopeDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit ScopeDisplay(QWidget *parent = 0);

     QPointF TransformIntoWidgetCoordinate(const QPointF &p);

     void setData(const PlotDataStruct &vP, double SampleRate=0.);

     void setTriggerLevel(const double tl);
     double getTriggerLevel(){return m_TriggerLineY; }
    // void setTimeStep(const double &TimeStep){ m_TimeStep=TimeStep;}
     void setTimeBase(const double &TimeBase){ m_TimeBase=TimeBase; update();}

     void setSoftTrigger(bool isSoftTrigger=true){m_isSoftTrigger=isSoftTrigger; update();}

     void set2Channel(bool b){m_Channel2=b;update();}

     //Set the Value of the User function This function should be called before the
     // update is called for the actual sample
     void setF1Value(UsrFunctionStruct v){F1Value=v;}
     void setF2Value(UsrFunctionStruct v){F2Value=v;}
     void setF3Value(UsrFunctionStruct v){F3Value=v;}
     void setF4Value(UsrFunctionStruct v){F4Value=v;}
     void setF5Value(UsrFunctionStruct v){F5Value=v;}
     void setF6Value(UsrFunctionStruct v){F6Value=v;}


     PlotDataStruct getDataPoints(){return m_dataPoints;}

    
signals:
    
public slots:
     void slot_setOffsetX(int Offset){m_XOffset=Offset; update();}
     void slot_setOffsetY(int Offset){m_YOffset=Offset; update();}
     void slot_setOffsetY2(int Offset){m_YOffset2=Offset; update();}
     void slot_setScaleX(int Scale){m_TimeBase=Scale; update();}
     void slot_setScaleY(int Scale){m_YScale=(double)Scale/10.; update();}
     void slot_setScaleY2(int Scale){m_YScale2=(double)Scale/10.; update();}

     void slot_showF1(bool b){F1_On=b; update();}
     void slot_showF2(bool b){F2_On=b; update();}
     void slot_showF3(bool b){F3_On=b; update();}
     void slot_showF4(bool b){F4_On=b; update();}
     void slot_showF5(bool b){F5_On=b; update();}
     void slot_showF6(bool b){F6_On=b; update();}



protected:
    void paintEvent(QPaintEvent *event);

private:
    double m_XOffset;
    double m_YOffset;
    double m_YOffset2;



    double m_XOrgin;
    double m_YOrgin;

    double m_XMax;
    double m_XMin;
    double m_YMax;
    double m_YMin;

    int BorderOffset;
    int FrameSize;

    double m_TriggerLineY;
    //double m_TimeStep;//DeltaT between the points in us
    double m_TimeBase;//Horizontal distance between each line in us
    double m_YScale;
    double m_YScale2;

    PlotDataStruct m_dataPoints;
    double m_SampleRate;

    bool m_isSoftTrigger;

    bool m_Channel2;

    //values of the user functions
    UsrFunctionStruct F1Value;
    UsrFunctionStruct F2Value;
    UsrFunctionStruct F3Value;
    UsrFunctionStruct F4Value;
    UsrFunctionStruct F5Value;
    UsrFunctionStruct F6Value;

    //show the funcion values on the screen
    bool F1_On;
    bool F2_On;
    bool F3_On;
    bool F4_On;
    bool F5_On;
    bool F6_On;

    
};

#endif // SCOPEDISPLAY_H
