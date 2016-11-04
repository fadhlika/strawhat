#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);

    flowBox = new QComboBox;
    flowBox->addItem("None");
    flowBox->addItem("Hardware");
    flowBox->addItem("Software");

    parityBox = new QComboBox;
    parityBox->addItem("None");
    parityBox->addItem("Even");
    parityBox->addItem("Odd");
    parityBox->addItem("Space");
    parityBox->addItem("Mark");

    stopbitBox = new QComboBox;
    stopbitBox->addItem("1");
    stopbitBox->addItem("1.5");
    stopbitBox->addItem("2");

    databitBox = new QComboBox;
    databitBox->addItem("5");
    databitBox->addItem("6");
    databitBox->addItem("7");
    databitBox->addItem("8");

    ui->vLayout->addWidget(flowBox);
    ui->vLayout->addWidget(parityBox);
    ui->vLayout->addWidget(stopbitBox);
    ui->vLayout->addWidget(databitBox);

    this->setFixedSize(320, 240);
}

SettingWindow::~SettingWindow()
{
    delete ui;
}
