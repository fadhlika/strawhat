#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), plotWindow()
{
    ui->setupUi(this);
    plotWindow = new PlotWindow;
    buffer = "";

    menuBar = new QMenuBar;

    fileMenu = new QMenu;
    fileMenu->setTitle("File");

    plotMenu = new QMenu;
    plotMenu->setTitle("Plot");

    exportAction = new QAction;
    exportAction->setText("Export");
    exitAction = new QAction;
    exitAction->setText("Exit");
    plotAction = new QAction;
    plotAction->setText("Plotter");

    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    plotMenu->addAction(plotAction);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(plotMenu);

    portBox = new QComboBox;
    portBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    baudBox = new QComboBox;
    baudBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    baudBox->addItem("9600");
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

    sendButton = new QPushButton;
    sendButton->setText("Send");
    sendButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

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
    refreshPorts();
    qint32 baud;
    switch(baudBox->currentText().toInt()){
        case 9600   : baud = QSerialPort::Baud9600;
                      break;
        case 112500 : baud = QSerialPort::Baud115200;
                      break;
    }

    if(!serialPort->isOpen() && portBox->currentText() != ""){
        serialPort->setPortName(portBox->currentText());
        serialPort->setBaudRate(baud);
        serialPort->open(QIODevice::ReadWrite);
        connButton->setText("Disconnect");
        qDebug() << "Opened : Port =" << portBox->currentText()
                     <<" Baud =" << baudBox->currentText().toInt();
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
        data = serialPort->readLine();
        buffer += QString::fromStdString(data.toStdString());
    } else {
        msgTextBrowser->insertPlainText(buffList[0]);
        if(buffer.contains("\n")) msgTextBrowser->insertPlainText("\n");
        QScrollBar *sb = msgTextBrowser->verticalScrollBar();
        sb->setValue(sb->maximum());
        if(plotWindow->isVisible()) plotWindow->plotData(buffList[0]);
        qDebug() << buffList;
        buffer = "";
    }
}
