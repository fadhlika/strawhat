#include "plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    series = new QLineSeries;
    series->setUseOpenGL(true);

    axisX = new QValueAxis;
    axisY = new QValueAxis;
    axisX->setTickCount(10);
    axisY->setTickCount(10);
    axisX->setRange(0, 5);
    axisY->setRange(-5,5);

    chart = new QChart;
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->legend()->hide();
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
    chart->setTheme(QChart::ChartThemeQt);
    chart->setBackgroundRoundness(0);
    chart->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chartView = new QChartView;
    chartView->setChart(chart);
    this->setCentralWidget(chartView);
    this->setAnimated(true);
    this->setWindowTitle("Plot");
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::closeEvent(QCloseEvent *){
    series->clear();
    x = 0;
}

void PlotWindow::plotData(QString str){
    qreal y = str.toFloat();
    *series << QPointF(x, y);
    if(axisX->max() < x) axisX->setMax(x);
    if(axisY->max() < y) axisY->setMax(y);
    x++;
}
