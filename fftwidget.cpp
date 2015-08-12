/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#include "fftwidget.h"

//#include "kiss_fft.h"

#include <mffm/realFFT.H>

#include <qregexp.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qstatusbar.h>
#include <qprinter.h>
#include <qpicture.h>
#include <qpainter.h>
#include <qprintdialog.h>
#include <qwt_counter.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_renderer.h>
#include <qwt_text.h>
#include <qwt_math.h>

#include <cmath>
#include <iostream>


class Zoomer: public QwtPlotZoomer
{
public:
    Zoomer( int xAxis, int yAxis, QWidget *canvas ):
        QwtPlotZoomer( xAxis, yAxis, canvas )
    {
        setTrackerMode( QwtPicker::AlwaysOff );
        setRubberBand( QwtPicker::NoRubberBand );

        // RightButton: zoom out by 1
        // Ctrl+RightButton: zoom out to full size

        setMousePattern( QwtEventPattern::MouseSelect2,
            Qt::RightButton, Qt::ControlModifier );
        setMousePattern( QwtEventPattern::MouseSelect3,
            Qt::RightButton );
    }
};


FFTWidget::FFTWidget(QWidget *parent) :
    QWidget(parent)
{

    AveragePos=0;

    int Offset=50;

    //setFixedSize(1024+2*Offset,800);
    //setFixedSize(640+2*Offset,480);

    grid_Main = new QGridLayout;



    plot = new Plot(this);
   // plot->show();


    const int margin = 5;
    plot->setContentsMargins( margin, margin, margin, 0 );

    d_zoomer[0] = new Zoomer( QwtPlot::xBottom, QwtPlot::yLeft,
            plot->canvas() );
    d_zoomer[0]->setRubberBand( QwtPicker::RectRubberBand );
    d_zoomer[0]->setRubberBandPen( QColor( Qt::green ) );
    d_zoomer[0]->setTrackerMode( QwtPicker::ActiveOnly );
    d_zoomer[0]->setTrackerPen( QColor( Qt::white ) );

  /*  d_zoomer[1] = new Zoomer( QwtPlot::xTop, QwtPlot::yRight,
         plot->canvas() );*/


    d_panner = new QwtPlotPanner( plot->canvas() );
        d_panner->setMouseButton( Qt::MidButton );

        d_picker = new QwtPlotPicker( QwtPlot::xBottom, QwtPlot::yLeft,
            QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
            plot->canvas() );
        d_picker->setStateMachine( new QwtPickerDragPointMachine() );
        d_picker->setRubberBandPen( QColor( Qt::green ) );
        d_picker->setRubberBand( QwtPicker::CrossRubberBand );
        d_picker->setTrackerPen( QColor( Qt::white ) );


        grid_Main->addWidget(plot);



        QToolBar *toolBar = new QToolBar( this );

        QToolButton *btnZoom = new QToolButton( toolBar );
        btnZoom->setText( "Zoom" );
        //btnZoom->setIcon( QPixmap( zoom_xpm ) );
        btnZoom->setCheckable( true );
        btnZoom->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
        toolBar->addWidget( btnZoom );
        connect( btnZoom, SIGNAL( toggled( bool ) ), SLOT( enableZoomMode( bool ) ) );


        QToolButton *btnLogX = new QToolButton( toolBar );
        btnLogX->setText( "LogX" );
        //btnZoom->setIcon( QPixmap( zoom_xpm ) );
        btnLogX->setCheckable( true );
        btnLogX->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
        toolBar->addWidget( btnLogX );
        connect( btnLogX, SIGNAL( toggled( bool ) ), plot,SLOT( setLogX(bool) ) );

        QToolButton *btnLogY = new QToolButton( toolBar );
        btnLogY->setText( "LogY" );
        //btnZoom->setIcon( QPixmap( zoom_xpm ) );
        btnLogY->setCheckable( true );

        btnLogY->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
        toolBar->addWidget( btnLogY );
        connect( btnLogY, SIGNAL( toggled( bool ) ), plot,SLOT( setLogY(bool) ) );

        QToolButton *btnAutoScale = new QToolButton( toolBar );
        btnAutoScale->setText( "AutoScale" );
        //btnZoom->setIcon( QPixmap( zoom_xpm ) );
        btnAutoScale->setCheckable( false );

        btnAutoScale->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
        toolBar->addWidget( btnAutoScale );
        connect( btnAutoScale, SIGNAL( clicked(bool) ), plot,SLOT( autoScale(bool) ) );


   /*     QToolButton *btnExport = new QToolButton( toolBar );
        btnExport->setText( "Export" );
        //btnExport->setIcon( QPixmap( print_xpm ) );
        btnExport->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
        toolBar->addWidget( btnExport );
        connect( btnExport, SIGNAL( clicked() ), SLOT( exportDocument() ) );

        toolBar->addSeparator();*/

  /*       QWidget *hBox = new QWidget( toolBar );

        QHBoxLayout *layout = new QHBoxLayout( hBox );
        layout->setSpacing( 0 );
        layout->addWidget( new QWidget( hBox ), 10 ); // spacer
        layout->addWidget( new QLabel( "Damping Factor", hBox ), 0 );
        layout->addSpacing( 10 );

       QwtCounter *cntDamp = new QwtCounter( hBox );
        cntDamp->setRange( 0.0, 5.0 );
        cntDamp->setSingleStep( 0.01 );
        cntDamp->setValue( 0.0 );

        layout->addWidget( cntDamp, 0 );

        ( void )toolBar->addWidget( hBox );*/

      //  addToolBar( toolBar );

        grid_Main->addWidget(toolBar);
 /*   #ifndef QT_NO_STATUSBAR
        ( void )statusBar();
    #endif*/

        enableZoomMode( false );
        showInfo();

      /*  connect( cntDamp, SIGNAL( valueChanged( double ) ),
            plot, SLOT( setDamp( double ) ) );*/

      /*  connect( d_picker, SIGNAL( moved( const QPoint & ) ),
            SLOT( moved( const QPoint & ) ) );*/
        connect( d_picker, SIGNAL( selected( const QPolygon & ) ),
            SLOT( selected( const QPolygon & ) ) );





        setLayout(grid_Main);

    //Run by default in log mode
    btnLogY->setChecked(true);
    plot->setLogY(true);



//performFFT();
//d_zoomer[0]->setZoomBase();


}

/*
void FFTWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);




    painter.setPen(QPen(Qt::red,1));//fixme will be removed


    QVector<QPointF> test;
    test<<QPoint(100,111);
    test<<QPoint(200,211);

    //painter.drawPolyline(test);


    QVector<QPointF> test2 = FFTWidget::performFFT();


    painter.drawPolyline(test2);



    painter.end();
}
*/


QVector<QPointF> FFTWidget::performFFT(QVector<double> v, double TimeInterval, int Channel){



    int SampleSize=v.size();

    realFFTData fftData(SampleSize);
    realFFT rfft(&fftData);

    for(int i=0;i<SampleSize;i++){
        fftData.in[i]=v[i];
    }

    // forward transform :
    rfft.fwdTransform();

    // Find the power spectrum ...
    fftData.compPowerSpec();




    //fixme potential memory leak
    double *frequency= new double[(SampleSize+1)/2];
    double *amplitude= new double[(SampleSize+1)/2];
    double *average= new double[(SampleSize+1)/2];


    AveragePos++;
    if(AveragePos>=N_AVERAGE)AveragePos=0;


    if(Average_Freq.size()==0){

        AveragePos=0;
        for(int i=0;i<N_AVERAGE;i++){
            double *tmp = new double[(SampleSize+1)/2];

            for(int j=0;j<(SampleSize+1)/2;j++){
                tmp[j]=0;
                //std::cout<<i<<"\t"<<j<<std::endl;
            }
            Average_Freq.append(tmp);
        }
    }


    for(int i=0;i<(SampleSize+1)/2;i++){

        //we can represent with 1024 samples a frequ. range of f_s=1/T
        //The time we an record with our sample rate in the time domain is t=n*T
        //
        //example: t=0.1s, -> T=0.1/1024 -> fs = 1024/0.1
        // each step in the frequency domain gets i/1024
        //the frequency spectra is only half as long as so 1024/2 samples

        //frequency[i]=(double) ((double)i/SampleSize) * 1./(0.1/1024.);

        frequency[i]=(double) ((double)i/SampleSize) * 1./(TimeInterval*1e-3/(SampleSize));

        amplitude[i]=fftData.power_spectrum[i];
    }

    Average_Freq[AveragePos]=amplitude;

    for(int i=0;i<(SampleSize+1)/2;i++){
        average[i]=0;
        for(int j=0;j<N_AVERAGE;j++){
            average[i]+=Average_Freq[j][i];
        }
        average[i]=average[i]/N_AVERAGE;
    }


    plot->showData( frequency, amplitude, SampleSize/2, Channel);
    plot->showData( frequency, average, SampleSize/2, 0);

    if(!d_zoomer[0]->isEnabled()) d_zoomer[0]->setZoomBase();


//kiss_fft code

/*


    int SampleSize=v.size();


    kiss_fft_cpx *In = new kiss_fft_cpx[SampleSize];
    kiss_fft_cpx *Out = new kiss_fft_cpx[SampleSize];

    kiss_fft_cfg mycfg=kiss_fft_alloc(SampleSize,0,NULL,NULL);

    for(int i=0;i<SampleSize;i++){
        In[i].r=v[i];
        In[i].i=0;
    }


    kiss_fft(mycfg,In,Out);


    double *frequency= new double[SampleSize];
    double *amplitude= new double[SampleSize];


    for(int i=0;i<SampleSize/2;i++){

        //we can represent with 1024 samples a frequ. range of f_s=1/T
        //The time we an record with our sample rate in the time domain is t=n*T
        //
        //example: t=0.1s, -> T=0.1/1024 -> fs = 1024/0.1
        // each step in the frequency domain gets i/1024
        //the frequency spectra is only half as long as so 1024/2 samples

        //frequency[i]=(double) ((double)i/SampleSize) * 1./(0.1/1024.);

        frequency[i]=(double) ((double)i/SampleSize) * 1./(TimeInterval*1e-6/SampleSize);

        amplitude[i]=-Out[i].i;
    }

    plot->showData( frequency, amplitude, SampleSize/2, Channel);

    if(!d_zoomer[0]->isEnabled()) d_zoomer[0]->setZoomBase();
*/

/*
    QVector<QPointF> OutPut;



    kiss_fft_cpx In[1024];
    kiss_fft_cpx Out[1024];
    kiss_fft_cpx Out2[1024];

    for(int i=0;i<1024;i++){

        In[i].r=100*sin(2*M_PI/512*i)+50*sin(100*M_PI/512*i)+sin(400*M_PI/512*i);

        std::cout<<"FFT: T "<<i<<"\t"<<In[i].r<<std::endl;

        //double x=-2.+4.*i/1024.;

        //In[i].r=100*cos(2*M_PI*(3*x))*exp(-M_PI*x*x);
        In[i].i=0;

        //if(i>256&&i<768)In[i].r=100;
        //else In[i].r=0;
    }


    kiss_fft_cfg mycfg=kiss_fft_alloc(1024,0,NULL,NULL);


    kiss_fft(mycfg,In,Out);

    kiss_fft(mycfg,Out,Out2);

//    for(int i=0;i<1024;i++){
 //      OutPut<<QPointF((double)i/2.+50,-sqrt(Out[i].i*Out[i].i+Out[i].r*Out[i].r)/100+600);
  //  }

    for(int i=0;i<1024/2;i++){

        std::cout<<"FFT: F "<<i<<"\t"<<Out[i].r<<"\t"<<Out[i].i<<std::endl;

        OutPut<<QPointF((double)i*2+50,Out[i].i/100+600);
    }


//    for(int i=0;i<1024;i++){
//        OutPut<<QPointF((double)i/2+50,-Out2[i].r/400+600);
//    }






    ///return OutPut;

    const int ArraySize = 1024;

    double frequency[ArraySize];
    double amplitude[ArraySize];


    for(int i=0;i<ArraySize/2;i++){

        //we can represent with 1024 samples a frequ. range of f_s=1/T
        //The time we an record with our sample rate in the time domain is t=n*T
        //
        //example: t=0.1s, -> T=0.1/1024 -> fs = 1024/0.1
        // each step in the frequency domain gets i/1024
        //the frequency spectra is only half as long as so 1024/2 samples

        frequency[i]=(double) ((double)i/ArraySize) * 1./(0.1/1024.);
        amplitude[i]=-Out[i].i;
    }

    plot->showData( frequency, amplitude, ArraySize/2 );

    if(!d_zoomer[0]->isEnabled()) d_zoomer[0]->setZoomBase();
*/
    QVector<QPointF> att;
    return att;
}


void FFTWidget::selected( const QPolygon & )
{
    showInfo();
}


void FFTWidget::enableZoomMode( bool on )
{
    if(!d_zoomer[0]->isEnabled()) d_zoomer[0]->setZoomBase();

    d_panner->setEnabled( on );

    d_zoomer[0]->setEnabled( on );
    d_zoomer[0]->zoom( 0 );

 //   d_zoomer[1]->setEnabled( on );
//   d_zoomer[1]->zoom( 0 );

    d_picker->setEnabled( !on );

    showInfo();
}

void FFTWidget::showInfo( QString text )
{
    if ( text == QString::null )
    {
        if ( d_picker->rubberBand() )
            text = "Cursor Pos: Press left mouse button in plot region";
        else
            text = "Zoom: Press mouse button and drag";
    }

/*#ifndef QT_NO_STATUSBAR
    statusBar()->showMessage( text );
#endif*/
}
