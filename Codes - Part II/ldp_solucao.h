#ifndef LDP_SOLUCAO_H
#define LDP_SOLUCAO_H

//Imported classes from the project.
#include "matriz.h"
#include "operacoes.h"
//Imported libraries.

class LDP_Solucao {
private:
    Matriz orig;
    Matriz L;
    Matriz D;
    Matriz P;
    Matriz resultado;
    Matriz solucaoparcial1;
    Matriz solucaoparcial2;
    Matriz solucao;
    Matriz index;
public:
    LDP_Solucao(const Matriz& o, const Matriz& l, const Matriz& d, const Matriz& p, const Matriz& r, const Matriz& sp1, const Matriz& sp2, const Matriz& s, const Matriz& i);
    static LDP_Solucao resolverPorLDP(const Matriz& s, const Matriz& r, int pivot);

    Matriz getOriginal() const;
    Matriz getL() const;
    Matriz getD() const;
    Matriz getP() const;
    Matriz getResultado() const;
    Matriz getSolucaoParcial1() const;
    Matriz getSolucaoParcial2() const;
    Matriz getSolucao() const;
    Matriz getIndex() const;
    Matriz getResultadoEmOrdem();
    Matriz getSolucaoEmOrdem();


};

#endif /* LDP_SOLUCAO_H */

