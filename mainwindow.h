#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "plotwindow.h"
#include "settingwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void connHandler();
    void readData();
    void sendData();
    void showPlotWindow();
    void exportFile();
    void showSettingWindow();
    void setSerialSetting();

private:
    Ui::MainWindow *ui;

    QVBoxLayout *vLayout;
    QHBoxLayout *connLayout;
    QHBoxLayout *sendLayout;
    QTextBrowser *msgTextBrowser;
    QTextEdit *sendTextEdit;
    QPushButton *connButton;
    QPushButton *sendButton;
    QPushButton *refreshButton;
    QScrollBar *sb;
    QComboBox *portBox;
    QComboBox *baudBox;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *plotMenu;
    QMenu *terminalMenu;
    QAction *exportAction;
    QAction *exitAction;
    QAction *plotAction;
    QAction *clearAction;
    QAction *settingAction;

    QSerialPort *serialPort;
    QByteArray data;
    QString buffer;

    PlotWindow *plotWindow;
    SettingWindow *settingWindow;
    QString filename;

    void refreshPorts();
    void clearText();
    void closeApp();

};

#endif // MAINWINDOW_H
