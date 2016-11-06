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

    QVBoxLayout *serialVLayout = new QVBoxLayout;

    serialVLayout->addWidget(flowLabel);
    serialVLayout->addWidget(flowBox);
    serialVLayout->addWidget(parityLabel);
    serialVLayout->addWidget(parityBox);
    serialVLayout->addWidget(stopbitLabel);
    serialVLayout->addWidget(stopbitBox);
    serialVLayout->addWidget(databitLabel);
    serialVLayout->addWidget(databitBox);

    QGroupBox *serialGroup = new QGroupBox(tr("Port Configuration"));
    serialGroup->setLayout(serialVLayout);

    ui->hLayout->addWidget(serialGroup);

    QCheckBox *returnCheck = new QCheckBox(tr("/r"));
    QCheckBox *newlineCheck = new QCheckBox(tr("/n"));
    QCheckBox *localEchoCheck = new QCheckBox(tr("Local Echo"));

    QVBoxLayout *transmitVLayout = new QVBoxLayout;
    transmitVLayout->addWidget(returnCheck);
    transmitVLayout->addWidget(newlineCheck);
    transmitVLayout->addWidget(localEchoCheck);

    QGroupBox *transmitGroup = new QGroupBox(tr("Transmitted Text"));
    transmitGroup->setLayout(transmitVLayout);

    ui->hLayout->addWidget(transmitGroup);

    this->setWindowTitle("Settings");
}

SettingWindow::~SettingWindow()
{
    delete ui;
}
