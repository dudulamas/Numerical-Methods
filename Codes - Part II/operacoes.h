#ifndef OPERACOES_H
#define OPERACOES_H

//Imported classes from the project.
#include "matriz.h"
//Imported libraries.
#include <string>

class Operacao {
private:

public:
    virtual Matriz executarSobre(Matriz& m) const=0;
    virtual int getIDOperacao() const=0;
    virtual std::string getNomeOperacao() const=0;
};

class TrocarLinhas : public Operacao {
private:
    int linha1, linha2;
public:
    TrocarLinhas(int l1, int l2);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha1() const;
    int getLinha2() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class TrocarColunas : public Operacao {
private:
    int coluna1, coluna2;
public:
    TrocarColunas(int c1, int c2);

    virtual Matriz executarSobre(Matriz& m) const;

    int getColuna1() const;
    int getColuna2() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class AdicionarLinhaALinha : public Operacao {
private:
    int linha1, linha2;
    double quant;
public:
    AdicionarLinhaALinha(int l1, int l2, double quant);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha1() const;
    int getLinha2() const;
    double getQuant() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class AdicionarColunaAColuna : public Operacao {
private:
    int coluna1, coluna2;
    double quant;
public:
    AdicionarColunaAColuna(int c1, int c2, double quant);

    virtual Matriz executarSobre(Matriz& m) const;

    int getColuna1() const;
    int getColuna2() const;
    double getQuant() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class PivotacaoParcialSuperior : public Operacao {
private:
    int linha1, coluna1, linha2, coluna2;
public:
    PivotacaoParcialSuperior(int l, int c, Matriz& m);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha1() const;
    int getColuna1() const;
    int getLinha2() const;
    int getColuna2() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class PivotacaoParcialInferior : public Operacao {
private:
    int linha1, coluna1, linha2, coluna2;
public:
    PivotacaoParcialInferior(int l, int c, Matriz& m);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha1() const;
    int getColuna1() const;
    int getLinha2() const;
    int getColuna2() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class PivotacaoParcialEsquerda : public Operacao {
private:
    int linha1, coluna1, linha2, coluna2;
public:
    PivotacaoParcialEsquerda(int l, int c, Matriz& m);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha1() const;
    int getColuna1() const;
    int getLinha2() const;
    int getColuna2() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class PivotacaoParcialDireita : public Operacao {
private:
    int linha1, coluna1, linha2, coluna2;
public:
    PivotacaoParcialDireita(int l, int c, Matriz& m);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha1() const;
    int getColuna1() const;
    int getLinha2() const;
    int getColuna2() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class PivotacaoTotalSuperiorEsquerda : public Operacao {
private:
    int linha1, coluna1, linha2, coluna2;
public:
    PivotacaoTotalSuperiorEsquerda(int l, int c, Matriz& m);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha1() const;
    int getColuna1() const;
    int getLinha2() const;
    int getColuna2() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class PivotacaoTotalSuperiorDireita : public Operacao {
private:
    int linha1, coluna1, linha2, coluna2;
public:
    PivotacaoTotalSuperiorDireita(int l, int c, Matriz& m);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha1() const;
    int getColuna1() const;
    int getLinha2() const;
    int getColuna2() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class PivotacaoTotalInferiorEsquerda : public Operacao {
private:
    int linha1, coluna1, linha2, coluna2;
public:
    PivotacaoTotalInferiorEsquerda(int l, int c, Matriz& m);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha1() const;
    int getColuna1() const;
    int getLinha2() const;
    int getColuna2() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class PivotacaoTotalInferiorDireita : public Operacao {
private:
    int linha1, coluna1, linha2, coluna2;
public:
    PivotacaoTotalInferiorDireita(int l, int c, Matriz& m);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha1() const;
    int getColuna1() const;
    int getLinha2() const;
    int getColuna2() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class UniformizarLinha : public Operacao {
private:
    int linha, coluna;
public:
    UniformizarLinha(int l, int c);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha() const;
    int getColuna() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class UniformizarColuna : public Operacao {
private:
    int linha, coluna;
public:
    UniformizarColuna(int l, int c);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha() const;
    int getColuna() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class ZerarLinhasAcima : public Operacao {
private:
    int linha, coluna;
public:
    ZerarLinhasAcima(int l, int c);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha() const;
    int getColuna() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class ZerarLinhasAbaixo : public Operacao {
private:
    int linha, coluna;
public:
    ZerarLinhasAbaixo(int l, int c);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha() const;
    int getColuna() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class ZerarColunasEsquerda : public Operacao {
private:
    int linha, coluna;
public:
    ZerarColunasEsquerda(int l, int c);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha() const;
    int getColuna() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

class ZerarColunasDireita : public Operacao {
private:
    int linha, coluna;
public:
    ZerarColunasDireita(int l, int c);

    virtual Matriz executarSobre(Matriz& m) const;

    int getLinha() const;
    int getColuna() const;

    virtual int getIDOperacao() const;
    virtual std::string getNomeOperacao() const;
};

#endif /* OPERACOES_H */
