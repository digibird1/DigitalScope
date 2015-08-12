/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#include "instrumentcontrol.h"

InstrumentControl::InstrumentControl()
{
    m_InstrumentData=new InstrumentData;
}

void InstrumentControl::readInstrument(){
    //Add here the code the read the instrument and
    //save the retruned data into the m_InstrumentData structure
}

void InstrumentControl::setAutoScale(){
    //Add here the code to run Auto mode on the scope
}
