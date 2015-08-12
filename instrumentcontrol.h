/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */

/*
 * This class is a general class to provide functionality
 * to control instruments
 *
 */


#ifndef INSTRUMENTCONTROL_H
#define INSTRUMENTCONTROL_H

#include <cstring>
#include <string>
#include <vector>

struct InstrumentData {
  //Data in channel 1-4
  std::vector<double> DataCh1;
  std::vector<double> DataCh2;
  std::vector<double> DataCh3;
  std::vector<double> DataCh4;
};

enum TriggerEdge{RAISING_EDGE,FALLING_EDGE,OFF};

class InstrumentControl
{
public:
    InstrumentControl();

    //Set and get informations if AC or DC is set
    void setMode(const std::string &Mode){m_Mode=Mode;} //options are AC, DC
    std::string getMode(){ return m_Mode;}

    //General Function to get the measurment data
    InstrumentData* getInstrumentData(){return m_InstrumentData;}

    //read the Instrument has to be called before Instrument data is available
    void readInstrument();

    //Functions to set the sample rate of the instrument
    void setSampleRate(double SampleRate){m_SampleRate=SampleRate;}
    double getSampleRate(){return m_SampleRate;}

    //functions to set trigger
    void setTriggerLevel(double TriggerLevel){m_TriggerLevel=TriggerLevel;}
    double getTriggerLevel(){return m_TriggerLevel;}

    void setTriggerEdge(TriggerEdge Edge){m_TriggerEdge=Edge;}
    TriggerEdge getTrigerEdge(){return m_TriggerEdge;}

    //set the scale of the scope
    void setXScale(double XScale){m_XScale=XScale;}
    void setYScale(double YScale){m_YScale=YScale;}
    double getXScale(){return m_XScale;}
    double getYScale(){return m_YScale;}

    //Autoscale Scope
    void setAutoScale();

    //Set Instrument Adress Serial Port, IP adress GPIB ...
    void setInstAdress(std::string InstAdress){m_InstAddress=InstAdress;}
    std::string getInstAdress(){return m_InstAddress;}

private:
    std::string m_Mode;//if it is not
    InstrumentData* m_InstrumentData;
    int m_SampleRate;
    double m_TriggerLevel;
    TriggerEdge m_TriggerEdge;
    double m_XScale;
    double m_YScale;
    std::string m_InstAddress;
};

#endif // INSTRUMENTCONTROL_H
