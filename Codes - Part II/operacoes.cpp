//Class header file.
#include "operacoes.h"

TrocarLinhas::TrocarLinhas(int l1, int l2)
: linha1(l1), linha2(l2) {}

TrocarColunas::TrocarColunas(int c1, int c2)
: coluna1(c1), coluna2(c2) {}

AdicionarLinhaALinha::AdicionarLinhaALinha(int l1, int l2, double quant)
: linha1(l1), linha2(l2), quant(quant) {}

AdicionarColunaAColuna::AdicionarColunaAColuna(int c1, int c2, double quant)
: coluna1(c1), coluna2(c2), quant(quant) {}

PivotacaoParcialSuperior::PivotacaoParcialSuperior(int l, int c, Matriz& m)
: linha1(l), coluna1(c) {
    int maxlinhaindex = l;
    for(int i = l; i >= 0; i--) {
        if(m[i][c] > m[maxlinhaindex][c]) {
            maxlinhaindex = i;
        }
    }

    this->linha2 = maxlinhaindex;
    this->coluna2 = c;
}

PivotacaoParcialInferior::PivotacaoParcialInferior(int l, int c, Matriz& m)
: linha1(l), coluna1(c) {
    int maxlinhaindex = l;
    for(int i = l; i < m.getQuantLinhas(); i++) {
        if(m[i][c] > m[maxlinhaindex][c]) {
            maxlinhaindex = i;
        }
    }

    this->linha2 = maxlinhaindex;
    this->coluna2 = c;
}

PivotacaoParcialEsquerda::PivotacaoParcialEsquerda(int l, int c, Matriz& m)
: linha1(l), coluna1(c) {
    int maxcolunaindex = c;
    for(int j = l; j >= 0; j--) {
        if(m[l][j] > m[l][maxcolunaindex]) {
            maxcolunaindex = j;
        }
    }

    this->linha2 = l;
    this->coluna2 = maxcolunaindex;
}

PivotacaoParcialDireita::PivotacaoParcialDireita(int l, int c, Matriz& m)
: linha1(l), coluna1(c) {
    int maxcolunaindex = c;
    for(int j = l; j < m.getQuantColunas(); j++) {
        if(m[l][j] > m[l][maxcolunaindex]) {
            maxcolunaindex = j;
        }
    }

    this->linha2 = l;
    this->coluna2 = maxcolunaindex;
}

PivotacaoTotalSuperiorEsquerda::PivotacaoTotalSuperiorEsquerda(int l, int c, Matriz& m)
: linha1(l), coluna1(c) {
    int maxlinhaindex = l;
    int maxcolunaindex = c;
    for(int i = l; i >= 0; i--) {
        for(int j = c; j >= 0; j--) {
            if(m[i][j] > m[maxlinhaindex][maxcolunaindex]) {
                maxlinhaindex = i;
                maxcolunaindex = j;
            }
        }
    }

    this->linha2 = maxlinhaindex;
    this->coluna2 = maxcolunaindex;
}

PivotacaoTotalSuperiorDireita::PivotacaoTotalSuperiorDireita(int l, int c, Matriz& m)
: linha1(l), coluna1(c) {
    int maxlinhaindex = l;
    int maxcolunaindex = c;
    for(int i = l; i >= 0; i--) {
        for(int j = c; j >= 0; j--) {
            if(m[i][j] > m[maxlinhaindex][maxcolunaindex]) {
                maxlinhaindex = i;
                maxcolunaindex = j;
            }
        }
    }

    this->linha2 = maxlinhaindex;
    this->coluna2 = maxcolunaindex;
}

PivotacaoTotalInferiorEsquerda::PivotacaoTotalInferiorEsquerda(int l, int c, Matriz& m)
: linha1(l), coluna1(c) {
    int maxlinhaindex = l;
    int maxcolunaindex = c;
    for(int i = l; i >= 0; i--) {
        for(int j = c; j < m.getQuantColunas(); j++) {
            if(m[i][j] > m[maxlinhaindex][maxcolunaindex]) {
                maxlinhaindex = i;
                maxcolunaindex = j;
            }
        }
    }

    this->linha2 = maxlinhaindex;
    this->coluna2 = maxcolunaindex;
}

PivotacaoTotalInferiorDireita::PivotacaoTotalInferiorDireita(int l, int c, Matriz& m)
: linha1(l), coluna1(c) {
    int maxlinhaindex = l;
    int maxcolunaindex = c;
    for(int i = l; i < m.getQuantLinhas(); i++) {
        for(int j = c; j < m.getQuantColunas(); j++) {
            if(m[i][j] > m[maxlinhaindex][maxcolunaindex]) {
                maxlinhaindex = i;
                maxcolunaindex = j;
            }
        }
    }

    this->linha2 = maxlinhaindex;
    this->coluna2 = maxcolunaindex;
}

UniformizarLinha::UniformizarLinha(int l, int c)
: linha(l), coluna(c) {}

UniformizarColuna::UniformizarColuna(int l, int c)
: linha(l), coluna(c) {}

ZerarLinhasAcima::ZerarLinhasAcima(int l, int c)
: linha(l), coluna(c) {}

ZerarLinhasAbaixo::ZerarLinhasAbaixo(int l, int c)
: linha(l), coluna(c) {}

ZerarColunasEsquerda::ZerarColunasEsquerda(int l, int c)
: linha(l), coluna(c) {}

ZerarColunasDireita::ZerarColunasDireita(int l, int c)
: linha(l), coluna(c) {}

Matriz TrocarLinhas::executarSobre(Matriz& m) const {
    Matriz n = m;

    for(int j = 0; j < m.getQuantColunas(); j++) {
        n[this->linha1][j] = m[this->linha2][j];
        n[this->linha2][j] = m[this->linha1][j];
    }

    return n;
}

Matriz TrocarColunas::executarSobre(Matriz& m) const {
    Matriz n = m;

    for(int i = 0; i < m.getQuantLinhas(); i++) {
        n[i][this->coluna1] = m[i][this->coluna2];
        n[i][this->coluna2] = m[i][this->coluna1];
    }

    return n;
}

Matriz AdicionarLinhaALinha::executarSobre(Matriz& m) const {
    Matriz n = m;

    for(int j = 0; j < m.getQuantColunas(); j++) {
        n[this->linha2][j] += this->quant * m[this->linha1][j];
    }

    return n;
}

Matriz AdicionarColunaAColuna::executarSobre(Matriz& m) const {
    Matriz n = m;

    for(int i = 0; i < m.getQuantLinhas(); i++) {
        n[i][this->coluna2] += this->quant * m[i][this->coluna1];
    }

    return n;
}

Matriz PivotacaoParcialSuperior::executarSobre(Matriz& m) const {
    Matriz n = m;

    n = TrocarLinhas(this->linha1, this->linha2).executarSobre(n);

    return n;
}

Matriz PivotacaoParcialInferior::executarSobre(Matriz& m) const {
    Matriz n = m;

    n = TrocarLinhas(this->linha1, this->linha2).executarSobre(n);

    return n;
}

Matriz PivotacaoParcialEsquerda::executarSobre(Matriz& m) const {
    Matriz n = m;

    n = TrocarColunas(this->coluna1, this->coluna2).executarSobre(n);

    return n;
}

Matriz PivotacaoParcialDireita::executarSobre(Matriz& m) const {
    Matriz n = m;

    n = TrocarColunas(this->coluna1, this->coluna2).executarSobre(n);

    return n;
}

Matriz PivotacaoTotalSuperiorEsquerda::executarSobre(Matriz& m) const {
    Matriz n = m;

    n = TrocarLinhas(this->linha1, this->linha2).executarSobre(n);
    n = TrocarColunas(this->coluna1, this->coluna2).executarSobre(n);

    return n;
}

Matriz PivotacaoTotalSuperiorDireita::executarSobre(Matriz& m) const {
    Matriz n = m;

    n = TrocarLinhas(this->linha1, this->linha2).executarSobre(n);
    n = TrocarColunas(this->coluna1, this->coluna2).executarSobre(n);

    return n;
}

Matriz PivotacaoTotalInferiorEsquerda::executarSobre(Matriz& m) const {
    Matriz n = m;

    n = TrocarLinhas(this->linha1, this->linha2).executarSobre(n);
    n = TrocarColunas(this->coluna1, this->coluna2).executarSobre(n);

    return n;
}

Matriz PivotacaoTotalInferiorDireita::executarSobre(Matriz& m) const {
    Matriz n = m;

    n = TrocarLinhas(this->linha1, this->linha2).executarSobre(n);
    n = TrocarColunas(this->coluna1, this->coluna2).executarSobre(n);

    return n;
}

Matriz UniformizarLinha::executarSobre(Matriz& m) const {
    Matriz n = m;

    for(int j = 0; j < m.getQuantColunas(); j++) {
        n[this->linha][j] /= m[this->linha][this->coluna];
    }

    return n;
}

Matriz UniformizarColuna::executarSobre(Matriz& m) const {
    Matriz n = m;

    for(int i = 0; i < m.getQuantLinhas(); i++) {
        n[i][this->coluna] /= m[this->linha][this->coluna];
    }

    return n;
}

Matriz ZerarLinhasAcima::executarSobre(Matriz& m) const {
    Matriz n = m;

    for(int i = this->linha - 1; i >= 0; i--) {
        for(int j = 0; j < m.getQuantColunas(); j++) {
            n[i][j] -= m[this->linha][j] * m[i][this->coluna] / m[this->linha][this->coluna];
        }
    }

    return n;
}

Matriz ZerarLinhasAbaixo::executarSobre(Matriz& m) const {
    Matriz n = m;

    for(int i = this->linha + 1; i < m.getQuantLinhas(); i++) {
        for(int j = 0; j < m.getQuantColunas(); j++) {
            n[i][j] -= m[this->linha][j] * m[i][this->coluna] / m[this->linha][this->coluna];
        }
    }

    return n;
}

Matriz ZerarColunasEsquerda::executarSobre(Matriz& m) const {
    Matriz n = m;

    for(int j = this->coluna - 1; j >= 0; j--) {
        for(int i = 0; i < m.getQuantLinhas(); i++) {
            n[i][j] -= m[i][this->coluna] * m[this->linha][j] / m[this->linha][this->coluna];
        }
    }

    return n;
}

Matriz ZerarColunasDireita::executarSobre(Matriz& m) const {
    Matriz n = m;

    for(int j = this->coluna + 1; j < m.getQuantColunas(); j++) {
        for(int i = 0; i < m.getQuantLinhas(); i++) {
            n[i][j] -= m[i][this->coluna] * m[this->linha][j] / m[this->linha][this->coluna];
        }
    }

    return n;
}

int TrocarLinhas::getLinha1() const {
    return this->linha1;
}

int TrocarLinhas::getLinha2() const {
    return this->linha2;
}

int TrocarColunas::getColuna1() const {
    return this->coluna1;
}

int TrocarColunas::getColuna2() const {
    return this->coluna2;
}

int AdicionarLinhaALinha::getLinha1() const {
    return this->linha1;
}

int AdicionarLinhaALinha::getLinha2() const {
    return this->linha2;
}

int AdicionarColunaAColuna::getColuna1() const {
    return this->coluna1;
}

int AdicionarColunaAColuna::getColuna2() const {
    return this->coluna2;
}

int PivotacaoParcialSuperior::getLinha1() const {
    return this->linha1;
}

int PivotacaoParcialSuperior::getColuna1() const {
    return this->coluna1;
}

int PivotacaoParcialSuperior::getLinha2() const {
    return this->linha2;
}

int PivotacaoParcialSuperior::getColuna2() const {
    return this->coluna2;
}

int PivotacaoParcialInferior::getLinha1() const {
    return this->linha1;
}

int PivotacaoParcialInferior::getColuna1() const {
    return this->coluna1;
}

int PivotacaoParcialInferior::getLinha2() const {
    return this->linha2;
}

int PivotacaoParcialInferior::getColuna2() const {
    return this->coluna2;
}

int PivotacaoParcialEsquerda::getLinha1() const {
    return this->linha1;
}

int PivotacaoParcialEsquerda::getColuna1() const {
    return this->coluna1;
}

int PivotacaoParcialEsquerda::getLinha2() const {
    return this->linha2;
}

int PivotacaoParcialEsquerda::getColuna2() const {
    return this->coluna2;
}

int PivotacaoParcialDireita::getLinha1() const {
    return this->linha1;
}

int PivotacaoParcialDireita::getColuna1() const {
    return this->coluna1;
}

int PivotacaoParcialDireita::getLinha2() const {
    return this->linha2;
}

int PivotacaoParcialDireita::getColuna2() const {
    return this->coluna2;
}

int PivotacaoTotalSuperiorEsquerda::getLinha1() const {
    return this->linha1;
}

int PivotacaoTotalSuperiorEsquerda::getColuna1() const {
    return this->coluna1;
}

int PivotacaoTotalSuperiorEsquerda::getLinha2() const {
    return this->linha2;
}

int PivotacaoTotalSuperiorEsquerda::getColuna2() const {
    return this->coluna2;
}

int PivotacaoTotalSuperiorDireita::getLinha1() const {
    return this->linha1;
}

int PivotacaoTotalSuperiorDireita::getColuna1() const {
    return this->coluna1;
}

int PivotacaoTotalSuperiorDireita::getLinha2() const {
    return this->linha2;
}

int PivotacaoTotalSuperiorDireita::getColuna2() const {
    return this->coluna2;
}

int PivotacaoTotalInferiorEsquerda::getLinha1() const {
    return this->linha1;
}

int PivotacaoTotalInferiorEsquerda::getColuna1() const {
    return this->coluna1;
}

int PivotacaoTotalInferiorEsquerda::getLinha2() const {
    return this->linha2;
}

int PivotacaoTotalInferiorEsquerda::getColuna2() const {
    return this->coluna2;
}

int PivotacaoTotalInferiorDireita::getLinha1() const {
    return this->linha1;
}

int PivotacaoTotalInferiorDireita::getColuna1() const {
    return this->coluna1;
}

int PivotacaoTotalInferiorDireita::getLinha2() const {
    return this->linha2;
}

int PivotacaoTotalInferiorDireita::getColuna2() const {
    return this->coluna2;
}

int UniformizarLinha::getLinha() const {
    return this->linha;
}

int UniformizarLinha::getColuna() const {
    return this->coluna;
}

int UniformizarColuna::getLinha() const {
    return this->linha;
}

int UniformizarColuna::getColuna() const {
    return this->coluna;
}

int ZerarLinhasAcima::getLinha() const {
    return this->linha;
}

int ZerarLinhasAcima::getColuna() const {
    return this->coluna;
}

int ZerarLinhasAbaixo::getLinha() const {
    return this->linha;
}

int ZerarLinhasAbaixo::getColuna() const {
    return this->coluna;
}

int ZerarColunasEsquerda::getLinha() const {
    return this->linha;
}

int ZerarColunasEsquerda::getColuna() const {
    return this->coluna;
}

int ZerarColunasDireita::getLinha() const {
    return this->linha;
}

int ZerarColunasDireita::getColuna() const {
    return this->coluna;
}

int TrocarLinhas::getIDOperacao() const {
    return 0;
}

std::string TrocarLinhas::getNomeOperacao() const {
    return "Trocar linhas";
}

int TrocarColunas::getIDOperacao() const {
    return 1;
}

std::string TrocarColunas::getNomeOperacao() const {
    return "Trocar colunas";
}

int AdicionarLinhaALinha::getIDOperacao() const {
    return 2;
}

std::string AdicionarLinhaALinha::getNomeOperacao() const {
    return "Adicionar uma linha a outra";
}

int AdicionarColunaAColuna::getIDOperacao() const {
    return 3;
}

std::string AdicionarColunaAColuna::getNomeOperacao() const {
    return "Adicionar uma coluna a outra";
}

int PivotacaoParcialSuperior::getIDOperacao() const {
    return 4;
}

std::string PivotacaoParcialSuperior::getNomeOperacao() const {
    return "Pivotacao parcial superior";
}

int PivotacaoParcialInferior::getIDOperacao() const {
    return 5;
}

std::string PivotacaoParcialInferior::getNomeOperacao() const {
    return "Pivotacao parcial inferior";
}

int PivotacaoParcialEsquerda::getIDOperacao() const {
    return 6;
}

std::string PivotacaoParcialEsquerda::getNomeOperacao() const {
    return "Pivotacao parcial esquerda";
}

int PivotacaoParcialDireita::getIDOperacao() const {
    return 7;
}

std::string PivotacaoParcialDireita::getNomeOperacao() const {
    return "Pivotacao parcial direita";
}

int PivotacaoTotalSuperiorEsquerda::getIDOperacao() const {
    return 8;
}

std::string PivotacaoTotalSuperiorEsquerda::getNomeOperacao() const {
    return "Pivotacao total superior esquerda";
}

int PivotacaoTotalSuperiorDireita::getIDOperacao() const {
    return 9;
}

std::string PivotacaoTotalSuperiorDireita::getNomeOperacao() const {
    return "Pivotacao total superior direita";
}

int PivotacaoTotalInferiorEsquerda::getIDOperacao() const {
    return 10;
}

std::string PivotacaoTotalInferiorEsquerda::getNomeOperacao() const {
    return "Pivotacao total inferior esquerda";
}

int PivotacaoTotalInferiorDireita::getIDOperacao() const {
    return 11;
}

std::string PivotacaoTotalInferiorDireita::getNomeOperacao() const {
    return "Pivotacao total inferior direita";
}

int UniformizarLinha::getIDOperacao() const {
    return 12;
}

std::string UniformizarLinha::getNomeOperacao() const {
    return "Uniformizar linha";
}

int UniformizarColuna::getIDOperacao() const {
    return 13;
}

std::string UniformizarColuna::getNomeOperacao() const {
    return "Uniformizar coluna";
}

int ZerarLinhasAcima::getIDOperacao() const {
    return 14;
}

std::string ZerarLinhasAcima::getNomeOperacao() const {
    return "Zerar linhas acima";
}

int ZerarLinhasAbaixo::getIDOperacao() const {
    return 15;
}

std::string ZerarLinhasAbaixo::getNomeOperacao() const {
    return "Zerar linhas abaixo";
}

int ZerarColunasEsquerda::getIDOperacao() const {
    return 16;
}

std::string ZerarColunasEsquerda::getNomeOperacao() const {
    return "Zerar colunas à esquerda";
}

int ZerarColunasDireita::getIDOperacao() const {
    return 17;
}

std::string ZerarColunasDireita::getNomeOperacao() const {
    return "Zerar colunas à direita";
}
