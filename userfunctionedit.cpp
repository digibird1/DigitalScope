/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */

#include "userfunctionedit.h"

UserFunctionEdit::UserFunctionEdit(QWidget *parent) :
    QWidget(parent)
{

    Grid_Main = new QGridLayout;
    Grid_UsrFunc = new QGridLayout;
    Group_UsrFuncEdit = new QGroupBox("User Functions");
    Button_Save = new QPushButton("Save");
    Button_Close = new QPushButton("Close");

    Button_SetF1 = new QPushButton("Set");
    Button_SetF2 = new QPushButton("Set");
    Button_SetF3 = new QPushButton("Set");
    Button_SetF4 = new QPushButton("Set");
    Button_SetF5 = new QPushButton("Set");
    Button_SetF6 = new QPushButton("Set");


    Button_EditF1 = new QPushButton("Edit");
    Button_EditF2 = new QPushButton("Edit");
    Button_EditF3 = new QPushButton("Edit");
    Button_EditF4 = new QPushButton("Edit");
    Button_EditF5 = new QPushButton("Edit");
    Button_EditF6 = new QPushButton("Edit");

    LE_UsrF1= new QLineEdit("F1");
    LE_UsrF2= new QLineEdit("F2");
    LE_UsrF3= new QLineEdit("F3");
    LE_UsrF4= new QLineEdit("F4");
    LE_UsrF5= new QLineEdit("F5");
    LE_UsrF6= new QLineEdit("F6");

    LE_UsrF1->setDisabled(true);
    LE_UsrF2->setDisabled(true);
    LE_UsrF3->setDisabled(true);
    LE_UsrF4->setDisabled(true);
    LE_UsrF5->setDisabled(true);
    LE_UsrF6->setDisabled(true);

    TE_UserFuncCode= new QTextEdit;


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
    Grid_Main->addWidget(TE_UserFuncCode,0,1);

    Grid_Main->addWidget(Button_Close,1,0);
    Grid_Main->addWidget(Button_Save,1,1);

    setLayout(Grid_Main);

    connect(Button_SetF1,SIGNAL(clicked()),this,SLOT(slot_setF1()));
    connect(Button_SetF2,SIGNAL(clicked()),this,SLOT(slot_setF2()));
    connect(Button_SetF3,SIGNAL(clicked()),this,SLOT(slot_setF3()));
    connect(Button_SetF4,SIGNAL(clicked()),this,SLOT(slot_setF4()));
    connect(Button_SetF5,SIGNAL(clicked()),this,SLOT(slot_setF5()));
    connect(Button_SetF6,SIGNAL(clicked()),this,SLOT(slot_setF6()));

/*
    connect(Button_EditF1,SIGNAL(clicked()),this,SLOT(slot_editF1()));
    connect(Button_EditF2,SIGNAL(clicked()),this,SLOT(slot_editF2()));
    connect(Button_EditF3,SIGNAL(clicked()),this,SLOT(slot_editF3()));
    connect(Button_EditF4,SIGNAL(clicked()),this,SLOT(slot_editF4()));
    connect(Button_EditF5,SIGNAL(clicked()),this,SLOT(slot_editF5()));
    connect(Button_EditF6,SIGNAL(clicked()),this,SLOT(slot_editF6()));
*/
}

void UserFunctionEdit::slot_setF1(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("Image Files (*.m)"));
    if(fileName!="")LE_UsrF1->setText(fileName);
}

void UserFunctionEdit::slot_setF2(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("Image Files (*.m)"));
    if(fileName!="")LE_UsrF2->setText(fileName);
}

void UserFunctionEdit::slot_setF3(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("Image Files (*.m)"));
    if(fileName!="")LE_UsrF3->setText(fileName);
}

void UserFunctionEdit::slot_setF4(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("Image Files (*.m)"));
    if(fileName!="")LE_UsrF4->setText(fileName);
}

void UserFunctionEdit::slot_setF5(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("Image Files (*.m)"));
    if(fileName!="")LE_UsrF5->setText(fileName);
}

void UserFunctionEdit::slot_setF6(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select User Function"), "UsrScripts", tr("Image Files (*.m)"));
    if(fileName!="")LE_UsrF6->setText(fileName);
}

void UserFunctionEdit::slot_editF1(){
    //open the file and save a pointer to the file which is open
    //use the pointer together with the save button
    //load the text into the text edit

    m_OpenFile = new QFile(LE_UsrF1->text());
    if(m_OpenFile==NULL){
        error
    }

}
