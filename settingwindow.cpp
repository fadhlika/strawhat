#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);

    QLabel *flowLabel = new QLabel;
    flowLabel->setText("Flow Control :");
    flowBox = new QComboBox;
    flowBox->addItem("None");
    flowBox->addItem("Hardware");
    flowBox->addItem("Software");
    flowBox->setMaximumWidth(75);
    flowBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *parityLabel = new QLabel;
    parityLabel->setText("Parity :");
    parityBox = new QComboBox;
    parityBox->addItem("None");
    parityBox->addItem("Even");
    parityBox->addItem("Odd");
    parityBox->addItem("Space");
    parityBox->addItem("Mark");
    parityBox->setMaximumWidth(75);
    parityBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *stopbitLabel = new QLabel;
    stopbitLabel->setText("Stop Bit :");
    stopbitBox = new QComboBox;
    stopbitBox->addItem("1");
    stopbitBox->addItem("1.5");
    stopbitBox->addItem("2");
    stopbitBox->setMaximumWidth(75);
    stopbitBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *databitLabel = new QLabel;
    databitLabel->setText("Data Bit :");
    databitBox = new QComboBox;
    databitBox->addItem("5");
    databitBox->addItem("6");
    databitBox->addItem("7");
    databitBox->addItem("8");
    databitBox->setMaximumWidth(75);
    databitBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->vLayout->addWidget(flowLabel);
    ui->vLayout->addWidget(flowBox);
    ui->vLayout->addWidget(parityLabel);
    ui->vLayout->addWidget(parityBox);
    ui->vLayout->addWidget(stopbitLabel);
    ui->vLayout->addWidget(stopbitBox);
    ui->vLayout->addWidget(databitLabel);
    ui->vLayout->addWidget(databitBox);


}

SettingWindow::~SettingWindow()
{
    delete ui;
}
