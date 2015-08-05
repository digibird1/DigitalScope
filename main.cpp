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
 * Add button for DC / AC
 * ADD drop down menu to select the different scopes
 * Add a window to edit matlab scripts
 *
 */
