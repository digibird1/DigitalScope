/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#include "selectinstrument.h"

SelectInstrument::SelectInstrument(QWidget *parent) :
    QWidget(parent)
{
    Grid_Main=new QGridLayout;
    Group_InstSel=new QGroupBox;
    Button_Select= new QPushButton("Select");

    ComBox_InstSel = new QComboBox;
    LinEd_InstOption = new QLineEdit("Adress");

    Grid_Main->addWidget(ComBox_InstSel,0,0);
    Grid_Main->addWidget(LinEd_InstOption,0,1);
    Grid_Main->addWidget(Button_Select);

    setLayout(Grid_Main);

    connect(Button_Select,SIGNAL(clicked()),this,SLOT(slot_selectPressed()));

    ComBox_InstSel->addItem("Soundcard");
    ComBox_InstSel->addItem("Arduino Scope");
    ComBox_InstSel->addItem("RPi Scope");
    ComBox_InstSel->addItem("Rigol");
    ComBox_InstSel->addItem("ADC200");
    ComBox_InstSel->addItem("Simulation");


}

void SelectInstrument::slot_selectPressed(){
    close();
    emit signal_SelectionDone(ComBox_InstSel->currentText(), LinEd_InstOption->text());
}
