#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPlainTextEdit>
#include <ldp_solucao.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0,  int numberDisplacements = 2);
    ~Dialog();

private slots:
    void on_btn_calculate_LU_clicked();

    void on_btn_calculate_LDP_clicked();

    void on_matrix_cellChanged(int row, int column);


private:
    Ui::Dialog *ui;
    //QPlainTextEdit* inputs;
    int* numberDisplacements;
    int* count;
    float** A;
    float* F;

    void mountDialog(int numberDisplacements);

    void mountHeader(int numberDisplacements);

    bool capturateInputs();

    void mountLUR(int tamanho, float** matrizL, float** matrizU,float *d);

    void mountLDP(LDP_Solucao solucao);

};

#endif // DIALOG_H
