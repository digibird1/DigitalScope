#ifndef FFTWIDGET_H
#define FFTWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>

#include "plot.h"

class QwtPlotZoomer;
class QwtPlotPicker;
class QwtPlotPanner;
class Plot;
class QPolygon;


#include <iostream>

#define N_AVERAGE 50

class FFTWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FFTWidget(QWidget *parent = 0);

    QVector<QPointF> performFFT(QVector<double> v, double TimeInterval, int Channel=1);
    
signals:
    
public slots:

private Q_SLOTS:
    //void moved( const QPoint & );
    void selected( const QPolygon & );

    void enableZoomMode( bool );


protected:
    //void paintEvent(QPaintEvent *event);

private:
    Plot *plot;

    QGridLayout *grid_Main;

    void showInfo( QString text = QString::null );

    QwtPlotZoomer *d_zoomer[2];
    QwtPlotPicker *d_picker;
    QwtPlotPanner *d_panner;
    QVector<double *> Average_Freq;
    int AveragePos;//Hold the positin of the latest entry
    
};

#endif // FFTWIDGET_H
