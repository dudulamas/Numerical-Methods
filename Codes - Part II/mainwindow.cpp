#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_numberDisplacements_out->setNum(ui->horizontalSlider_numberDisplacements->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_callInputMatrix_clicked()
{
    int numberDisplacements = ui->horizontalSlider_numberDisplacements->value();
    cout << numberDisplacements << endl;

    if (numberDisplacements > 0) {
        cout << "call matrix Dialog" << endl;
        dialog = new Dialog(this, numberDisplacements);
        dialog->setWindowTitle("Matrix Dialog");
        dialog->show();

    }

    else {
        ui->label_error->setText("Please, check the value of displacements.");
    }

}


void MainWindow::on_horizontalSlider_numberDisplacements_valueChanged(int value)
{
    ui->label_numberDisplacements_out->setNum(value);

}
