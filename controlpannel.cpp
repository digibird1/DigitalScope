/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#include "controlpannel.h"

ControlPannel::ControlPannel(QWidget *parent) :
    QWidget(parent)
{

    m_isStop=false;
    m_isSOftTrigger=true;
    m_is2Channel=false;

    Grid_Main=new QGridLayout;
    Grid_Trigger=new QGridLayout;
    Grid_Offset=new QGridLayout;
    Grid_Scale=new QGridLayout;
    Grid_Other=new QGridLayout;
    Grid_UsrFunc=new QGridLayout;

    //Group_Main = new QGroupBox("Scope Control");
    Group_Trigger= new QGroupBox("Trigger");
    Group_Offset= new QGroupBox("Offset");
    Group_Scale= new QGroupBox("Scale");
    Group_Other= new QGroupBox("Other");
    Group_UsrFunc=new QGroupBox("Usr Func");

    Button_Stop= new QPushButton("Stop");
    Button_FFT= new QPushButton("Perform FFT");
    Button_SoftTrigger = new QPushButton("SoftTrig OFF");
    Button_Auto = new QPushButton("Auto");
    Button_Channel = new QPushButton("Set Ch2 ON");

    RadioB_Range1= new QRadioButton("1-1000 ns");
    RadioB_Range2= new QRadioButton("1-1000 us");
    RadioB_Range3= new QRadioButton("1-1000 ms");
    RadioB_Range1->setChecked(true);

    CheckBox_F1 = new QCheckBox("Usr F1");
    CheckBox_F2 = new QCheckBox("Usr F2");
    CheckBox_F3 = new QCheckBox("Usr F3");
    CheckBox_F4 = new QCheckBox("Usr F4");
    CheckBox_F5 = new QCheckBox("Usr F5");
    CheckBox_F6 = new QCheckBox("Usr F6");


    Scroll_Knob= new QwtKnob;
    //Scroll_Knob->setTotalAngle(1);
    Scroll_Knob->setNumTurns(30);
    Scroll_Knob->setMarkerStyle(QwtKnob::Tick);

    Scroll_Knob->setScale(0,30000);
    Scroll_Knob->setScaleStepSize(100);

    Scroll_Knob->setTotalSteps(3000);




    //Trigger
    Slid_V_Trigger = new QSlider(Qt::Vertical);
    Slid_V_Trigger->setMinimum(-350);
    Slid_V_Trigger->setMaximum(350);
    Grid_Trigger->addWidget(Slid_V_Trigger,0,0);

    Group_Trigger->setLayout(Grid_Trigger);


    //Offset
    Slid_V_Offset= new QSlider(Qt::Vertical);
    Slid_V_Offset->setMinimum(-350);
    Slid_V_Offset->setMaximum(350);
    Slid_V_Offset->setTickPosition(QSlider::TicksBothSides);
    Slid_V_Offset->setTickInterval(35);
    Slid_H_Offset= new QSlider(Qt::Horizontal);
    Slid_H_Offset->setMinimum(-350);
    Slid_H_Offset->setMaximum(350);
    //Channel 2
    Slid_V_Offset2= new QSlider(Qt::Vertical);
    Slid_V_Offset2->setMinimum(-350);
    Slid_V_Offset2->setMaximum(350);
    Slid_V_Offset2->setTickPosition(QSlider::TicksBothSides);
    Slid_V_Offset2->setTickInterval(35);
    Slid_V_Offset2->setEnabled(false);



    Grid_Offset->addWidget(new QLabel("Ch1"),0,0);
    Grid_Offset->addWidget(new QLabel("Ch2"),0,1);
    Grid_Offset->addWidget(Slid_V_Offset,1,0);
    Grid_Offset->addWidget(Slid_V_Offset2,1,1);
    Grid_Offset->addWidget(Slid_H_Offset,0,2);
    Grid_Offset->addWidget(Scroll_Knob,1,2);


    Group_Offset->setLayout(Grid_Offset);

    //Scale
    Slid_V_Scale= new QSlider(Qt::Vertical);
    Slid_V_Scale->setMinimum(1);
    Slid_V_Scale->setMaximum(100);
    Slid_V_Scale->setSingleStep(1);
    Slid_H_Scale= new QSlider(Qt::Horizontal);
    Slid_H_Scale->setMinimum(1);
    Slid_H_Scale->setMaximum(1000);
    Slid_H_Scale->setSingleStep(1);
    //channel 2
    Slid_V_Scale2= new QSlider(Qt::Vertical);
    Slid_V_Scale2->setMinimum(1);
    Slid_V_Scale2->setMaximum(100);
    Slid_V_Scale2->setSingleStep(1);
    Slid_V_Scale2->setEnabled(false);


    Grid_Scale->addWidget(new QLabel("Ch1"),0,0);
    Grid_Scale->addWidget(new QLabel("Ch2"),0,1);
    Grid_Scale->addWidget(Slid_V_Scale,1,0);
    Grid_Scale->addWidget(Slid_V_Scale2,1,1);
    Grid_Scale->addWidget(Slid_H_Scale,0,2);


    Grid_Range = new QGridLayout;
    Grid_Range->addWidget(RadioB_Range1,1,0);
    Grid_Range->addWidget(RadioB_Range2,2,0);
    Grid_Range->addWidget(RadioB_Range3,3,0);


    Group_Range= new QGroupBox("Range");
    Group_Range->setLayout(Grid_Range);

    Grid_Scale->addWidget(Group_Range,1,2);

    Group_Scale->setLayout(Grid_Scale);


    Grid_Other->addWidget(Button_Stop,0,1);
    Grid_Other->addWidget(Button_FFT,1,1);
    Grid_Other->addWidget(Button_SoftTrigger,2,1);
    Grid_Other->addWidget(Button_Auto,3,1);
    Grid_Other->addWidget(Button_Channel,4,1);



    Group_Other->setLayout(Grid_Other);

    Grid_UsrFunc->addWidget(CheckBox_F1,0,0);
    Grid_UsrFunc->addWidget(CheckBox_F2,1,0);
    Grid_UsrFunc->addWidget(CheckBox_F3,2,0);
    Grid_UsrFunc->addWidget(CheckBox_F4,3,0);
    Grid_UsrFunc->addWidget(CheckBox_F5,4,0);
    Grid_UsrFunc->addWidget(CheckBox_F6,5,0);


    Group_UsrFunc->setLayout(Grid_UsrFunc);

    Grid_Main->addWidget(Group_Trigger,0,0);
    Grid_Main->addWidget(Group_Other,0,1);
    Grid_Main->addWidget(Group_Offset,1,0);
    Grid_Main->addWidget(Group_Scale,1,1);
    Grid_Main->addWidget(Group_UsrFunc,0,2);

    setLayout(Grid_Main);

    setFixedSize(500,400);


    //connect(Slid_V_Trigger,SIGNAL(valueChanged(int)),this,SLOT(slot_TriggerLevelChanged(int)));

    connect(Slid_V_Trigger,SIGNAL(valueChanged(int)),this,SIGNAL(TriggerLevelChanged(int)));
    connect(Slid_V_Offset,SIGNAL(valueChanged(int)),this,SIGNAL(OffsetYChanged(int)));
    connect(Slid_V_Offset2,SIGNAL(valueChanged(int)),this,SIGNAL(OffsetYChanged2(int)));
    connect(Slid_H_Offset,SIGNAL(valueChanged(int)),this,SIGNAL(OffsetXChanged(int)));
    connect(Slid_V_Scale,SIGNAL(valueChanged(int)),this,SIGNAL(ScaleYChanged(int)));
    connect(Slid_V_Scale2,SIGNAL(valueChanged(int)),this,SIGNAL(ScaleYChanged2(int)));
    connect(Slid_H_Scale,SIGNAL(valueChanged(int)),this,SLOT(slot_ScaleXChanged(int)));

    connect(Button_Stop,SIGNAL(clicked()),this,SLOT(slot_StopRunButtonClicked()));
    connect(Button_FFT,SIGNAL(clicked()),this,SIGNAL(PerformFFT()));
    connect(Button_SoftTrigger,SIGNAL(clicked()),this,SLOT(slot_SoftTriggerChange()));


    connect(RadioB_Range1,SIGNAL(clicked()),this,SLOT(slot_RangeChanged()));
    connect(RadioB_Range2,SIGNAL(clicked()),this,SLOT(slot_RangeChanged()));
    connect(RadioB_Range3,SIGNAL(clicked()),this,SLOT(slot_RangeChanged()));


    connect(Slid_H_Offset,SIGNAL(valueChanged(int)),this,SLOT(slot_KnobNewValue(int)));
    connect(Scroll_Knob,SIGNAL(sliderMoved(double)),this,SLOT(slot_KnobChanged(double)));

    connect(Button_Auto,SIGNAL(clicked()),this,SIGNAL(AutoScale()));

    connect(Button_Channel,SIGNAL(clicked()),this,SLOT(slot_ChannelChanged()));

    connect(CheckBox_F1,SIGNAL(stateChanged(int)),this,SLOT(slot_FX_Changed(int)));
    connect(CheckBox_F2,SIGNAL(stateChanged(int)),this,SLOT(slot_FX_Changed(int)));
    connect(CheckBox_F3,SIGNAL(stateChanged(int)),this,SLOT(slot_FX_Changed(int)));
    connect(CheckBox_F4,SIGNAL(stateChanged(int)),this,SLOT(slot_FX_Changed(int)));
    connect(CheckBox_F5,SIGNAL(stateChanged(int)),this,SLOT(slot_FX_Changed(int)));
    connect(CheckBox_F6,SIGNAL(stateChanged(int)),this,SLOT(slot_FX_Changed(int)));
}

void ControlPannel::setTriggerLevel(int Level){
    Slid_V_Trigger->setValue(Level);
}

void ControlPannel::slot_TriggerLevelChanged(int nl){
    emit TriggerLevelChanged(nl);
}

void ControlPannel::slot_StopRunButtonClicked(){
    if(m_isStop==true){
        Button_Stop->setText("Stop");
        m_isStop=false;
    }
    else{
        Button_Stop->setText("Run");
        m_isStop=true;
    }

}

void ControlPannel::slot_SoftTriggerChange(){

    if(m_isSOftTrigger==true){
        Button_SoftTrigger->setText("SoftTrig ON");
        m_isSOftTrigger=false;
    }
    else{
        Button_SoftTrigger->setText("SoftTrig OFF");
        m_isSOftTrigger=true;
    }

    emit SoftTriggerChanged(m_isSOftTrigger);
}


void ControlPannel::slot_ScaleXChanged(int Scale){

    int Range=1;
    if(RadioB_Range1->isChecked())Range=1;
    if(RadioB_Range2->isChecked())Range=1000;
    if(RadioB_Range3->isChecked())Range=1000000;


    emit ScaleXChanged(Scale*Range);
}

void ControlPannel::slot_RangeChanged(){
    slot_ScaleXChanged(Slid_H_Scale->value());
}

void ControlPannel::slot_KnobChanged(double a){
    std::cout<<"Knob "<<a<<std::endl;
    emit OffsetXChanged((int)-1*a);
}

void ControlPannel::slot_KnobNewValue(int a){
    Scroll_Knob->setValue(a);
}

void ControlPannel::slot_ChannelChanged(){
    if(m_is2Channel){
        m_is2Channel=false;
        Button_Channel->setText("Set Ch2 ON");
        Slid_V_Offset2->setEnabled(false);
        Slid_V_Scale2->setEnabled(false);

        emit Channel2ON(false);
    }
    else{
        m_is2Channel=true;
        Button_Channel->setText("Set Ch2 OFF");
        Slid_V_Offset2->setEnabled(true);
        Slid_V_Scale2->setEnabled(true);
        emit Channel2ON(true);
    }
}

void ControlPannel::slot_FX_Changed(int a){
    emit FX_Changed();
}

bool ControlPannel::isCheckedUsrFunc(QString X){
    if(X=="F1") return CheckBox_F1->isChecked();
    if(X=="F2") return CheckBox_F2->isChecked();
    if(X=="F3") return CheckBox_F3->isChecked();
    if(X=="F4") return CheckBox_F4->isChecked();
    if(X=="F5") return CheckBox_F5->isChecked();
    if(X=="F6") return CheckBox_F6->isChecked();

    return false;
}
