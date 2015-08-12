/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#include <QApplication>

#include <iostream>
#include "scopedatamanager.h"


using namespace std;

int main(int argc, char ** argv )
{

    QApplication app( argc, argv );
    cout << "Hello World!" << endl;

    //SerialMain serialMain;
    ScopeDataManager s( argc, argv);

    return app.exec();
}

/*
 * TODO:
 *
 * Add suppot for soundcard, RIGOL scope
 * Make the trigger button with three states Softtrigger, Hardware trigger if available, OFF
 * Channel 2 is only clickable when instrument has two channels
 *
 * Add a window to edit matlab scripts
 *
 *
 * Add a way to export a screen shot
 * Write a Class with general instrument control
 *
 */
