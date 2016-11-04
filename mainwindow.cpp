#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), plotWindow()
{
    ui->setupUi(this);

    plotWindow = new PlotWindow;
    settingWindow = new SettingWindow;
    buffer = "";

    menuBar = new QMenuBar;

    fileMenu = new QMenu;
    fileMenu->setTitle("File");

    plotMenu = new QMenu;
    plotMenu->setTitle("Plot");

    terminalMenu = new QMenu;
    terminalMenu->setTitle("Terminal");

    exportAction = new QAction;
    exportAction->setText("Export");
    exitAction = new QAction;
    exitAction->setText("Exit");
    plotAction = new QAction;
    plotAction->setText("Plotter");
    clearAction = new QAction;
    clearAction->setText("Clear");
    settingAction = new QAction;
    settingAction->setText("Settings");


    fileMenu->addAction(exportAction);
    fileMenu->addAction(settingAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);


    plotMenu->addAction(plotAction);
    terminalMenu->addAction(clearAction);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(terminalMenu);
    menuBar->addMenu(plotMenu);

    portBox = new QComboBox;
    portBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    baudBox = new QComboBox;
    baudBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    baudBox->addItem("9600");
    baudBox->addItem("19200");
    baudBox->addItem("115200");

    refreshButton = new QPushButton;
    refreshButton->setText("Refresh");
    refreshButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshPorts);

    connButton = new QPushButton;
    connButton->setText("Connect");
    connButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    connLayout = new QHBoxLayout;
    connLayout->addWidget(portBox);
    connLayout->addWidget(baudBox);
    connLayout->addStretch(100);
    connLayout->addWidget(refreshButton);
    connLayout->addWidget(connButton);
    connLayout->setMargin(0);

    QWidget *connWidgets = new QWidget;
    connWidgets->setLayout(connLayout);

    msgTextBrowser = new QTextBrowser;
    msgTextBrowser->setReadOnly(true);
    msgTextBrowser->setText("");
    connButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    msgTextBrowser = new QTextBrowser;

    vLayout = new QVBoxLayout;
    vLayout->addWidget(connWidgets);
    vLayout->addWidget(msgTextBrowser);

    sendTextEdit = new QTextEdit;
    sendTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sendTextEdit->setMaximumHeight(23);
    sendTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    sendButton = new QPushButton;
    sendButton->setText("Send");
    sendButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::sendData);

    sendLayout = new QHBoxLayout;
    sendLayout->addWidget(sendTextEdit);
    sendLayout->addWidget(sendButton,0,Qt::AlignRight);
    sendLayout->setMargin(0);

    QWidget *sendWidgets = new QWidget;
    sendWidgets->setLayout(sendLayout);
    vLayout->addWidget(sendWidgets);

    QWidget *monitorWidgets = new QWidget;
    monitorWidgets->setLayout(vLayout); 

    this->setMenuBar(menuBar);
    QWidget *central = new QWidget;
    central->setLayout(vLayout);
    this->setCentralWidget(central);
    this->setAnimated(true);

    this->setWindowTitle("Strawhat");

    connect(connButton, &QPushButton::clicked, this, &MainWindow::connHandler);
    connect(plotAction, &QAction::triggered, this, &MainWindow::showPlotWindow);
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearText);
    connect(exitAction, &QAction::triggered, this, &MainWindow::closeApp);
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportFile);
    connect(settingAction, &QAction::triggered, this, &MainWindow::showSettingWindow);

    connect(settingWindow, &QDialog::accepted, this, &MainWindow::setSerialSetting);

    QScrollBar *sb = msgTextBrowser->verticalScrollBar();
    sb->setValue(sb->maximum());

    serialPort = new QSerialPort;
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
    refreshPorts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *){
    plotWindow->close();
}

void MainWindow::showPlotWindow(){
    plotWindow->show();
}

void MainWindow::refreshPorts(){
    portBox->clear();
    foreach(const QSerialPortInfo &port, QSerialPortInfo::availablePorts()){
        portBox->addItem(port.portName());
    }
}

void MainWindow::connHandler(){
    qint32 baud;
    switch(baudBox->currentText().toInt()){
        case 9600   : baud = QSerialPort::Baud9600;
                      break;
        case 19200  : baud = QSerialPort::Baud19200;
                      break;
        case 115200 : baud = QSerialPort::Baud115200;
                      break;
    }

    if(!serialPort->isOpen() && portBox->currentText() != ""){
        serialPort->setPortName(portBox->currentText());
        serialPort->setBaudRate(baud);
        serialPort->open(QIODevice::ReadWrite);
        connButton->setText("Disconnect");
        qDebug() << "Opened : Port =" << portBox->currentText()
                     <<" Baud =" << baudBox->currentText();
    } else if(serialPort->isOpen()){
        serialPort->close();
        connButton->setText("Connect");
        qDebug() << "Closed : Port =" << portBox->currentText()
                 <<" Baud =" << baudBox->currentText();
    } else {
        qDebug() << "No device available";
    }
}

void MainWindow::readData(){
    QStringList buffList = buffer.split("\r\n");
    if(buffList.length() < 2)
    {
        data = serialPort->readAll();
        buffer += QString::fromStdString(data.toStdString());
    } else {
        msgTextBrowser->insertPlainText(buffList[0]);
        if(buffer.contains("\n")) msgTextBrowser->insertPlainText("\n");
        sb = msgTextBrowser->verticalScrollBar();
        sb->setValue(sb->maximum());
        if(plotWindow->isVisible()) plotWindow->plotData(buffList[0]);
        qDebug() << buffList;
        buffer = "";
    }
}

void MainWindow::clearText(){
    msgTextBrowser->setText("");
}

void MainWindow::closeApp(){
    this->close();
}

void MainWindow::exportFile(){
    filename = QFileDialog::getSaveFileName(this, tr("Save file as"), "C:/text.txt", tr("Texts (*.txt)"));
    QFile file(filename);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << msgTextBrowser->toPlainText();
        file.close();
    }
}

void MainWindow::sendData(){
    serialPort->write(sendTextEdit->toPlainText().toLocal8Bit());
    sendTextEdit->setText("");
}

void MainWindow::showSettingWindow(){
    settingWindow->exec();
}

void MainWindow::setSerialSetting(){
    qint32 parity = settingWindow->parityBox->currentText().toInt();
}
