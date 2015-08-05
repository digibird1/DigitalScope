/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#include "scopedatamanager.h"

#include <iostream>
#include "DataStructure.h"
#include <cmath>
#include <cstring>

ScopeDataManager::ScopeDataManager(int argc, char ** argv,QObject *parent) :
    QObject(parent)
{

    m_isNetworkData=false;
    m_isSerialData=false;

    m_is2Channel=false;

    //Interpret arguments:
    QString SerialPort = "";
    QString NetworkAddr = "";
    QString SimFrequency ="";//Simulation frequency in Hz

    for(int i=1;i<argc;i++){
        std::string sArg =(std::string)argv[i];
        int pos = sArg.find_first_of('=');
        if(pos != std::string::npos){
            std::string sLeft = sArg.substr(0,pos);
            std::string sRight = sArg.substr(pos+1,sArg.length());

            if(sLeft=="SERIAL") SerialPort=QString(sRight.c_str());
            else if(sLeft=="NETWORK") NetworkAddr=QString(sRight.c_str()); //int the form xxx.xxx.xxx.xxx:xxxxx
            else if(sLeft=="SIMULATION") SimFrequency=QString(sRight.c_str());


            else{
                std::cerr<<"Unknown option!"<<std::endl;
            }
        }
    }

    std::cout<<"SerialPort "<<SerialPort.toStdString()<<std::endl;
    std::cout<<"NetworkAddr "<<NetworkAddr.toStdString()<<std::endl;
    std::cout<<"SimFrequency (not yet used)"<<SimFrequency.toStdString()<<std::endl;


    if(SerialPort=="" && NetworkAddr =="" && SimFrequency == "") quick_exit(-1);


    if(SerialPort!=""){
        serial= new SerialMain(SerialPort);
        connect(serial,SIGNAL(dataReceived(QByteArray)),this,SLOT(slot_receiveData(QByteArray)));
        m_isSerialData=true;
    }
    else if(NetworkAddr!=""){
        client = new Client(NetworkAddr);
        connect(client,SIGNAL(dataReceived(QByteArray)),this,SLOT(slot_receiveData(QByteArray)));
        m_isNetworkData=true;
        m_is2Channel=true;
    }
    else if(SimFrequency!=""){

        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_SimulateData()));
        connect(this,SIGNAL(signal_SimDone(QByteArray)),this,SLOT(slot_receiveData(QByteArray)));
        m_timer->start(1000);
        m_isSerialData=true;
    }
    else{
        std::cerr<<"Too many sources to connect to"<<std::endl;
        quick_exit(-1);
    }







    doAutoScaleInNextStep=false;

    display = new ScopeDisplay;
    m_Pannel = new ControlPannel;
    fftWidget = new FFTWidget;

    m_runOctaveScript = new RunOctaveScript;

    display->show();
    m_Pannel->show();



    m_ReceivedData.clear();



    //Some initialization

    //Trigger
    m_Trigger.setTriggerLevel(display->getTriggerLevel());
    m_Pannel->setTriggerLevel(display->getTriggerLevel());

    //Offset
    m_Pannel->setOffsetXLevel(0);
    display->slot_setOffsetX(0);
    m_Pannel->setOffsetYLevel(0);
    display->slot_setOffsetY(0);
    //Scale
    m_Pannel->setScaleXLevel(100);
    display->slot_setScaleX(100);
    m_Pannel->setScaleYLevel(1);
    display->slot_setScaleY(1);

    connect(m_Pannel,SIGNAL(TriggerLevelChanged(int)),this,SLOT(slot_TriggerChange(int)));
    connect(m_Pannel,SIGNAL(OffsetXChanged(int)),display,SLOT(slot_setOffsetX(int)));
    connect(m_Pannel,SIGNAL(OffsetYChanged(int)),display,SLOT(slot_setOffsetY(int)));
    connect(m_Pannel,SIGNAL(OffsetYChanged2(int)),display,SLOT(slot_setOffsetY2(int)));

    connect(m_Pannel,SIGNAL(ScaleXChanged(int)),display,SLOT(slot_setScaleX(int)));
    connect(m_Pannel,SIGNAL(ScaleYChanged(int)),display,SLOT(slot_setScaleY(int)));
    connect(m_Pannel,SIGNAL(ScaleYChanged2(int)),display,SLOT(slot_setScaleY2(int)));

    connect(m_Pannel,SIGNAL(PerformFFT()),this,SLOT(slot_callFFT()));

    connect(m_Pannel,SIGNAL(SoftTriggerChanged(bool)),this,SLOT(slot_SoftTriggerChanged(bool)));

    connect(m_Pannel,SIGNAL(AutoScale()),this,SLOT(slot_AutoScale()));

    connect(m_Pannel,SIGNAL(Channel2ON(bool)),this,SLOT(slot_ChannelChange(bool)));

    connect(m_Pannel,SIGNAL(FX_Changed()),this,SLOT(slot_setUsrFunctionOn()));


}


void ScopeDataManager::slot_receiveData(const QByteArray &a){

    m_ReceivedData.append(a);//Add the new data at the end;

    unsigned int StopPos=0;

    char StopBit=0xFF;//We stop with 2 of these our binary data transfer

    //Search for combination of two stop bits;
    for(int i=1;i<m_ReceivedData.size();i++){
        if(m_ReceivedData[i-1]==StopBit && m_ReceivedData[i]==StopBit ){
            std::cout<<"Found"<<std::endl;
            StopPos=i;
            break;
        }
    }

  //  std::cout<<"here"<<std::endl;


    QByteArray testHex=m_ReceivedData.toHex();
//    std::cout<<(QString::fromLatin1(testHex)).toStdString()<<std::endl;

    QByteArray Message;
    if(StopPos!=0){
      Message=m_ReceivedData.left(StopPos-1);//Returns the message up to the stop bit
      m_ReceivedData=m_ReceivedData.remove(0,StopPos+1);//removes the message up to the stop bit.. so that only the not yet compleate part is there
    }
    else{
        std::cout<<"No End found"<<std::endl;
        return;
    }

    std::cout<<"\nExtracted"<<std::endl;
    testHex=Message.toHex();
//    std::cout<<(QString::fromLatin1(testHex)).toStdString()<<std::endl;
    std::cout<<"\nRest"<<std::endl;
    testHex=m_ReceivedData.toHex();
//    std::cout<<(QString::fromLatin1(testHex)).toStdString()<<std::endl;





    int StructSize=0;
    if(m_isSerialData) StructSize=sizeof(DataStructArduino); //1604;//Size of the received structure in byte
    if(m_isNetworkData) StructSize=sizeof(DataStructPi);

    if(Message.size()!=StructSize){//Check if we have the right structure size
        std::cerr<<"Wrong structure size: "<<Message.size()<<"vs."<<StructSize<<std::endl;
        if(m_isSerialData)std::cerr<<"Arduino"<<std::endl;
        if(m_isNetworkData)std::cerr<<"Pi"<<std::endl;
        return;
    }

    DataStruct data;

    if(m_isSerialData) data=convertByteArrayToStruct(Message,"Arduino");
    if(m_isNetworkData) data=convertByteArrayToStruct(Message,"Pi");

    std::cout<<data.Time<<std::endl;

    double DeltaT=(double)data.Time/data.nPoints;//us
    std::cout<<"DeltaT "<<DeltaT<<"us"<<std::endl;


    DeltaT=DeltaT*1000.;//Convert in ns


   // DeltaT=DeltaT*10;//remove


    //DeltaT=4;//fixme remove
    //display->setTimeStep(DeltaT);


//    QVector<QPointF> testV;

    PlotDataStruct PlotData;

    QVector<double> fftValues;

    for(int i=0;i<data.nPoints;i++){
       // testV<<QPointF(DeltaT*i,data.values[i]);
        PlotData.Channel1<<QPointF(DeltaT*i,data.values[i]);
        PlotData.Channel2<<QPointF(DeltaT*i,data.values2[i]);
        fftValues<<data.values[i];
        std::cout<<"Tab: "<<DeltaT*i<<"\t"<<data.values[i]<<std::endl;
    }




/*
    //Generator
    double Offset=(rand() % 200 + 100);
    double Phase = 2*M_PI/360*(rand() % 360 );
    for(int i=0;i<1000;i++){

        testV<<QPointF(i*2-Offset,100*sin(2*M_PI/100*i+Phase));
    }
*/



    //m_Trigger.setTriggerLevel(90);


    double SampleRate=data.nPoints*1000./data.Time; //data.Time is in us | Samples per ns


    //Autoscale
    if(doAutoScaleInNextStep) AutoScale(PlotData,data.Time*1000);


    //check if stop button is clicked
    if(m_Pannel->isStop()) return;



    updateUsrFunctionValues(PlotData);

    display->setData(m_Trigger.EdgeTrigger(PlotData),SampleRate);

    fftWidget->performFFT(fftValues,data.Time);

/*
    //edge Trigger
    double TriggerLevel=90;
    int FirstPointOverLevel=-1;

    for(int i=1;i<testV.size();i++){
        if(testV[i].y()>=TriggerLevel && testV[i-1].y()<TriggerLevel){
            FirstPointOverLevel=i;
            break;
        }
    }

    //calculate slope between fist triggered point and the point before
    double m=(testV[FirstPointOverLevel].y()-testV[FirstPointOverLevel-1].y())/(testV[FirstPointOverLevel].x()-testV[FirstPointOverLevel-1].x());

    //calculate the offset to always get the same start pos of the triggered point (y-b)/m=x

    double X_Off=TriggerLevel/m;

    //The point P[FirstPointOverLevel-1] + X_Off has to be alsways at the same pos

    //courve should start at -200

    double TotalOff=-200-(testV[FirstPointOverLevel-1].x()+X_Off);

    //Correct all points by this offset
    for(int i=0;i<testV.size();i++){
        testV[i].setX(testV[i].x()+TotalOff);
    }

    display->setData(testV);
*/
}


void ScopeDataManager::slot_TriggerChange(int tl){
    m_Trigger.setTriggerLevel(tl);
    display->setTriggerLevel(tl);
}

void ScopeDataManager::slot_callFFT(){
    QVector<double> fftValues;
    QVector<double> fftValues2;

    PlotDataStruct data = display->getDataPoints();

    if(data.Channel1.size()==0) return;

    for(int i=0;i<data.Channel1.size();i++){
        fftValues<<data.Channel1[i].y();
        fftValues2<<data.Channel2[i].y();
    }

    double Time=(data.Channel1[1].x()-data.Channel1[0].x())*data.Channel1.size();

    fftWidget->performFFT(fftValues,Time,1);

    if(m_is2Channel)fftWidget->performFFT(fftValues2,Time,2);



    fftWidget->show();

}

void ScopeDataManager::slot_SoftTriggerChanged(bool isSoftTrig){
    m_Trigger.setSoftTrigger(isSoftTrig);
    display->setSoftTrigger(isSoftTrig);
}

void ScopeDataManager::slot_AutoScale(){
    doAutoScaleInNextStep=true;
}

void ScopeDataManager::slot_SimulateData(){
    const int Samples=1600;
    struct data{
      int Time;
      //unsigned int Values[800];
      char Values[Samples];
    } Data;

    double Frequency=100;

    for(int i=0;i<Samples;i++){
        //16 periods
        double r=(125.*std::sin(2.*M_PI*Frequency*(1+(0.00001*(std::rand()%10)/10.))*i/((double)Samples)));
        std::cout<<"r "<<r<<std::endl;
        Data.Values[i]=(char)(int)r;
    }

    Data.Time=1e6;

    char *structurePointer=(char *)&Data;

    QByteArray a;
    for(size_t i=0;i<sizeof(Data);i++){
        a.append(structurePointer[i]);
    }
    a.append(0xFF);
    a.append(0xFF);




    emit signal_SimDone(a);
    m_timer->start(100);
}

void ScopeDataManager::AutoScale(const PlotDataStruct &v,const double &Time){

    //Scan through trigger
    doAutoScaleInNextStep=false;
    int i=0;
    for(i=0;i<255;i++){
        m_Trigger.setTriggerLevel(i);
        if(m_Trigger.EdgeTrigger(v).Channel1.size()>0) break;
    }

    //Set Trigger Level
    m_Trigger.setTriggerLevel(i);
    m_Pannel->setTriggerLevel(i);
    display->setTriggerLevel(i);


    double Max=0;
    double Min=99999999999999999999;

    for(i=0;i<v.Channel1.size();i++){
        if(v.Channel1[i].y()>Max)Max=v.Channel1[i].y();
        if(v.Channel1[i].y()<Min)Min=v.Channel1[i].y();
    }

    int Scale=50/std::abs(Max-Min)*20; //fixme This needs to be understood

    std::cout<<"Scale "<<Scale<<"\t"<<std::abs(Max-Min)<<std::endl;

    m_Pannel->setScaleYLevel(Scale);
    display->slot_setScaleY(Scale);


    //we ant 4 div and Time is in ns
    m_Pannel->setScaleXLevel((int)Time/4);
    display->slot_setScaleX((int)Time/4 );


}


void ScopeDataManager::slot_ChannelChange(bool b){
    display->set2Channel(b);
    m_is2Channel=b;

}

void ScopeDataManager::slot_setUsrFunctionOn(){
    std::cout<<"DDD slot_setUsrFunctionOn()"<<std::endl;
    display->slot_showF1(m_Pannel->isCheckedUsrFunc("F1"));
    display->slot_showF2(m_Pannel->isCheckedUsrFunc("F2"));
    display->slot_showF3(m_Pannel->isCheckedUsrFunc("F3"));
    display->slot_showF4(m_Pannel->isCheckedUsrFunc("F4"));
    display->slot_showF5(m_Pannel->isCheckedUsrFunc("F5"));
    display->slot_showF6(m_Pannel->isCheckedUsrFunc("F6"));
}

void ScopeDataManager::updateUsrFunctionValues(const PlotDataStruct &a){
    if(m_Pannel->isCheckedUsrFunc("F1")){



        display->setF1Value(m_runOctaveScript->runUsrFunction(a).ReturnValue);
    }

    if(m_Pannel->isCheckedUsrFunc("F2")){
        display->setF2Value(100);
    }

    if(m_Pannel->isCheckedUsrFunc("F3")){
        display->setF3Value(100);
    }

    if(m_Pannel->isCheckedUsrFunc("F4")){
        display->setF4Value(100);
    }

    if(m_Pannel->isCheckedUsrFunc("F5")){
        display->setF5Value(100);
    }

    if(m_Pannel->isCheckedUsrFunc("F6")){
        display->setF6Value(100);
    }
}













