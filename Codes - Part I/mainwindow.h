#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "result.h"

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
    void on_pushButtonBisection_clicked();

    void on_pushButtonFixedPoint_clicked();

    void on_pushButtonNewtonRaphson_clicked();

    void on_verticalSlider_e1_valueChanged(int value);

    void on_verticalSlider_e2_valueChanged(int value);

    void on_verticalSlider_maxIter_valueChanged(int value);

    float findA(int ms, int ls1, int ls2, int ls3);

    void on_verticalSlider_variableA_1_valueChanged(int value);

    void on_verticalSlider_variableA_2_valueChanged(int value);

    void on_verticalSlider_variableA_3_valueChanged(int value);

    void on_verticalSlider_variableA_0_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Dialog *dialog;
};

#endif // MAINWINDOW_H
