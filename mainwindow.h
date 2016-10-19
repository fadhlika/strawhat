#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCharts/QtCharts>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void plotterHandler();
    void connHandler();
    void readData();

private:
    Ui::MainWindow *ui;
    QHBoxLayout *mainLayout;
    QVBoxLayout *vLayout;
    QHBoxLayout *connLayout;
    QHBoxLayout *sendLayout;
    QTextBrowser *msgTextBrowser;
    QTextEdit *sendTextEdit;
    QPushButton *connButton;
    QPushButton *sendButton;
    QPushButton *refreshButton;
    QPushButton *plotButton;
    QComboBox *portBox;
    QComboBox *baudBox;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *plotMenu;
    QAction *exportAction;
    QAction *exitAction;
    QAction *plotAction;

    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QSerialPort *serialPort;
    QByteArray data;
    QStringList tempList;

    void refreshPorts();
    void plotData(QString str);

    int x = 0;
};

#endif // MAINWINDOW_H
