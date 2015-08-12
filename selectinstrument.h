/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */

/*
 * This widget pops up at the program starts and
 * the user selects the instrument he/she wants to use
 * add adds if needed the adress of the instrument
 */

#ifndef SELECTINSTRUMENT_H
#define SELECTINSTRUMENT_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QtGui>

class SelectInstrument : public QWidget
{
    Q_OBJECT
public:
    explicit SelectInstrument(QWidget *parent = 0);

signals:
    void signal_SelectionDone(QString,QString);

public slots:
    void slot_selectPressed();
private:
    QGridLayout *Grid_Main;
    QGroupBox *Group_InstSel;
    QPushButton *Button_Select;

    QComboBox *ComBox_InstSel;
    QLineEdit *LinEd_InstOption;

};

#endif // SELECTINSTRUMENT_H
