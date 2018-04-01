#include "dialog.h"
#include "ui_dialog.h"
#include "methods.h"

#include <matriz.h>
#include "operacoes.h"
#include "lu_solucao.h"
#include "ldp_solucao.h"

#include <QDebug>
#include <QString>

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;


Dialog::Dialog(QWidget *parent, int numberDisplacements) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //Diminuindo o tamanho da tela, para poder esconder os campos em branco da L, U e D:
    setGeometry(geometry().x(),geometry().y(),geometry().width(), geometry().height()/2 + 20);

    //Escondendo as Tabelas L, U e D. As mostraremos somente se necessário e quando os cálculos forem concluídos:
    ui->matrixL->hide();
    ui->matrixU->hide();
    ui->matrixP->hide();

    //Montando a interface do usuário
    mountDialog(numberDisplacements);
}

Dialog::~Dialog()
{
    delete ui;
}

// FUNÇÃO PARA MONTAR AS CONFIGURAÇÕES INICIAIS
void Dialog::mountDialog(int numberDisplacements) {
    //int n = numberDisplacements;
    //Dialog::numberDisplacements = &n;
    //cout << "Numero de inputs: " << *Dialog::numberDisplacements << endl;

    //Criando o numero de linhas e colunas da matriz de entrada de dados e das matrizes L,U&D,P:
    ui->matrix->setRowCount(numberDisplacements);
    ui->matrix->setColumnCount(numberDisplacements + 1);
    ui->matrixL->setRowCount(numberDisplacements);
    ui->matrixL->setColumnCount(numberDisplacements);
    ui->matrixU->setRowCount(numberDisplacements);
    ui->matrixU->setColumnCount(numberDisplacements);
    ui->matrixP->setRowCount(numberDisplacements);
    ui->matrixP->setColumnCount(numberDisplacements);
    ui->matrix_results->setColumnCount(numberDisplacements);
    ui->matrix_results->setRowCount(1);

    //Montando os headers:
    mountHeader(numberDisplacements);
    ui->matrix->setShowGrid(false); //Evitando mostrar os cortes das celulas;

    //A proxima linha e os dois laços serão ajustes nas largura da tabela:
    ui->matrix->horizontalHeader()->setStretchLastSection(true);
    ui->matrixL->horizontalHeader()->setStretchLastSection(true);
    ui->matrixU->horizontalHeader()->setStretchLastSection(true);
    ui->matrixP->horizontalHeader()->setStretchLastSection(true);
    ui->matrix_results->horizontalHeader()->setStretchLastSection(true);

    //Definindo a largura e altura da tabela de entrada de dados:
    for (int i = 0; i < ui->matrix->columnCount(); i++)
        ui->matrix->setColumnWidth(i, ui->matrix->width()/ui->matrix->columnCount());

    for (int i = 0; i < ui->matrix->rowCount(); i++)
        ui->matrix->setRowHeight(i, ui->matrix->height()/ui->matrix->rowCount());


    // Agora, fazendo o mesmo para as outras matrizes de apresentação de dados:
    for (int i = 0; i < numberDisplacements; i++) {
        ui->matrixL->setColumnWidth(i, ui->matrixL->width()/numberDisplacements);
        ui->matrixU->setColumnWidth(i, ui->matrixU->width()/numberDisplacements);
        ui->matrixP->setColumnWidth(i, ui->matrixP->width()/numberDisplacements);
        ui->matrix_results->setColumnWidth(i, ui->matrix_results->width()/numberDisplacements);

    }

    for (int i = 0; i < numberDisplacements; i++) {
        ui->matrixL->setRowHeight(i, ui->matrixL->height()/numberDisplacements);
        ui->matrixU->setRowHeight(i, ui->matrixU->height()/numberDisplacements);
        ui->matrixP->setRowHeight(i, ui->matrixP->height()/numberDisplacements);
        ui->matrix_results->setRowHeight(i, ui->matrix_results->height()/1);

    }

    //Escondendo os headers verticais;
    ui->matrix->verticalHeader()->hide();
    ui->matrixL->verticalHeader()->hide();
    ui->matrixU->verticalHeader()->hide();
    ui->matrixP->verticalHeader()->hide();
    ui->matrix_results->verticalHeader()->hide();

    //Escondendo os horizontais:
    ui->matrixL->horizontalHeader()->hide();
    ui->matrixU->horizontalHeader()->hide();
    ui->matrixP->horizontalHeader()->hide();
    ui->matrix_results->horizontalHeader()->hide();




}

// FUNÇÃO PARA MONTAR O HEADER DA MATRIZ DE ENTRADA:
void Dialog::mountHeader(int numberDisplacements) {
    QStringList headers;
    QString header[] = {"d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "f"};


    for (int i=0; i<numberDisplacements; i++)
        headers << header[i];

    headers << header[8];
    ui->matrix->setHorizontalHeaderLabels(headers);

}

// FUNÇÃO PARA VARRER A MATRIZ DE ENTRADA, PEGANDO OS SEUS VALORES
bool Dialog::capturateInputs() {
    QTableWidgetItem *item;
    QString itemString;
    float valueCell;

    //cout << ui->matrix->rowCount() << " " << ui->matrix->columnCount() << endl;

    //Somando 1 por causa do vetor F:
    A = (float**) malloc(ui->matrix->rowCount() * sizeof(float*));
    for (int i=0; i<ui->matrix->rowCount(); i++)
        A[i] = (float*) malloc(ui->matrix->rowCount() * sizeof(float));

    F = (float*) malloc(ui->matrix->rowCount() * sizeof(float));
    //float A[ui->matrix->rowCount()][ui->matrix->columnCount()];
    //float F[ui->matrix->rowCount()];

    //Capturando as entradas do usuário:
    for (int i=0; i < ui->matrix->rowCount(); i++) {
        for (int j=0; j<ui->matrix->columnCount(); j++) {

            item = ui->matrix->item(i,j);

            if(item) {
                itemString = item->text();
                //cout << itemString.toUtf8().constData() << endl;
                valueCell = itemString.toFloat();
                //cout << i << " - " << j << ": " << valueCell << endl;

                if(j==ui->matrix->columnCount()-1) {
                     //Tratando da ultima coluna, ou da coluna F:
                     F[i] = valueCell;
                 }

                else {
                    //Se não, trata-se da coluna dos coeficientes;
                    A[i][j] = valueCell;
                }


            }

            else {

                if(j==ui->matrix->columnCount()-1) {
                     //Tratando da ultima coluna, ou da coluna F:
                     F[i] = 0;
                 }

                else {
                    //Se não, trata-se da coluna dos coeficientes;
                    A[i][j] = 0;
                }


            }


        }
    }

    double detA = determinant(A, ui->matrix->rowCount());

    cout << detA << endl;

    if (testa_sistema(detA)) {
       //Colocando o valor da Determinante na tela:
       ui->label_determinant_value->setText(QString::number(detA));
       return true;
    }

    ui->label_determinant_value->setText(QString::number(detA));
    return false;

}

void Dialog::mountLUR(int tamanho, float** matrizL, float** matrizU,float *d) {
    QString value;

    // PREENCHENDO AS MATRIZES L & U:
    for(int linha=0; linha<tamanho; linha++){
        for(int coluna=0; coluna < tamanho; coluna++) {
                value = QString::number(matrizL[linha][coluna]);
                //cout << value.toFloat() << endl;
                ui->matrixL->setItem(linha,coluna,new QTableWidgetItem(value));
                ui->matrixL->item(linha,coluna)->setTextAlignment(Qt::AlignCenter);

                //cout << value.toFloat() << endl;
                value = QString::number(matrizU[linha][coluna]);
                ui->matrixU->setItem(linha,coluna,new QTableWidgetItem(value));
                ui->matrixU->item(linha,coluna)->setTextAlignment(Qt::AlignCenter);

        }
    }

    //cout << "Preencher Matriz resultados" << endl;

    // PREENCHENDO A MATRIZ DE RESULTADOS:
    for(int coluna=0; coluna<tamanho; coluna++) {

        value = QString::number(d[coluna]);

        ui->matrix_results->setItem(0,coluna,new QTableWidgetItem(value));
        ui->matrix_results->item(0,coluna)->setTextAlignment(Qt::AlignCenter);

    }

    // FAZENDO COM QUE AS MATRIZES L & U APAREÇAM NA TELA:
    ui->label_P->hide(); //Escondendo a Label D
    ui->label_U->setText(QString('U'));
    ui->label_totalOp_value->setText(QString::number(*count));

    if(geometry().height() < 666)
        this->resize(geometry().width(),geometry().height()*2); //Dobrando o tamanho da altura da tela;

    ui->matrixL->show();
    ui->matrixU->show();

}

void Dialog::mountLDP(LDP_Solucao solucao) {

    //Pegar o atributo solução pode ser acessado assim solucao.getResultadoEmOrdem()[i][j] ou
    Matriz finalresult = solucao.getSolucaoEmOrdem();
    //cout << "Final Result " << finalresult.getQuantLinhas() << " " << finalresult.getQuantColunas() << endl;
    //finalresult.print();

    //caso queira tem um matriz com os Resultados em ordem pós pivoteamento total orig*solucao = resultado
    //solucao.getResultadoEmOrdem();
    //Mesma coisa pra pegar L, D, P
    Matriz L = solucao.getL();
    //cout << "L" << endl;
    //L.print();
    Matriz D = solucao.getD();
    //cout << "D" << endl;
    //D.print();
    Matriz P = solucao.getP();
    //cout << "P" << endl;
    //P.print();

    int tamanho = ui->matrix->rowCount();
    QString value;

    cout << "Preencher Matriz na Tela:" << endl;

    // PREENCHENDO AS MATRIZES L & D (U) & P:
    for(int linha=0; linha< tamanho; linha++){
        for(int coluna=0; coluna < tamanho; coluna++) {
                value = QString::number(L[linha][coluna]);
                //value = QString::number(matrizL[linha][coluna]);
                ui->matrixL->setItem(linha,coluna,new QTableWidgetItem(value));
                ui->matrixL->item(linha,coluna)->setTextAlignment(Qt::AlignCenter);

                //cout << value.toFloat() << endl;
                value = QString::number(D[linha][coluna]);
                ui->matrixU->setItem(linha,coluna,new QTableWidgetItem(value));
                ui->matrixU->item(linha,coluna)->setTextAlignment(Qt::AlignCenter);

                value = QString::number(P[linha][coluna]);
                ui->matrixP->setItem(linha,coluna,new QTableWidgetItem(value));
                ui->matrixP->item(linha,coluna)->setTextAlignment(Qt::AlignCenter);

        }
    }

    cout << "Preencher Matriz resultados "  << ui->matrix->rowCount() << endl;

    // PREENCHENDO A MATRIZ DE RESULTADOS:
    for(int coluna=0; coluna<tamanho; coluna++) {
        value = QString::number(finalresult[coluna][0]);
        cout << "Value = " << value.toFloat() << endl;
        ui->matrix_results->setItem(0,coluna,new QTableWidgetItem(value));
        ui->matrix_results->item(0,coluna)->setTextAlignment(Qt::AlignCenter);

    }

    //cout << "Preechidos!" << endl;

    // FAZENDO COM QUE AS MATRIZES L & D(U) & P APAREÇAM NA TELA:
    //this->setGeometry(geometry().x, geometry().y, geometry().width(), geometry().height()*2);
    ui->label_U->setText(QString('D'));

    if(geometry().height() < 666)
        this->resize(geometry().width(),geometry().height()*2); //Dobrando o tamanho da altura da tela;

    ui->label_P->show();
    ui->matrixL->show();
    ui->matrixU->show();
    ui->matrixP->show();

}

void Dialog::on_btn_calculate_LU_clicked() {
    //Função que preencherá A e F, ou seja, pegará as informacoes colocadas pelos usuários;
    //Se o sistema for indeterminado, ele entrara no if;
    if (!capturateInputs()) {
        ui->label_error->setText(QString("Check the inputs! Indeterminate system."));
        return;
    }

    ui->label_P->hide();
    ui->matrixP->hide();
    //Variáveis para contar o tempo de execução:
    double elapsed;
    clock_t timeLUStart, timeLUFinish, timeFunctionStart, timeFunctionFinish;

    timeFunctionStart = clock();

    int c0 = 0;
    count = &c0;

    /*
    cout << "Print Matriz dos Coeficientes A:" << endl;
    for (int i=0; i<ui->matrix->rowCount(); i++) {
            for (int j=0; j<ui->matrix->columnCount()-1; j++)
                cout << i << " - " << j << ": " << A[i][j] << endl;
        }

    cout << "\nPrint Matriz F:" << endl;
    for (int i=0; i<ui->matrix->rowCount(); i++)
        cout  << i << ": " << F[i] << endl;
    */

    //Passando a ordem da matriz e a matriz dos coeficientes:
    timeLUStart = clock();
    float*** LU = calcula_LU(ui->matrix->rowCount(), A, count);
    timeLUFinish = clock();

    cout << "count: " << *count << endl;

    //Escrevendo o tempo de execução de LU na tela:
    elapsed = (double)(timeLUFinish - timeLUStart) * 1000.0 / CLOCKS_PER_SEC;
    ui->label_timeL->setText(QString::number(elapsed));
    ui->label_timeU->setText(QString::number(elapsed));

    cout << "Tempo execucao LU: " << elapsed << endl;

    //Calculando a matriz y:
    float* y = calcula_y(ui->matrix->rowCount(), LU[0], F, count);

    float* d = calcula_x(ui->matrix->rowCount(), LU[1], y, count);

    /*float determinant = determinante(ui->matrix->rowCount(), LU[1]);

    if (testa_sistema(determinant) ) {
         //Colocando o valor da Determinante na tela:
         //ui->label_determinant_value->setText(QString::number(determinant));

         //Funcao que montara as matrizes LUR:
         mountLUR(ui->matrix->rowCount(), LU[0], LU[1], d);
    }*/

    //Funcao que montara as matrizes LUR:
    mountLUR(ui->matrix->rowCount(), LU[0], LU[1], d);

    timeFunctionFinish = clock();
    elapsed = (double)(timeFunctionFinish - timeFunctionStart) * 1000.0 / CLOCKS_PER_SEC;
    ui->label_totalTime_value->setText(QString::number(elapsed));
}

void Dialog::on_btn_calculate_LDP_clicked()
{
    //Função que preencherá A e F, ou seja, pegará as informacoes colocadas pelos usuários;
    //Se o sistema for indeterminado, ele entrara no if;
    if (!capturateInputs()) {
        ui->label_error->setText(QString("Check the inputs! Indeterminate system."));
        return;
    }

    //Variáveis para contar o tempo de execução:
    clock_t timeLDPStart, timeLDPFinish, timeFunctionStart, timeFunctionFinish;
    double elapsed;

    timeFunctionStart = clock();

    int c0 = 0;
    count = &c0;

    // Pegando uma matriz [][], no caso A e convertendo-a para []. Assim, poderemos instanciar e utilizar a classe Matriz aqui implementada:
    float *elementsOfA = (float*) malloc((sizeof(Dialog::A)+1) * sizeof(float)); // Criando um array comum;

    int iterator = 0;
    for (int i=0; i<ui->matrix->rowCount(); i++) {
        for (int j=0; j<ui->matrix->columnCount()-1; j++) { //Diminuindo 1, pois o matrix Row Count tem uma coluna a mais, a coluna D:
            elementsOfA[iterator] = Dialog::A[i][j];
            iterator++;
            //cout << i << " - " << j << ": " << A[i][j] << endl;
        }
    }

    cout << "Iterator = " << iterator << endl;

    //double numbers[] = {3, -2, 1, 1,-3, 4,9, 4, -5};
    //Agora vamos preencher o vector:
    std::vector<double> A;
    for (int i = 0; i<iterator; i++){
        A.push_back(elementsOfA[i]);
    }

    Matriz sistema = Matriz(ui->matrix->rowCount(), (ui->matrix->columnCount()-1), A);
    cout << "A" << endl;
    sistema.print();

    //double numbers2[] = {8, 6, 11};
    //Agora, montaremos a matriz dos resultados:
    std::vector<double> F;
    for (int i=0; i<ui->matrix->rowCount(); i++)
            F.push_back(Dialog::F[i]);

    Matriz resultado = Matriz(ui->matrix->rowCount(), 1, F);
    cout << "F" << endl;
    resultado.print();


    //Instanciar LDP_Solucao o inteiro no final do construtor indica os tipos de pivoteamento que podem ser feitos 0->nenhum 1->parcial 2->total
    timeLDPStart = clock();
    LDP_Solucao ldp0 = LDP_Solucao::resolverPorLDP(sistema, resultado, 0);
    timeLDPFinish = clock();

    //Escrevendo o tempo de execução de LDP na tela:
    elapsed = (double)(timeLDPFinish - timeLDPStart) * 1000.0 / CLOCKS_PER_SEC;
    ui->label_timeL->setText(QString::number(elapsed));
    ui->label_timeU->setText(QString::number(elapsed));
    ui->label_timeD->setText(QString::number(elapsed));

    mountLDP(ldp0);

    timeFunctionFinish = clock();
    elapsed = (double)(timeFunctionFinish - timeFunctionStart) * 1000.0 / CLOCKS_PER_SEC;
    ui->label_totalTime_value->setText(QString::number(elapsed));

}

void Dialog::on_matrix_cellChanged(int row, int column)
{
    //cout << "Cell Changed:" << row << " " << column << endl;
    ui->matrix->item(row,column)->setTextAlignment(Qt::AlignCenter);
}
