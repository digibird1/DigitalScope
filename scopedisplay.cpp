/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#include "scopedisplay.h"
#include <iostream>

ScopeDisplay::ScopeDisplay(QWidget *parent) :
    QWidget(parent)
{

    m_isSoftTrigger=true;
    m_Channel2=false;

    m_XOffset=0;
    m_YOffset=0;

    BorderOffset = 50;
    FrameSize=600;

    m_XMax=512;
    m_YMax=256;
    m_XMin=-512;
    m_YMin=-256;

    m_XOrgin=FrameSize/2;
    m_YOrgin=FrameSize/2;

    m_TriggerLineY=90;
    m_YScale=1.;

    setMinimumSize(700,700);
    setFixedSize(700,700);


    m_TimeBase=10000;//um

    m_SampleRate=0;

    //Initialize the user functions
    F1Value=-9999999999899;//0;
    F2Value=-99999999999;//0;
    F3Value=-99999999999;//0;
    F4Value=-99999999999;//0;
    F5Value=-99999999999;//0;
    F6Value=-99999999999;//0;

    F1_On=false;
    F2_On=false;
    F3_On=false;
    F4_On=false;
    F5_On=false;
    F6_On=false;

}



void ScopeDisplay::paintEvent(QPaintEvent *event){
    QPainter painter(this);





    int GridSize=50;

    painter.setPen(QPen(Qt::green,2));//fixme will be removed
    painter.drawRect(BorderOffset,BorderOffset,FrameSize,FrameSize);
    painter.setPen(QPen(Qt::green,1));//fixme will be removed
    for(int i=1;i<=FrameSize/GridSize-1;i++){
        painter.drawLine(BorderOffset,BorderOffset+i*GridSize,BorderOffset+FrameSize,BorderOffset+i*GridSize);//Horizontal Line
        painter.drawLine(BorderOffset+i*GridSize,BorderOffset,BorderOffset+i*GridSize,BorderOffset+FrameSize);//Vertical Line
    }
    //Orgin Line
    painter.setPen(QPen(Qt::black,2));
    painter.drawLine(BorderOffset,m_YOrgin+BorderOffset,BorderOffset+FrameSize,m_YOrgin+BorderOffset);//Horizontal Line
    painter.drawLine(m_XOrgin+BorderOffset,BorderOffset,m_XOrgin+BorderOffset,BorderOffset+FrameSize);//Vertical Line


    //trigger line
    if(m_isSoftTrigger){
        painter.setPen(QPen(Qt::blue,2));
        painter.drawLine(TransformIntoWidgetCoordinate(QPointF(-m_XOrgin,m_TriggerLineY)),TransformIntoWidgetCoordinate(QPointF(m_XOrgin,m_TriggerLineY)));//Horizontal Line
        QString text;
        text.setNum(m_TriggerLineY);
        painter.drawText(TransformIntoWidgetCoordinate(QPointF(-m_XOrgin,m_TriggerLineY)),text);
    }

    //print Function

    QVector<QPointF> PolyLine;
    //PolyLine<<TransformIntoWidgetCoordinate(QPointF(0,0));
    //PolyLine<<TransformIntoWidgetCoordinate(QPointF(200,200));

    for(int i=0;i<m_dataPoints.Channel1.size();i++){

        QPointF Point=m_dataPoints.Channel1[i];
        //convert the points to the time base
        //m_dataPoints[i].setX(m_dataPoints[i].x()*(GridSize/m_TimeBase));

        //Apply Scale
        Point.setX(Point.x()*(GridSize/m_TimeBase));
        Point.setY(Point.y()*(m_YScale));

        Point=TransformIntoWidgetCoordinate(Point);

        //Apply the offset
        Point.setX(Point.x()+m_XOffset);
        Point.setY(Point.y()-m_YOffset);

        //remove points which are outside the frame
        if(Point.x()>BorderOffset+FrameSize || Point.x()<BorderOffset)
            continue;
        if(Point.y()>BorderOffset+FrameSize)Point.setY(BorderOffset+FrameSize);
        if(Point.y()<BorderOffset )Point.setY(BorderOffset);


        //put point
        PolyLine<<Point;
    }

    painter.setPen(QPen(Qt::red,1,Qt::SolidLine));
    painter.drawPolyline(PolyLine);




    //Channel 2
    if(m_Channel2){
        QVector<QPointF> PolyLine2;
        //PolyLine<<TransformIntoWidgetCoordinate(QPointF(0,0));
        //PolyLine<<TransformIntoWidgetCoordinate(QPointF(200,200));

        for(int i=0;i<m_dataPoints.Channel2.size();i++){

            QPointF Point2=m_dataPoints.Channel2[i];
            //convert the points to the time base
            //m_dataPoints[i].setX(m_dataPoints[i].x()*(GridSize/m_TimeBase));

            //Apply Scale
            Point2.setX(Point2.x()*(GridSize/m_TimeBase));
            Point2.setY(Point2.y()*(m_YScale2));

            Point2=TransformIntoWidgetCoordinate(Point2);

            //Apply the offset
            Point2.setX(Point2.x()+m_XOffset);
            Point2.setY(Point2.y()-m_YOffset2);

            //remove points which are outside the frame
            if(Point2.x()>BorderOffset+FrameSize || Point2.x()<BorderOffset)
                continue;
            if(Point2.y()>BorderOffset+FrameSize)Point2.setY(BorderOffset+FrameSize);
            if(Point2.y()<BorderOffset )Point2.setY(BorderOffset);


            //put point
            PolyLine2<<Point2;
        }

        painter.setPen(QPen(Qt::magenta,1,Qt::SolidLine));
        painter.drawPolyline(PolyLine2);
    }



/*
    //Scale to the Max and Min;
    double ScaleX=(FrameSize/2.)/(double)m_SampleSize;
    double ScaleY=(FrameSize/2.)/(double)m_YMax;


    QString SubBufferStr=readBufferSubStr(m_SampleSize);
    for(int i=0;i<SubBufferStr.size();i++){
        unsigned char c = SubBufferStr.at(i).toAscii();
        //PolyLine<<QPointF((i-500)*ScaleX+XOrgin,((int)c)*ScaleY+YOrgin);
        PolyLine<<transformCoordinates((i)*ScaleX,((int)c)*ScaleY,XOrgin,YOrgin);
    }
    painter.setPen(QPen(Qt::red,1));
    painter.drawLines(PolyLine);
*/
    //QString text;
    //text.setNum(TestIterator);


    painter.setPen(QPen(Qt::red,1,Qt::SolidLine));
    QString TimeBaseLable;
    QString TimeBaseNum;
    TimeBaseNum.setNum(m_TimeBase);
    TimeBaseLable ="TimeBase="+TimeBaseNum+"ns/Div";
    painter.drawText(BorderOffset ,FrameSize+BorderOffset,TimeBaseLable);

    QString tmp;
    tmp.setNum(F1Value,'e',10);
    if(F1_On)painter.drawText(BorderOffset ,FrameSize+BorderOffset-40,QString("F1: "+tmp));
    tmp.setNum(F2Value,'e',10);
    if(F2_On)painter.drawText(BorderOffset ,FrameSize+BorderOffset-55,QString("F2: "+tmp));
    tmp.setNum(F3Value,'e',10);
    if(F3_On)painter.drawText(BorderOffset ,FrameSize+BorderOffset-70,QString("F3: "+tmp));
    tmp.setNum(F4Value,'e',10);
    if(F4_On)painter.drawText(BorderOffset ,FrameSize+BorderOffset-85,QString("F4: "+tmp));
    tmp.setNum(F5Value,'e',10);
    if(F5_On)painter.drawText(BorderOffset ,FrameSize+BorderOffset-100,QString("F5: "+tmp));
    tmp.setNum(F6Value,'e',10);
    if(F6_On)painter.drawText(BorderOffset ,FrameSize+BorderOffset-115,QString("F6: "+tmp));

    //Amplitude
    QString Amplitude;
    Amplitude.setNum(50/m_YScale);
    painter.drawText(FrameSize-100 ,FrameSize+BorderOffset,QString("Amplitude CH1="+Amplitude+"/Div"));

    painter.setPen(QPen(Qt::magenta,1,Qt::SolidLine));
    Amplitude.setNum(50/m_YScale2);
    if(m_Channel2)painter.drawText(FrameSize-100 ,FrameSize+BorderOffset-10,QString("Amplitude CH2="+Amplitude+"/Div"));

    painter.setPen(QPen(Qt::red,1,Qt::SolidLine));
    QString SampleRate;
    SampleRate.setNum(m_SampleRate);
    SampleRate = "Sample Rate: "+SampleRate+"k [1/s]";
    painter.drawText(BorderOffset ,BorderOffset,SampleRate);




    painter.end();
}

QPointF ScopeDisplay::TransformIntoWidgetCoordinate(const QPointF &p){

    QPointF P_Trans;

    P_Trans.setX(BorderOffset+m_XOrgin+p.x());
    P_Trans.setY((BorderOffset+m_YOrgin-p.y()));


    return P_Trans;
}

void ScopeDisplay::setData(const PlotDataStruct &vP, double SampleRate){
    m_SampleRate=SampleRate;
    m_dataPoints=vP;

    update();
}

void ScopeDisplay::setTriggerLevel(const double tl){
    m_TriggerLineY=tl;
    update();
}
