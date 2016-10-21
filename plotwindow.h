#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts/QtCharts>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = 0);
    ~PlotWindow();
    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisX;
    QValueAxis *axisY;

    void plotData(QString str);
    int x = 0;
protected:
    void closeEvent(QCloseEvent *);
public slots:


private:
    Ui::PlotWindow *ui;

};

#endif // PLOTWINDOW_H
