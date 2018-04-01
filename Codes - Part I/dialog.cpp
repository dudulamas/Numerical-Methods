#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>

using namespace std;

Dialog::Dialog(QWidget *parent, bool isNewtonRaphson) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    setHeaders(isNewtonRaphson);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setHeaders(bool isNewtonRaphson) {
    QStringList headers;
    if (isNewtonRaphson) {
        headers << "x" << "f(x)" << "proximo x" << "f(proximo x)" << "x - xprox";
        ui->tableWidget->setColumnCount(5);
    }
    else {
        headers << "i1" << "f(i1)" << "i2" << "f(i2)" << "midpoint" << "f(midpoint)" << "i1-i2";
        ui->tableWidget->setColumnCount(7);
    }

    ui->tableWidget->setHorizontalHeaderLabels(headers);

}

void Dialog::setDataBisection(resultBissecaoFakePoint *results, int maxIter) {
    dataBisection = results;
    mountTable(dataBisection, maxIter);
}

void Dialog::setDataFakePoint(resultBissecaoFakePoint *results, int maxIter) {
    dataFakePoint = results;
    mountTable(dataFakePoint, maxIter);
}

void Dialog::setDataNewtonRaphson(resultNewtonRaphson *results, int maxIter) {
    dataNewtonRaphson = results;
    mountTableNP(dataNewtonRaphson, maxIter);
}

void Dialog::mountTable(resultBissecaoFakePoint *results, int maxIter) {
    int i = 0, row = ui->tableWidget->rowCount();
    cout << "Row:" << row << results[i].hasNext << endl;

    while(results[i].hasNext == true and i < maxIter) {
        ui->tableWidget->insertRow(row);
        //ui->tableWidget->setItem(row,0, new QTableWidgetItem(QString::number(results[i].round)));
        ui->tableWidget->setItem(row,0, new QTableWidgetItem(QString::number(results[i].i1)));
        ui->tableWidget->setItem(row,1, new QTableWidgetItem(QString::number(results[i].f1)));
        ui->tableWidget->setItem(row,2, new QTableWidgetItem(QString::number(results[i].i2)));
        ui->tableWidget->setItem(row,3, new QTableWidgetItem(QString::number(results[i].f2)));
        ui->tableWidget->setItem(row,4, new QTableWidgetItem(QString::number(results[i].midpoint)));
        ui->tableWidget->setItem(row,5, new QTableWidgetItem(QString::number(results[i].fmidpoint)));
        ui->tableWidget->setItem(row,6, new QTableWidgetItem(QString::number(results[i].absolutValueOfInterval)));

        cout << "Round: " << results[i].round << " " << results[i].i1 << " " << results[i].f1 <<
                   " " << results[i].i2 << " " << results[i].f2 << " " << results[i].midpoint <<
                   " " << results[i].fmidpoint << results[i].absolutValueOfInterval << " " << results[i].hasNext << endl;
        row++;
        i++;
    }

}

void Dialog::mountTableNP(resultNewtonRaphson *results, int maxIter) {
    int i = 0, row = ui->tableWidget->rowCount();

    while(results[i].hasNext == true and i< maxIter) {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row,0, new QTableWidgetItem(QString::number(results[i].x)));
        ui->tableWidget->setItem(row,1, new QTableWidgetItem(QString::number(results[i].fx)));
        ui->tableWidget->setItem(row,2, new QTableWidgetItem(QString::number(results[i].xprox)));
        ui->tableWidget->setItem(row,3, new QTableWidgetItem(QString::number(results[i].fxprox)));
        ui->tableWidget->setItem(row,4, new QTableWidgetItem(QString::number(results[i].xmenusxprox)));

        row++;
        i++;
    }

}

