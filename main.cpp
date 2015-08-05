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

