#include "plot.h"

#include <qwt_math.h>

#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_plot_canvas.h>

#include <cmath>



Plot::Plot(QWidget *parent):QwtPlot( parent )
{    setAutoReplot( false );

     setTitle( "FFT" );

     QwtPlotCanvas *canvas = new QwtPlotCanvas();
     canvas->setBorderRadius( 10 );

     setCanvas( canvas );
     setCanvasBackground( QColor( "MidnightBlue" ) );

     // legend
     QwtLegend *legend = new QwtLegend;
     insertLegend( legend, QwtPlot::BottomLegend );

     // grid
     QwtPlotGrid *grid = new QwtPlotGrid;
     grid->enableXMin( true );
     grid->setMajorPen( Qt::white, 0, Qt::DotLine );
     grid->setMinorPen( Qt::gray, 0 , Qt::DotLine );
     grid->attach( this );

     // axes
     //enableAxis( QwtPlot::yRight );
     setAxisTitle( QwtPlot::xBottom, "Frequency [kHz]" );
     setAxisTitle( QwtPlot::yLeft, "Amplitude " );
     //setAxisTitle( QwtPlot::yRight, "Phase [deg]" );




     setAxisMaxMajor( QwtPlot::xBottom, 6 );
     setAxisMaxMinor( QwtPlot::xBottom, 9 );


      //setAxisScale(QwtPlot::xBottom,0.01,100);

     //setAxisScaleEngine( QwtPlot::xBottom, ScaleEngine_Lin_X );


     // setAxisScaleEngine(QwtPlot::xBottom, new QwtLogScaleEngine );

     // curves


     d_curve1 = new QwtPlotCurve( "Amplitude Ch1" );
     d_curve1->setRenderHint( QwtPlotItem::RenderAntialiased );
     d_curve1->setPen( Qt::red );
     d_curve1->setLegendAttribute( QwtPlotCurve::LegendShowLine );
     d_curve1->setYAxis( QwtPlot::yLeft );
     d_curve1->attach( this );




     m_Channel2=true;

      if(m_Channel2){
         d_curve2 = new QwtPlotCurve( "Amplitude Ch2 " );
         d_curve2->setRenderHint( QwtPlotItem::RenderAntialiased );
         d_curve2->setPen( Qt::magenta );
         d_curve2->setLegendAttribute( QwtPlotCurve::LegendShowLine );
         d_curve2->setYAxis( QwtPlot::yLeft );
         d_curve2->attach( this );
      }

      d_average = new QwtPlotCurve( "Average Ch1" );
      d_average->setRenderHint( QwtPlotItem::RenderAntialiased );
      d_average->setPen( Qt::white );
      d_average->setLegendAttribute( QwtPlotCurve::LegendShowLine );
      d_average->setYAxis( QwtPlot::yLeft );
      d_average->attach( this );


     // marker
     d_marker1 = new QwtPlotMarker();
     d_marker1->setValue( 0.0, 0.0 );
     d_marker1->setLineStyle( QwtPlotMarker::VLine );
     d_marker1->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
     d_marker1->setLinePen(  Qt::green, 0, Qt::DashDotLine );
     d_marker1->attach( this );

      if(m_Channel2){
        /*  d_marker2 = new QwtPlotMarker();
          d_marker2->setValue( 0.0, 0.0 );
          d_marker2->setLineStyle( QwtPlotMarker::VLine );
          d_marker2->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
          d_marker2->setLinePen(  Qt::gray, 0, Qt::DashDotLine );
          d_marker2->attach( this );*/

          /*
         d_marker2 = new QwtPlotMarker();
         d_marker2->setLineStyle( QwtPlotMarker::HLine );
         d_marker2->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
         d_marker2->setLinePen( QColor( 200, 150, 0 ), 0, Qt::DashDotLine );
         d_marker2->setSymbol( new QwtSymbol( QwtSymbol::Diamond,
            QColor( Qt::yellow ), QColor( Qt::green ), QSize( 8, 8 ) ) );
         d_marker2->attach( this );*/
      }

    //setDamp( 0.0 );

     setAutoReplot( true );


}


//
// re-calculate frequency response
//

void Plot::setDamp( double damping )
{
    const bool doReplot = autoReplot();
    setAutoReplot( false );

    const int ArraySize = 1024;

    double frequency[ArraySize];
    double amplitude[ArraySize];


    for(int i=0;i<ArraySize;i++){
        frequency[i]=i;
        amplitude[i]=100*std::sin(2*M_PI*i/1024);
    }


    //double phase[ArraySize];

    // build frequency vector with logarithmic division
 /*   logSpace( frequency, ArraySize, 0.01, 100 );

    int i3 = 1;
    double fmax = 1;
    double amax = -1000.0;

    for ( int i = 0; i < ArraySize; i++ )
    {
        double f = frequency[i];
       //const ComplexNumber g =
       //     ComplexNumber( 1.0 ) / ComplexNumber( 1.0 - f * f, 2.0 * damping * f );

        amplitude[i] = 20.0 * log10( qSqrt( g.real() * g.real() + g.imag() * g.imag() ) );
        //phase[i] = qAtan2( g.imag(), g.real() ) * ( 180.0 / M_PI );

        if ( ( i3 <= 1 ) && ( amplitude[i] < -3.0 ) )
            i3 = i;
        if ( amplitude[i] > amax )
        {
            amax = amplitude[i];
            fmax = frequency[i];
        }

    }

    double f3 = frequency[i3] - ( frequency[i3] - frequency[i3 - 1] )
        / ( amplitude[i3] - amplitude[i3 -1] ) * ( amplitude[i3] + 3 );
*/
    //showPeak( fmax, amax );
    //show3dB( f3 );
 //   showData( frequency, amplitude, ArraySize );

    setAutoReplot( doReplot );

    replot();
}

void Plot::showData( const double *frequency, const double *amplitude, int count, int Channel )
{

    const bool doReplot = autoReplot();
    setAutoReplot( false );
    if(Channel==0)d_average->setSamples( frequency, amplitude, count );
    if(Channel==1)d_curve1->setSamples( frequency, amplitude, count );
    if(Channel==2)d_curve2->setSamples( frequency, amplitude, count );
    setAutoReplot( doReplot );


    //d_curve2->setSamples( frequency, phase, count );

}


void Plot::setLogX(bool on){

    if(!on){

        setAxisScaleEngine( QwtPlot::xBottom, new QwtLinearScaleEngine );
        setAxisAutoScale(QwtPlot::xBottom);
    }
    else{

        setAxisScaleEngine( QwtPlot::xBottom, new QwtLogScaleEngine );
        setAxisScale(QwtPlot::xBottom,0.01,d_curve1->maxXValue()*2);


    }

}

void Plot::setLogY(bool on){

    if(!on){

        setAxisScaleEngine( QwtPlot::yLeft, new QwtLinearScaleEngine );
        setAxisAutoScale(QwtPlot::yLeft);

    }
    else{

        setAxisScaleEngine( QwtPlot::yLeft, new QwtLogScaleEngine );
        setAxisScale(QwtPlot::yLeft,d_average->minYValue(),d_average->maxYValue()*2);
    }

}
