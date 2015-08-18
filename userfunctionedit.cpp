/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */

#include "userfunctionedit.h"
#include <iostream>

UserFunctionEdit::UserFunctionEdit(QWidget *parent) :
    QWidget(parent)
{

    m_OpenFile= new QFile;

    Grid_Main = new QGridLayout;
    Grid_UsrFunc = new QGridLayout;
    Group_UsrFuncEdit = new QGroupBox("User Functions");
    Button_Save = new QPushButton("Save");
    Button_Close = new QPushButton("Close");
    Button_New_File = new QPushButton("New");

    Button_Save->setEnabled(false);

    Button_SetF1 = new QPushButton("Set F1");
    Button_SetF2 = new QPushButton("Set F2");
    Button_SetF3 = new QPushButton("Set F3");
    Button_SetF4 = new QPushButton("Set F4");
    Button_SetF5 = new QPushButton("Set F5");
    Button_SetF6 = new QPushButton("Set F6");


    Button_EditF1 = new QPushButton("Edit");
    Button_EditF2 = new QPushButton("Edit");
    Button_EditF3 = new QPushButton("Edit");
    Button_EditF4 = new QPushButton("Edit");
    Button_EditF5 = new QPushButton("Edit");
    Button_EditF6 = new QPushButton("Edit");

    LE_UsrF1= new QLineEdit("");
    LE_UsrF2= new QLineEdit("");
    LE_UsrF3= new QLineEdit("");
    LE_UsrF4= new QLineEdit("");
    LE_UsrF5= new QLineEdit("");
    LE_UsrF6= new QLineEdit("");

    LE_UsrF1->setDisabled(true);
    LE_UsrF2->setDisabled(true);
    LE_UsrF3->setDisabled(true);
    LE_UsrF4->setDisabled(true);
    LE_UsrF5->setDisabled(true);
    LE_UsrF6->setDisabled(true);

    TE_UserFuncCode= new QTextEdit;
    TE_UserFuncCode->setWordWrapMode(QTextOption::NoWrap);

            //QTextOption::NoWrap

    Grid_UsrFunc->addWidget(LE_UsrF1,0,0);
    Grid_UsrFunc->addWidget(LE_UsrF2,1,0);
    Grid_UsrFunc->addWidget(LE_UsrF3,2,0);
    Grid_UsrFunc->addWidget(LE_UsrF4,3,0);
    Grid_UsrFunc->addWidget(LE_UsrF5,4,0);
    Grid_UsrFunc->addWidget(LE_UsrF6,5,0);
    Grid_UsrFunc->addWidget(Button_SetF1,0,1);
    Grid_UsrFunc->addWidget(Button_SetF2,1,1);
    Grid_UsrFunc->addWidget(Button_SetF3,2,1);
    Grid_UsrFunc->addWidget(Button_SetF4,3,1);
    Grid_UsrFunc->addWidget(Button_SetF5,4,1);
    Grid_UsrFunc->addWidget(Button_SetF6,5,1);


    Grid_UsrFunc->addWidget(Button_EditF1,0,2);
    Grid_UsrFunc->addWidget(Button_EditF2,1,2);
    Grid_UsrFunc->addWidget(Button_EditF3,2,2);
    Grid_UsrFunc->addWidget(Button_EditF4,3,2);
    Grid_UsrFunc->addWidget(Button_EditF5,4,2);
    Grid_UsrFunc->addWidget(Button_EditF6,5,2);


    Group_UsrFuncEdit->setFixedWidth(300);

    Group_UsrFuncEdit->setLayout(Grid_UsrFunc);

    Grid_Main->addWidget(Group_UsrFuncEdit,0,0);
    Grid_Main->addWidget(TE_UserFuncCode,0,1,1,2);

    Grid_Main->addWidget(Button_Close,1,0);
    Grid_Main->addWidget(Button_Save,1,1);
    Grid_Main->addWidget(Button_New_File,1,2);

    setLayout(Grid_Main);

    connect(Button_SetF1,SIGNAL(clicked()),this,SLOT(slot_setF1()));
    connect(Button_SetF2,SIGNAL(clicked()),this,SLOT(slot_setF2()));
    connect(Button_SetF3,SIGNAL(clicked()),this,SLOT(slot_setF3()));
    connect(Button_SetF4,SIGNAL(clicked()),this,SLOT(slot_setF4()));
    connect(Button_SetF5,SIGNAL(clicked()),this,SLOT(slot_setF5()));
    connect(Button_SetF6,SIGNAL(clicked()),this,SLOT(slot_setF6()));


    connect(Button_EditF1,SIGNAL(clicked()),this,SLOT(slot_editF1()));
    connect(Button_EditF2,SIGNAL(clicked()),this,SLOT(slot_editF2()));
    connect(Button_EditF3,SIGNAL(clicked()),this,SLOT(slot_editF3()));
    connect(Button_EditF4,SIGNAL(clicked()),this,SLOT(slot_editF4()));
    connect(Button_EditF5,SIGNAL(clicked()),this,SLOT(slot_editF5()));
    connect(Button_EditF6,SIGNAL(clicked()),this,SLOT(slot_editF6()));

    connect(Button_Save,SIGNAL(clicked()),this,SLOT(slot_saveToFile()));
    connect(Button_New_File,SIGNAL(clicked()),this,SLOT(slot_newFile()));
    connect(Button_Close,SIGNAL(clicked()),this,SLOT(close()));
}

void UserFunctionEdit::slot_setF1(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("User Functions (*.m)"));
    if(fileName!="")LE_UsrF1->setText(fileName);
}

void UserFunctionEdit::slot_setF2(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("User Functions (*.m)"));
    if(fileName!="")LE_UsrF2->setText(fileName);
}

void UserFunctionEdit::slot_setF3(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("User Functions (*.m)"));
    if(fileName!="")LE_UsrF3->setText(fileName);
}

void UserFunctionEdit::slot_setF4(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("User Functions (*.m)"));
    if(fileName!="")LE_UsrF4->setText(fileName);
}

void UserFunctionEdit::slot_setF5(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("User Functions (*.m)"));
    if(fileName!="")LE_UsrF5->setText(fileName);
}

void UserFunctionEdit::slot_setF6(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("User Functions (*.m)"));
    if(fileName!="")LE_UsrF6->setText(fileName);
}

void UserFunctionEdit::editUserFunction(QString FileName){
    //open the file and save a pointer to the file which is open
    //use the pointer together with the save button
    //load the text into the text edit


    if(m_OpenFile->isOpen()){
        int ret = QMessageBox::warning(this, tr("File Open"),
                                       tr("These is already an open file do you want to save it before opening a new one?"),
                                       QMessageBox::Save|QMessageBox::No);

        switch (ret) {
          case QMessageBox::Save:
              slot_saveToFile();
              break;
          case QMessageBox::No:
            ;//do nothing
              break;
          default:
              // should never be reached
              break;
        }

        m_OpenFile->close();
        //m_OpenFile=NULL;
    }


    m_OpenFile->setFileName(FileName);

    if(!m_OpenFile->exists()){
        int ret = QMessageBox::critical(this, tr("File Open"),
                                       tr("The file could not be opened"),
                                       QMessageBox::Ok);
        return;
    }

//load the file int text edit
    m_OpenFile->open(QIODevice::ReadOnly);
    m_OpenFile->setTextModeEnabled(true);
    QByteArray FileText=m_OpenFile->readAll();

    TE_UserFuncCode->setText(QString(FileText));
    Button_Save->setEnabled(true);

}

void UserFunctionEdit::slot_editF1(){
    editUserFunction(LE_UsrF1->text());
}
void UserFunctionEdit::slot_editF2(){
    editUserFunction(LE_UsrF2->text());
}
void UserFunctionEdit::slot_editF3(){
    editUserFunction(LE_UsrF3->text());
}
void UserFunctionEdit::slot_editF4(){
    editUserFunction(LE_UsrF4->text());
}
void UserFunctionEdit::slot_editF5(){
    editUserFunction(LE_UsrF5->text());
}
void UserFunctionEdit::slot_editF6(){
    editUserFunction(LE_UsrF6->text());
}

void UserFunctionEdit::slot_saveToFile(){
    if(m_OpenFile->exists())
        m_OpenFile->close();
        m_OpenFile->open(QIODevice::WriteOnly);
        m_OpenFile->write(TE_UserFuncCode->toPlainText().toAscii());
        m_OpenFile->close();
        m_OpenFile->open(QIODevice::ReadOnly);
}

void UserFunctionEdit::slot_newFile(){
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("New User Function"), "UsrScripts", tr("User Functions (*.m)"));
    //The template for a user function:
    QString UF_Template;

    UF_Template+="%XVecCh1,YVecCh1,XVecCh2,YVecCh2 these are the x and y vectors with the to define the data points\n";
    UF_Template+="\n";
    UF_Template+="% the function has to return the function name (string\n";
    UF_Template+="% The return value, a doubel of the result\n";
    UF_Template+="% The unit, a string, return "" if no unit\n";
    UF_Template+="\n";
    UF_Template+="function [FunctionName, RetrunValue, Unit] = ExampleUsrFunction (XVecCh1,YVecCh1,XVecCh2,YVecCh2)\n";
    UF_Template+="  FunctionName = \"ExampleUsrFunction\";\n";
    UF_Template+="  RetrunValue = 1000001;\n";
    UF_Template+="  Unit = \"cm\";\n";
    UF_Template+="endfunction";

    if(m_OpenFile->isOpen()){
        int ret = QMessageBox::warning(this, tr("File Open"),
                                       tr("These is already an open file do you want to save it before opening a new one?"),
                                       QMessageBox::Save|QMessageBox::No);
                switch (ret) {
          case QMessageBox::Save:
              slot_saveToFile();
              break;
          case QMessageBox::No:
            ;//do nothing
              break;
          default:
              // should never be reached
              break;
        }
    }
    m_OpenFile->setFileName(fileName);
    m_OpenFile->open(QIODevice::WriteOnly);
    m_OpenFile->setTextModeEnabled(true);
    TE_UserFuncCode->setText(UF_Template);
    Button_Save->setEnabled(true);
}

QString UserFunctionEdit::getFunctionName(UserFunctionEnum usrFunc){
    QFileInfo fileInfo;
    if(usrFunc==F1)fileInfo.setFile(LE_UsrF1->text());
    else if(usrFunc==F2)fileInfo.setFile(LE_UsrF2->text());
    else if(usrFunc==F3)fileInfo.setFile(LE_UsrF3->text());
    else if(usrFunc==F4)fileInfo.setFile(LE_UsrF4->text());
    else if(usrFunc==F5)fileInfo.setFile(LE_UsrF5->text());
    else if(usrFunc==F6)fileInfo.setFile(LE_UsrF6->text());
    else return "";


    QString BaseName=fileInfo.baseName();
   std::cerr<<"BaseName "<<BaseName.toAscii().constData()<<std::endl;

    return fileInfo.baseName();
}

QString UserFunctionEdit::getFunctionPath(UserFunctionEnum usrFunc){
    if(usrFunc==F1)return LE_UsrF1->text();
    else if(usrFunc==F2)return LE_UsrF2->text();
    else if(usrFunc==F3)return LE_UsrF3->text();
    else if(usrFunc==F4)return LE_UsrF4->text();
    else if(usrFunc==F5)return LE_UsrF5->text();
    else if(usrFunc==F6)return LE_UsrF6->text();
    else return "";
}

void UserFunctionEdit::setFunctionPath(UserFunctionEnum usrFunc, QString Path){
    if(usrFunc==F1)LE_UsrF1->setText(Path);
    else if(usrFunc==F2)LE_UsrF2->setText(Path);
    else if(usrFunc==F3)LE_UsrF3->setText(Path);
    else if(usrFunc==F4)LE_UsrF4->setText(Path);
    else if(usrFunc==F5)LE_UsrF5->setText(Path);
    else if(usrFunc==F6)LE_UsrF6->setText(Path);
}
