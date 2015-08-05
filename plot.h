/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>
#include <qwt_scale_engine.h>

class QwtPlotCurve;
class QwtPlotMarker;

class Plot : public QwtPlot
{

    Q_OBJECT
public:
    Plot(QWidget *parent);
    void showData( const double *frequency, const double *amplitude, int count, int Channel=1 );

private:
    QwtPlotCurve *d_curve1;
    QwtPlotCurve *d_curve2;
    QwtPlotCurve *d_average;
    QwtPlotMarker *d_marker1;
    QwtPlotMarker *d_marker2;

    bool m_Channel2;


public Q_SLOTS:
    void setDamp( double damping );

    void setLogX(bool on);
    void setLogY(bool on);
};

#endif // PLOT_H
