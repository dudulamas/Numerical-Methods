#ifndef LU_SOLUCAO_H
#define LU_SOLUCAO_H

//Imported classes from the project.
#include "matriz.h"
#include "operacoes.h"
//Imported libraries.

class LU_Solucao {
private:
    Matriz orig;
    Matriz L;
    Matriz U;
    Matriz resultado;
    Matriz solucaoparcial;
    Matriz solucao;
    Matriz index;
public:
    LU_Solucao(const Matriz& o, const Matriz& l, const Matriz& u, const Matriz& r, const Matriz& sp, const Matriz& s, const Matriz& i);
    static LU_Solucao resolverPorLU(const Matriz& s, const Matriz& r, int pivot);

    Matriz getOriginal() const;
    Matriz getL() const;
    Matriz getU() const;
    Matriz getResultado() const;
    Matriz getSolucaoParcial() const;
    Matriz getSolucao() const;
    Matriz getIndex() const;
    Matriz getResultadoEmOrdem();
    Matriz getSolucaoEmOrdem();
};

#endif /* LU_SOLUCAO_H */

