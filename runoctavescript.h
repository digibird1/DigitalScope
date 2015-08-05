/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#ifndef RUNOCTAVESCRIPT_H
#define RUNOCTAVESCRIPT_H

/*
 * This class is responsible for running Octave scripts as
 * user functions
 *
 *http://lists.gnu.org/archive/html/help-octave/2009-04/msg00005.html
 */

#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/toplev.h> /* do_octave_atexit */

#include <iostream>
#include "DataStructure.h"


class RunOctaveScript
{
public:
    RunOctaveScript();
    ~RunOctaveScript();

    UsrFunctionStruct runUsrFunction(const PlotDataStruct &a);
};

#endif // RUNOCTAVESCRIPT_H
