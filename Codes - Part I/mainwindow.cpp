#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

#include "methods.h"
#include "math.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Numerical Methods");
    ui->label_outVariableA_0->setNum(ui->verticalSlider_variableA_0->value());
    ui->label_outVariableA_1->setNum(ui->verticalSlider_variableA_1->value());
    ui->label_outVariableA_2->setNum(ui->verticalSlider_variableA_2->value());
    ui->label_outVariableA_3->setNum(ui->verticalSlider_variableA_3->value());
    ui->label_outE1->setNum(ui->verticalSlider_e1->value());
    ui->label_outE2->setNum(ui->verticalSlider_e2->value());
    ui->label_outMaxIter->setNum(ui->verticalSlider_maxIter->value());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonBisection_clicked()
{
    //int a = ui->verticalSlider_variableA->value();
    //int e1 = ui->verticalSlider_e1->value();
    //int e2 = ui->verticalSlider_e2->value();
    int maxIter = ui->verticalSlider_maxIter->value();
    float limInf = ui->doubleSpinBox_limiteInferior->value();
    float limSup = ui->doubleSpinBox_limiteSuperior->value();

    if (limSup < limInf) {
        cout << "Avalie os valores do intervalo!" << endl;
        ui->label_error->setText("Check the values of interval");
        return;
    }

    cout << "FindA(): " << findA(ui->verticalSlider_variableA_0->value(),
                                 ui->verticalSlider_variableA_1->value(),
                                 ui->verticalSlider_variableA_2->value(),
                                 ui->verticalSlider_variableA_3->value()) << endl;

    float valueA = findA(ui->verticalSlider_variableA_0->value(),
                        ui->verticalSlider_variableA_1->value(),
                        ui->verticalSlider_variableA_2->value(),
                        ui->verticalSlider_variableA_3->value());

    resultBissecaoFakePoint *results = bisection(ui->doubleSpinBox_limiteInferior->value(),
                                                 ui->doubleSpinBox_limiteSuperior->value(),
                                                 valueA,
                                                 pow(10,ui->verticalSlider_e1->value()),
                                                 ui->verticalSlider_maxIter->value());

    if (results == NULL) {
        cout << "Ponteiro Nulo!" << endl;
        ui->label_error->setText("Check the inputs");
    }

    else {
        dialog = new Dialog(this, false);
        dialog->setWindowTitle("Bisection Method");
        dialog->setDataBisection(results, maxIter);
        //dialog->printDataBisection();
        dialog->show();
    }


}

void MainWindow::on_pushButtonFixedPoint_clicked()
{
    //int a = ui->verticalSlider_variableA->value();
    //int e1 = ui->verticalSlider_e1->value();
    //int e2 = ui->verticalSlider_e2->value();
    int maxIter = ui->verticalSlider_maxIter->value();
    float limInf = ui->doubleSpinBox_limiteInferior->value();
    float limSup = ui->doubleSpinBox_limiteSuperior->value();

    if (limSup < limInf) {
        cout << "Avalie os valores do intervalo!" << endl;
        ui->label_error->setText("Check the values of interval");
        return;
    }

    float valueA = findA(ui->verticalSlider_variableA_0->value(),
                        ui->verticalSlider_variableA_1->value(),
                        ui->verticalSlider_variableA_2->value(),
                        ui->verticalSlider_variableA_3->value());

    resultBissecaoFakePoint *results = fakePoint(valueA,
                                                 ui->doubleSpinBox_limiteInferior->value(),
                                                 ui->doubleSpinBox_limiteSuperior->value(),
                                                 pow(10,ui->verticalSlider_e1->value()),
                                                 pow(10,ui->verticalSlider_e1->value()),
                                                 ui->verticalSlider_maxIter->value());

    if (results == NULL) {
        cout << "Ponteiro Nulo!" << endl;
        ui->label_error->setText("Check the inputs");
    }

    else {
        dialog = new Dialog(this, false);
        dialog->setWindowTitle("Fake Point Method");
        dialog->setDataFakePoint(results, maxIter);
        dialog->show();
    }

}

void MainWindow::on_pushButtonNewtonRaphson_clicked()
{
    //int a = ui->verticalSlider_variableA->value();
    //int e1 = ui->verticalSlider_e1->value();
    //int e2 = ui->verticalSlider_e2->value();
    int maxIter = ui->verticalSlider_maxIter->value();
    float limInf = ui->doubleSpinBox_limiteInferior->value();
    float limSup = ui->doubleSpinBox_limiteSuperior->value();

    if (limSup < limInf) {
        cout << "Avalie os valores do intervalo!" << endl;
        ui->label_error->setText("Check the values of interval");
        return;
    }

    float valueA = findA(ui->verticalSlider_variableA_0->value(),
                        ui->verticalSlider_variableA_1->value(),
                        ui->verticalSlider_variableA_2->value(),
                        ui->verticalSlider_variableA_3->value());

    resultNewtonRaphson *results = newtonRaphson(valueA,
                                                 (limInf+limSup)/2,
                                                 pow(10,ui->verticalSlider_e1->value()),
                                                 pow(10,ui->verticalSlider_e1->value()),
                                                 ui->verticalSlider_maxIter->value());

    if (results == NULL) {
        cout << "Ponteiro Nulo!" << endl;
        ui->label_error->setText("Check the inputs");
    }

    else {
        dialog = new Dialog(this, true);
        dialog->setWindowTitle("NewtonRaphson Method");
        dialog->setDataNewtonRaphson(results, maxIter);
        dialog->show();
    }

}


//Funções de Evento:


void MainWindow::on_verticalSlider_e1_valueChanged(int value)
{
    ui->label_outE1->setNum(value);

}

void MainWindow::on_verticalSlider_e2_valueChanged(int value)
{
    ui->label_outE2->setNum(value);

}

void MainWindow::on_verticalSlider_maxIter_valueChanged(int value)
{
    ui->label_outMaxIter->setNum(value);

}

void MainWindow::on_verticalSlider_variableA_1_valueChanged(int value)
{
    ui->label_outVariableA_1->setNum(value);
}


void MainWindow::on_verticalSlider_variableA_2_valueChanged(int value)
{
    ui->label_outVariableA_2->setNum(value);
}

void MainWindow::on_verticalSlider_variableA_3_valueChanged(int value)
{
    ui->label_outVariableA_3->setNum(value);
}

void MainWindow::on_verticalSlider_variableA_0_valueChanged(int value)
{
    ui->label_outVariableA_0->setNum(value);
}

float MainWindow::findA(int ms, int ls1, int ls2, int ls3) {
    if(ms>=0)
        return ms+(ls1*0.1)+(ls2*0.01)+(ls3*0.001);

    return ms-(ls1*0.1)-(ls2*0.01)-(ls3*0.001);

}
