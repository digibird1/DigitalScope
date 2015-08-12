/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */

#ifndef USERFUNCTIONEDIT_H
#define USERFUNCTIONEDIT_H

#include <QWidget>
#include <QtGui>

class UserFunctionEdit : public QWidget
{
    Q_OBJECT
public:
    explicit UserFunctionEdit(QWidget *parent = 0);

signals:

public slots:
    void slot_setF1();
    void slot_setF2();
    void slot_setF3();
    void slot_setF4();
    void slot_setF5();
    void slot_setF6();


    void slot_editF1();
    void slot_editF2();
    void slot_editF3();
    void slot_editF4();
    void slot_editF5();
    void slot_editF6();

private:
    QGridLayout *Grid_Main;
    QGridLayout *Grid_UsrFunc;
    QGroupBox *Group_UsrFuncEdit;
    QPushButton *Button_Save;
    QPushButton *Button_Close;

    QLineEdit *LE_UsrF1;
    QLineEdit *LE_UsrF2;
    QLineEdit *LE_UsrF3;
    QLineEdit *LE_UsrF4;
    QLineEdit *LE_UsrF5;
    QLineEdit *LE_UsrF6;

    QPushButton *Button_SetF1;
    QPushButton *Button_SetF2;
    QPushButton *Button_SetF3;
    QPushButton *Button_SetF4;
    QPushButton *Button_SetF5;
    QPushButton *Button_SetF6;


    QPushButton *Button_EditF1;
    QPushButton *Button_EditF2;
    QPushButton *Button_EditF3;
    QPushButton *Button_EditF4;
    QPushButton *Button_EditF5;
    QPushButton *Button_EditF6;

    QTextEdit *TE_UserFuncCode;

    QFileDialog *FD_SelectFile;

    QFile *m_OpenFile;

};

#endif // USERFUNCTIONEDIT_H
