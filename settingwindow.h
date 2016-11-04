#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = 0);
    ~SettingWindow();

    QComboBox *flowBox;
    QComboBox *databitBox;
    QComboBox *parityBox;
    QComboBox *stopbitBox;

private:
    Ui::SettingWindow *ui;
};

#endif // SETTINGWINDOW_H
