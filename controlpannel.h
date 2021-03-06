/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#ifndef CONTROLPANNEL_H
#define CONTROLPANNEL_H

#include <QWidget>
#include <QtGui>
#include <iostream>

#include <qwt_knob.h>

enum enum_ACDC{NONE,AC,DC};
enum enum_Trigger{OFF,SOFT,HARD};

class ControlPannel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPannel(QWidget *parent = 0);

    void setTriggerLevel(int Level);

    void setOffsetXLevel(int Level){Slid_H_Offset->setValue(Level);}
    void setOffsetYLevel(int Level){Slid_V_Offset->setValue(Level); Slid_V_Offset2->setValue(Level);}
    void setScaleXLevel(int Level){Slid_H_Scale->setValue(Level);


                                if(Level>0 && Level/1000==0 && Level/1000000==0){
                                  RadioB_Range1->setChecked(true);
                                  Slid_H_Scale->setValue(Level/1000);
                                }
                                else if(Level/1000>0 && Level/1000000==0){
                                    RadioB_Range2->setChecked(true);
                                    Slid_H_Scale->setValue(Level/1000);
                                }
                                else if( Level/1000000==0){
                                    RadioB_Range3->setChecked(true);
                                    Slid_H_Scale->setValue(Level/1000000);
                                }
                                else{
                                    std::cerr<<"There was an error in Setting Scale X and Range"<<std::endl;
                                    RadioB_Range3->setChecked(true);
                                    Slid_H_Scale->setValue(1);
                                }

    }
    void setScaleYLevel(int Level){Slid_V_Scale->setValue(Level);Slid_V_Scale2->setValue(Level);}




    bool isStop(){return m_isStop;}
    bool isSoftTrigger(){return (m_Trigger==SOFT);}
    void setHasHardWareTrigger(bool t){m_hasHardWareTrigger=t;}

    //Check if a function checkbox is checked
    //Opptions are F1, F2 ... F6
    bool isCheckedUsrFunc(QString X);
    //This function disables the ckeckbox again
    //This is usefull if an external class wants to disable the ckeck box
    //for example if the user function does not exist
    void unCheckUsrFunction(QString X);

    
signals:
    void TriggerLevelChanged(int);
    void OffsetYChanged(int);
    void OffsetYChanged2(int);
    void OffsetXChanged(int);
    void ScaleYChanged(int);
    void ScaleYChanged2(int);
    void ScaleXChanged(int);
    void PerformFFT();
    void TriggerChanged(enum_Trigger);
    void AutoScale();
    void Channel2ON(bool);
    void FX_Changed();
    void ACDCChanged(int);

    //Add function get which uses status of teh checkbox to return values for f1-f6

    
public slots:
    void slot_TriggerLevelChanged(int nl);
    void slot_StopRunButtonClicked();
    void slot_TriggerChange();
    void slot_ScaleXChanged(int Scale);
    void slot_RangeChanged();
    void slot_KnobChanged(double);
    void slot_KnobNewValue(int);
    void slot_ChannelChanged();
    void slot_FX_Changed(int);
    void slot_ACDCChanged();

private:
    QGridLayout *Grid_Main;
    QGridLayout *Grid_Trigger;
    QGridLayout *Grid_Offset;
    QGridLayout *Grid_Scale;
    QGridLayout *Grid_Other;
    QGridLayout *Grid_UsrFunc;
    QGridLayout *Grid_AcDc;

    QGroupBox *Group_Other;
    QGroupBox *Group_Trigger;
    QGroupBox *Group_Offset;
    QGroupBox *Group_Scale;
    QGroupBox *Group_UsrFunc;
    QGroupBox *Group_AcDc;



    QSlider *Slid_V_Trigger;
    QSlider *Slid_V_Offset;
    QSlider *Slid_V_Scale;

    QSlider *Slid_V_Offset2;
    QSlider *Slid_V_Scale2;

    QSlider *Slid_H_Offset;
    QSlider *Slid_H_Scale;


    QPushButton *Button_Stop;
    QPushButton *Button_FFT;
    QPushButton *Button_Trigger;
    QPushButton *Button_Auto;
    QPushButton *Button_Channel;


    QGridLayout *Grid_Range;
    QGroupBox *Group_Range;
    QRadioButton *RadioB_Range1;
    QRadioButton *RadioB_Range2;
    QRadioButton *RadioB_Range3;


    QwtKnob *Scroll_Knob;

    //turn the user functions on/off
    QCheckBox *CheckBox_F1;
    QCheckBox *CheckBox_F2;
    QCheckBox *CheckBox_F3;
    QCheckBox *CheckBox_F4;
    QCheckBox *CheckBox_F5;
    QCheckBox *CheckBox_F6;

    //AC or DC coubling of the scope
    QRadioButton *RadioB_DC;
    QRadioButton *RadioB_AC;

    bool m_isStop;
    enum_Trigger m_Trigger;
    bool m_is2Channel;
    bool m_hasHardWareTrigger;


    
};

#endif // CONTROLPANNEL_H
