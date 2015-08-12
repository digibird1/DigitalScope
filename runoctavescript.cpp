/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#include "runoctavescript.h"

RunOctaveScript::RunOctaveScript()
{
    const char * argvv [] = {"" /* name of program, not relevant */, "--silent", "--path", "UsrScripts"};
      octave_main (4, (char **) argvv, true /* embedded */);

      /*
       * There is some chance that octave only is allowed to be initialized one time
       * I thsi is the case, we need to make sure that of the constructor is called a second time
       * that we don't open it again... not tested yet
       *
       *http://octave.1599824.n4.nabble.com/embedding-octave-twice-causes-warning-duplicate-binary-operator-td1634950.html
       */

}

RunOctaveScript::~RunOctaveScript(){
    //do_octave_atexit ();
}


UsrFunctionStruct RunOctaveScript::runUsrFunction(const PlotDataStruct &a, QString ScriptName){
      UsrFunctionStruct UsrResult;


      octave_value_list functionArguments;



      ColumnVector XVectorCh1(a.Channel1.size());
      ColumnVector YVectorCh1(a.Channel1.size());
      ColumnVector XVectorCh2(a.Channel2.size());
      ColumnVector YVectorCh2(a.Channel2.size());

      for(int i=0;i<a.Channel1.size();i++){
          XVectorCh1(i) = a.Channel1.at(i).x();
          YVectorCh1(i) = a.Channel1.at(i).y();
      }

      for(int i=0;i<a.Channel2.size();i++){
          XVectorCh2(i) = a.Channel2.at(i).x();
          YVectorCh2(i) = a.Channel2.at(i).y();
      }
      functionArguments (0) = XVectorCh1;
      functionArguments (1) = YVectorCh1;
      functionArguments (2) = XVectorCh2;
      functionArguments (3) = YVectorCh2;

      const octave_value_list result = feval (ScriptName.toStdString(), functionArguments, 1);

      if(result.empty()){
          std::cerr<<"User Function Script Error, No return Value!!!!"<<std::endl;
          UsrResult.FunctionName=QString("");
          UsrResult.ReturnValue=0;
          UsrResult.Unit=QString("");
      //    do_octave_atexit ();

          return UsrResult;
      }


      std::cerr << "FunctionName" << result (0).string_value () << std::endl;
      std::cerr << "RetrunValue " << result (1).scalar_value () << std::endl;
      std::cerr << "Unit" << result (2).string_value ()<< std::endl;


      UsrResult.FunctionName=QString(result (0).string_value ().c_str());
      UsrResult.ReturnValue=result (1).scalar_value ();
      UsrResult.Unit=QString(result (2).string_value ().c_str());

   //   do_octave_atexit ();

      return UsrResult;

}
