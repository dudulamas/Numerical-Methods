#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QTableWidget"
#include "result.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, bool isNewtonRaphson = false);
    ~Dialog();

    void setHeaders(bool isNewtonRapshon);
    void setDataBisection(resultBissecaoFakePoint *results, int maxIter);
    void setDataFakePoint(resultBissecaoFakePoint *results, int maxIter);
    void setDataNewtonRaphson(resultNewtonRaphson *results, int maxIter);

private:
    Ui::Dialog *ui;
    QTableWidget *tableBisection;
    QStringList tableHeader;
    resultBissecaoFakePoint *dataBisection;
    resultBissecaoFakePoint *dataFakePoint;
    resultNewtonRaphson *dataNewtonRaphson;

    void mountTable(resultBissecaoFakePoint *results, int maxIter);
    void mountTableNP(resultNewtonRaphson *results, int maxIter);
};

#endif // DIALOG_H
