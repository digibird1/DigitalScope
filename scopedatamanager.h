/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#ifndef SCOPEDATAMANAGER_H
#define SCOPEDATAMANAGER_H

#include <QObject>
#include "serialmain.h"
#include "scopedisplay.h"
#include "trigger.h"
#include "controlpannel.h"
#include "fftwidget.h"
#include "client.h"
#include "runoctavescript.h"
#include "selectinstrument.h"
#include "userfunctionedit.h"

class ScopeDataManager : public QWidget //QObject
{
    Q_OBJECT
public:
    explicit ScopeDataManager(int argc, char ** argv,QWidget *parent = 0);

    void AutoScale(const PlotDataStruct &v,const double &Time);

    //This functions calculates the user functions
    //and updates the value in the display
    void updateUsrFunctionValues(const PlotDataStruct &a);

private:
    SerialMain *serial;
    Client *client; //Client for the scope server
    ScopeDisplay *display;

    QByteArray m_ReceivedData;
    Trigger m_Trigger;
    ControlPannel *m_Pannel;

    FFTWidget *fftWidget;

    QTimer *m_timer;//timer needed for the simulation

    RunOctaveScript *m_runOctaveScript;

    QGridLayout *MainLayout;

    UserFunctionEdit *m_UserFunctionEdit;
    
signals:
    void signal_SimDone(const QByteArray&);
public slots:
    void slot_receiveData(const QByteArray &a);
    void slot_TriggerChange(int tl);
    void slot_callFFT();
    void slot_TriggerChanged(enum_Trigger Trig);

    void slot_AutoScale();
    void slot_ChannelChange(bool b);

    void slot_SimulateData();

    void slot_setUsrFunctionOn();

    void slot_ConnectInstrument(QString Inst, QString Option);



private:
    bool doAutoScaleInNextStep;

    bool m_isSerialData;
    bool m_isNetworkData;

    bool m_is2Channel;

    SelectInstrument *m_InstSelect;
    
};

#endif // SCOPEDATAMANAGER_H
